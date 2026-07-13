using System.Diagnostics;
using System.Drawing;
using System.Security.Cryptography;
using System.Text;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Windows.Forms;

namespace GioushJudge;

internal static class Program
{
    [STAThread]
    private static void Main()
    {
        ApplicationConfiguration.Initialize();
        Application.Run(new MainForm());
    }
}

internal sealed class MainForm : Form
{
    private const string DefaultManifest = "https://ehundategh.github.io/Blog/oj/problems.json";

    private readonly SplitContainer split = new();
    private readonly ListView problemList = new();
    private readonly TextBox searchBox = new();
    private readonly Label accountLabel = new();
    private readonly Label titleLabel = new();
    private readonly Label sourceLabel = new();
    private readonly Label statusLabel = new();
    private readonly TextBox sourcePathBox = new();
    private readonly Button registerButton = new();
    private readonly Button loginButton = new();
    private readonly Button logoutButton = new();
    private readonly Button chooseButton = new();
    private readonly Button submitButton = new();
    private readonly Button exportButton = new();
    private readonly Button refreshButton = new();
    private readonly ProgressBar progress = new();
    private readonly TextBox outputBox = new();

    private readonly HttpClient http = new();
    private readonly List<ProblemInfo> problems = new();
    private readonly List<AccountInfo> accounts = new();
    private JsonObject records = new();
    private AccountInfo? currentAccount;
    private ProblemInfo? currentProblem;

    private string judgeRoot = "";
    private string accountFile = "";
    private string sessionFile = "";
    private string runnerPath = "";

    public MainForm()
    {
        Text = "Gioush Judge";
        MinimumSize = new Size(1080, 680);
        StartPosition = FormStartPosition.CenterScreen;
        Font = new Font("Microsoft YaHei UI", 10F);
        BackColor = Color.FromArgb(245, 247, 251);
        BuildLayout();
        Shown += async (_, _) => await InitializeAsync();
    }

    private void BuildLayout()
    {
        split.Dock = DockStyle.Fill;
        split.SplitterDistance = 360;
        split.Panel1.Padding = new Padding(16);
        split.Panel2.Padding = new Padding(18);
        Controls.Add(split);

        var leftTitle = new Label
        {
            Text = "题目列表",
            Dock = DockStyle.Top,
            Height = 38,
            Font = new Font(Font.FontFamily, 18F, FontStyle.Bold)
        };
        searchBox.Dock = DockStyle.Top;
        searchBox.Height = 34;
        searchBox.PlaceholderText = "搜索题号或题名";
        searchBox.TextChanged += (_, _) => RenderProblems();

        problemList.Dock = DockStyle.Fill;
        problemList.View = View.Details;
        problemList.FullRowSelect = true;
        problemList.HideSelection = false;
        problemList.Columns.Add("题号", 150);
        problemList.Columns.Add("题目", 110);
        problemList.Columns.Add("状态", 70);
        problemList.SelectedIndexChanged += (_, _) => SelectCurrentProblem();

        split.Panel1.Controls.Add(problemList);
        split.Panel1.Controls.Add(searchBox);
        split.Panel1.Controls.Add(leftTitle);

        var header = new TableLayoutPanel
        {
            Dock = DockStyle.Top,
            Height = 112,
            ColumnCount = 2,
            RowCount = 3
        };
        header.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 70));
        header.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 30));
        header.RowStyles.Add(new RowStyle(SizeType.Absolute, 44));
        header.RowStyles.Add(new RowStyle(SizeType.Absolute, 34));
        header.RowStyles.Add(new RowStyle(SizeType.Absolute, 34));

        titleLabel.Text = "Gioush Judge";
        titleLabel.Font = new Font(Font.FontFamily, 21F, FontStyle.Bold);
        titleLabel.Dock = DockStyle.Fill;
        titleLabel.TextAlign = ContentAlignment.MiddleLeft;

        sourceLabel.Text = "选择题目后即可提交。";
        sourceLabel.Dock = DockStyle.Fill;
        sourceLabel.ForeColor = Color.FromArgb(90, 99, 118);

        statusLabel.Text = "未评测";
        statusLabel.Dock = DockStyle.Fill;
        statusLabel.ForeColor = Color.FromArgb(64, 76, 168);

        accountLabel.Text = "未登录";
        accountLabel.Dock = DockStyle.Fill;
        accountLabel.TextAlign = ContentAlignment.MiddleRight;
        accountLabel.Font = new Font(Font.FontFamily, 10F, FontStyle.Bold);

        refreshButton.Text = "刷新";
        refreshButton.Dock = DockStyle.Right;
        refreshButton.Width = 90;
        refreshButton.Click += async (_, _) => await LoadStateAsync();

        header.Controls.Add(titleLabel, 0, 0);
        header.Controls.Add(accountLabel, 1, 0);
        header.Controls.Add(sourceLabel, 0, 1);
        header.Controls.Add(refreshButton, 1, 1);
        header.Controls.Add(statusLabel, 0, 2);

        var accountPanel = new FlowLayoutPanel
        {
            Dock = DockStyle.Top,
            Height = 46,
            FlowDirection = FlowDirection.LeftToRight
        };
        registerButton.Text = "注册";
        loginButton.Text = "登录";
        logoutButton.Text = "退出";
        registerButton.Width = loginButton.Width = logoutButton.Width = 90;
        registerButton.Click += (_, _) => RegisterAccount();
        loginButton.Click += (_, _) => LoginAccount();
        logoutButton.Click += async (_, _) => await LogoutAsync();
        accountPanel.Controls.Add(registerButton);
        accountPanel.Controls.Add(loginButton);
        accountPanel.Controls.Add(logoutButton);

        var submitPanel = new TableLayoutPanel
        {
            Dock = DockStyle.Top,
            Height = 92,
            ColumnCount = 4,
            RowCount = 2
        };
        submitPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100));
        submitPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 108));
        submitPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 108));
        submitPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 108));
        submitPanel.RowStyles.Add(new RowStyle(SizeType.Absolute, 42));
        submitPanel.RowStyles.Add(new RowStyle(SizeType.Absolute, 42));

        sourcePathBox.Dock = DockStyle.Fill;
        sourcePathBox.PlaceholderText = "选择 main.cpp 或直接粘贴路径";
        chooseButton.Text = "选择代码";
        submitButton.Text = "Submit";
        exportButton.Text = "导出报告";
        chooseButton.Dock = submitButton.Dock = exportButton.Dock = DockStyle.Fill;
        chooseButton.Click += (_, _) => ChooseSourceFile();
        submitButton.Click += async (_, _) => await SubmitAsync();
        exportButton.Click += async (_, _) => await ExportAsync();
        progress.Dock = DockStyle.Fill;
        progress.Style = ProgressBarStyle.Continuous;

        submitPanel.Controls.Add(sourcePathBox, 0, 0);
        submitPanel.Controls.Add(chooseButton, 1, 0);
        submitPanel.Controls.Add(submitButton, 2, 0);
        submitPanel.Controls.Add(exportButton, 3, 0);
        submitPanel.Controls.Add(progress, 0, 1);
        submitPanel.SetColumnSpan(progress, 4);

        outputBox.Dock = DockStyle.Fill;
        outputBox.Multiline = true;
        outputBox.ScrollBars = ScrollBars.Both;
        outputBox.ReadOnly = true;
        outputBox.WordWrap = false;
        outputBox.Font = new Font("Consolas", 10F);
        outputBox.BackColor = Color.FromArgb(22, 25, 36);
        outputBox.ForeColor = Color.FromArgb(238, 243, 255);
        outputBox.Text = "等待提交。";

        split.Panel2.Controls.Add(outputBox);
        split.Panel2.Controls.Add(submitPanel);
        split.Panel2.Controls.Add(accountPanel);
        split.Panel2.Controls.Add(header);
    }

    private async Task InitializeAsync()
    {
        judgeRoot = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile), ".gioush-judge");
        accountFile = Path.Combine(judgeRoot, "accounts.json");
        sessionFile = Path.Combine(judgeRoot, "session.json");
        runnerPath = Path.Combine(AppContext.BaseDirectory, "gioush-judge.ps1");
        Directory.CreateDirectory(judgeRoot);
        LoadAccounts();
        LoadSession();
        await LoadStateAsync();
    }

    private async Task LoadStateAsync()
    {
        SetBusy(true);
        try
        {
            await LoadProblemsAsync();
            LoadRecords();
            RenderAccount();
            RenderProblems();
            SelectCurrentProblem();
        }
        catch (Exception ex)
        {
            outputBox.Text = ex.Message;
        }
        finally
        {
            SetBusy(false);
        }
    }

    private async Task LoadProblemsAsync()
    {
        problems.Clear();
        var json = await http.GetStringAsync(DefaultManifest);
        using var doc = JsonDocument.Parse(json);
        foreach (var item in doc.RootElement.GetProperty("problems").EnumerateArray())
        {
            problems.Add(new ProblemInfo(
                item.GetProperty("id").GetString() ?? "",
                item.GetProperty("title").GetString() ?? "",
                item.GetProperty("source").GetString() ?? ""));
        }
    }

    private void LoadAccounts()
    {
        accounts.Clear();
        if (!File.Exists(accountFile)) return;
        using var doc = JsonDocument.Parse(File.ReadAllText(accountFile, Encoding.UTF8));
        if (!doc.RootElement.TryGetProperty("accounts", out var array)) return;
        foreach (var item in array.EnumerateArray())
        {
            accounts.Add(new AccountInfo(
                item.GetProperty("name").GetString() ?? "",
                item.GetProperty("handle").GetString() ?? "",
                item.GetProperty("salt").GetString() ?? "",
                item.GetProperty("passwordHash").GetString() ?? ""));
        }
    }

    private void SaveAccounts()
    {
        Directory.CreateDirectory(judgeRoot);
        var accountArray = new JsonArray();
        foreach (var account in accounts)
        {
            accountArray.Add(new JsonObject
            {
                ["name"] = account.Name,
                ["handle"] = account.Handle,
                ["salt"] = account.Salt,
                ["passwordHash"] = account.PasswordHash
            });
        }
        var root = new JsonObject { ["accounts"] = accountArray };
        File.WriteAllText(accountFile, root.ToJsonString(new JsonSerializerOptions { WriteIndented = true }), new UTF8Encoding(false));
    }

    private void LoadSession()
    {
        currentAccount = null;
        if (!File.Exists(sessionFile)) return;
        using var doc = JsonDocument.Parse(File.ReadAllText(sessionFile, Encoding.UTF8));
        var handle = doc.RootElement.TryGetProperty("handle", out var h) ? h.GetString() : "";
        currentAccount = accounts.FirstOrDefault(x => x.Handle == handle);
    }

    private void SaveSession()
    {
        Directory.CreateDirectory(judgeRoot);
        var root = new JsonObject { ["handle"] = currentAccount?.Handle ?? "" };
        File.WriteAllText(sessionFile, root.ToJsonString(), new UTF8Encoding(false));
    }

    private string ActiveHome()
    {
        if (currentAccount is null) return judgeRoot;
        var safe = string.Concat(currentAccount.Handle.Select(c => char.IsLetterOrDigit(c) || c is '_' or '-' or '.' ? c : '_'));
        var path = Path.Combine(judgeRoot, "accounts", safe);
        Directory.CreateDirectory(path);
        return path;
    }

    private void SaveProfile()
    {
        if (currentAccount is null) return;
        var profile = new JsonObject
        {
            ["name"] = currentAccount.Name,
            ["handle"] = currentAccount.Handle,
            ["updatedAt"] = DateTimeOffset.UtcNow.ToString("o")
        };
        File.WriteAllText(Path.Combine(ActiveHome(), "profile.json"), profile.ToJsonString(new JsonSerializerOptions { WriteIndented = true }), new UTF8Encoding(false));
    }

    private void LoadRecords()
    {
        records = new JsonObject();
        var path = Path.Combine(ActiveHome(), "records.json");
        if (!File.Exists(path)) return;
        records = JsonNode.Parse(File.ReadAllText(path, Encoding.UTF8))?.AsObject() ?? new JsonObject();
    }

    private void RenderAccount()
    {
        accountLabel.Text = currentAccount is null ? "未登录" : $"{currentAccount.Name} / {currentAccount.Handle}";
        logoutButton.Enabled = currentAccount is not null;
    }

    private void RenderProblems()
    {
        problemList.BeginUpdate();
        problemList.Items.Clear();
        var key = searchBox.Text.Trim();
        foreach (var problem in problems)
        {
            if (key.Length > 0 && !problem.Id.Contains(key, StringComparison.OrdinalIgnoreCase) && !problem.Title.Contains(key, StringComparison.OrdinalIgnoreCase))
                continue;
            var status = ProblemStatus(problem.Id);
            var item = new ListViewItem(new[] { problem.Id, problem.Title, status }) { Tag = problem };
            if (status == "AC") item.ForeColor = Color.FromArgb(20, 128, 111);
            problemList.Items.Add(item);
        }
        problemList.EndUpdate();
        if (problemList.Items.Count > 0 && problemList.SelectedItems.Count == 0)
            problemList.Items[0].Selected = true;
    }

    private string ProblemStatus(string id)
    {
        if (!records.TryGetPropertyValue(id, out var node) || node is null) return "-";
        var obj = node.AsObject();
        if (obj.TryGetPropertyValue("accepted", out var accepted) && accepted?.GetValue<bool>() == true) return "AC";
        if (obj.TryGetPropertyValue("bestScore", out var score)) return score?.ToString() ?? "-";
        return "-";
    }

    private void SelectCurrentProblem()
    {
        currentProblem = problemList.SelectedItems.Count == 0 ? null : problemList.SelectedItems[0].Tag as ProblemInfo;
        if (currentProblem is null) return;
        titleLabel.Text = currentProblem.Title;
        sourceLabel.Text = $"{currentProblem.Id} / {currentProblem.Source}";
        statusLabel.Text = $"当前状态：{ProblemStatus(currentProblem.Id)}";
    }

    private void RegisterAccount()
    {
        using var dialog = new AccountDialog("注册");
        if (dialog.ShowDialog(this) != DialogResult.OK) return;
        if (accounts.Any(a => a.Handle == dialog.UserHandle))
        {
            MessageBox.Show(this, "这个 Handle 已经在本机注册。", "注册失败");
            return;
        }
        var salt = Convert.ToBase64String(RandomNumberGenerator.GetBytes(16));
        currentAccount = new AccountInfo(dialog.DisplayName, dialog.UserHandle, salt, HashPassword(dialog.Password, salt));
        accounts.Add(currentAccount);
        SaveAccounts();
        SaveSession();
        SaveProfile();
        RenderAccount();
        LoadRecords();
        RenderProblems();
    }

    private void LoginAccount()
    {
        using var dialog = new AccountDialog("登录", needName: false);
        if (dialog.ShowDialog(this) != DialogResult.OK) return;
        var account = accounts.FirstOrDefault(a => a.Handle == dialog.UserHandle);
        if (account is null || HashPassword(dialog.Password, account.Salt) != account.PasswordHash)
        {
            MessageBox.Show(this, "Handle 或密码不正确。", "登录失败");
            return;
        }
        currentAccount = account;
        SaveSession();
        SaveProfile();
        LoadRecords();
        RenderAccount();
        RenderProblems();
    }

    private async Task LogoutAsync()
    {
        currentAccount = null;
        SaveSession();
        LoadRecords();
        RenderAccount();
        RenderProblems();
        await Task.CompletedTask;
    }

    private static string HashPassword(string password, string salt)
    {
        var bytes = SHA256.HashData(Encoding.UTF8.GetBytes($"{salt}:{password}"));
        return Convert.ToHexString(bytes).ToLowerInvariant();
    }

    private void ChooseSourceFile()
    {
        using var dialog = new OpenFileDialog
        {
            Filter = "C++ source (*.cpp;*.cc;*.cxx)|*.cpp;*.cc;*.cxx|All files (*.*)|*.*",
            Title = "选择提交代码"
        };
        if (dialog.ShowDialog(this) == DialogResult.OK)
            sourcePathBox.Text = dialog.FileName;
    }

    private async Task SubmitAsync()
    {
        if (currentAccount is null)
        {
            MessageBox.Show(this, "请先登录或注册本地账号。", "无法提交");
            return;
        }
        if (currentProblem is null)
        {
            MessageBox.Show(this, "请选择题目。", "无法提交");
            return;
        }
        var source = sourcePathBox.Text.Trim();
        if (!File.Exists(source))
        {
            MessageBox.Show(this, "源文件不存在。", "无法提交");
            return;
        }
        if (!File.Exists(runnerPath))
        {
            MessageBox.Show(this, "缺少 gioush-judge.ps1。", "无法提交");
            return;
        }
        SetBusy(true);
        outputBox.Text = "评测中...\r\n";
        var result = await RunJudgeAsync("run", currentProblem.Id, source);
        outputBox.Text = result;
        LoadRecords();
        RenderProblems();
        SelectCurrentProblem();
        SetBusy(false);
    }

    private async Task ExportAsync()
    {
        if (currentAccount is null || currentProblem is null) return;
        SetBusy(true);
        outputBox.Text = await RunJudgeAsync("export", currentProblem.Id, "--format", "md");
        SetBusy(false);
    }

    private async Task<string> RunJudgeAsync(params string[] args)
    {
        var psi = new ProcessStartInfo
        {
            FileName = "powershell",
            UseShellExecute = false,
            RedirectStandardOutput = true,
            RedirectStandardError = true,
            CreateNoWindow = true
        };
        psi.Environment["GIOUSH_JUDGE_HOME"] = ActiveHome();
        psi.ArgumentList.Add("-NoProfile");
        psi.ArgumentList.Add("-ExecutionPolicy");
        psi.ArgumentList.Add("Bypass");
        psi.ArgumentList.Add("-File");
        psi.ArgumentList.Add(runnerPath);
        psi.ArgumentList.Add("--manifest");
        psi.ArgumentList.Add(DefaultManifest);
        foreach (var arg in args) psi.ArgumentList.Add(arg);

        using var process = Process.Start(psi) ?? throw new InvalidOperationException("无法启动评测器。");
        var stdout = await process.StandardOutput.ReadToEndAsync();
        var stderr = await process.StandardError.ReadToEndAsync();
        await process.WaitForExitAsync();
        return stdout + (string.IsNullOrWhiteSpace(stderr) ? "" : "\r\n" + stderr);
    }

    private void SetBusy(bool busy)
    {
        submitButton.Enabled = !busy;
        exportButton.Enabled = !busy;
        chooseButton.Enabled = !busy;
        refreshButton.Enabled = !busy;
        progress.Style = busy ? ProgressBarStyle.Marquee : ProgressBarStyle.Continuous;
        progress.Value = busy ? 0 : 0;
    }
}

internal sealed class AccountDialog : Form
{
    private readonly TextBox nameBox = new();
    private readonly TextBox handleBox = new();
    private readonly TextBox passwordBox = new();

    public string DisplayName => string.IsNullOrWhiteSpace(nameBox.Text) ? handleBox.Text.Trim() : nameBox.Text.Trim();
    public string UserHandle => handleBox.Text.Trim();
    public string Password => passwordBox.Text;

    public AccountDialog(string title, bool needName = true)
    {
        Text = title;
        StartPosition = FormStartPosition.CenterParent;
        FormBorderStyle = FormBorderStyle.FixedDialog;
        MaximizeBox = false;
        MinimizeBox = false;
        ClientSize = new Size(360, needName ? 190 : 145);
        Font = new Font("Microsoft YaHei UI", 10F);

        var layout = new TableLayoutPanel
        {
            Dock = DockStyle.Fill,
            Padding = new Padding(14),
            ColumnCount = 2,
            RowCount = needName ? 4 : 3
        };
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 74));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100));
        Controls.Add(layout);

        var row = 0;
        if (needName)
        {
            layout.Controls.Add(new Label { Text = "昵称", Dock = DockStyle.Fill, TextAlign = ContentAlignment.MiddleLeft }, 0, row);
            layout.Controls.Add(nameBox, 1, row++);
        }
        layout.Controls.Add(new Label { Text = "Handle", Dock = DockStyle.Fill, TextAlign = ContentAlignment.MiddleLeft }, 0, row);
        layout.Controls.Add(handleBox, 1, row++);
        layout.Controls.Add(new Label { Text = "密码", Dock = DockStyle.Fill, TextAlign = ContentAlignment.MiddleLeft }, 0, row);
        passwordBox.UseSystemPasswordChar = true;
        layout.Controls.Add(passwordBox, 1, row++);

        var buttons = new FlowLayoutPanel { Dock = DockStyle.Fill, FlowDirection = FlowDirection.RightToLeft };
        var ok = new Button { Text = "确定", DialogResult = DialogResult.OK, Width = 86 };
        var cancel = new Button { Text = "取消", DialogResult = DialogResult.Cancel, Width = 86 };
        buttons.Controls.Add(ok);
        buttons.Controls.Add(cancel);
        layout.Controls.Add(buttons, 0, row);
        layout.SetColumnSpan(buttons, 2);

        AcceptButton = ok;
        CancelButton = cancel;
    }
}

internal sealed record ProblemInfo(string Id, string Title, string Source);
internal sealed record AccountInfo(string Name, string Handle, string Salt, string PasswordHash);
