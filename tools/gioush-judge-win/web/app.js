const state = {
  manifest: { problems: [] },
  account: null,
  records: {}
};

const $ = (id) => document.getElementById(id);

async function api(path, options = {}) {
  const res = await fetch(path, {
    headers: { "Content-Type": "application/json" },
    ...options
  });
  const data = await res.json();
  if (!data.ok) throw new Error(data.error || "Request failed");
  return data;
}

function formData(form) {
  return Object.fromEntries(new FormData(form).entries());
}

function recordFor(id) {
  return state.records && state.records[id] ? state.records[id] : null;
}

function renderAccount() {
  const box = $("accountBox");
  if (!state.account) {
    box.innerHTML = `<span class="status-dot"></span><span>未登录</span>`;
    return;
  }
  box.innerHTML = `
    <span class="status-dot on"></span>
    <span>${state.account.name}</span>
    <strong>${state.account.handle}</strong>
    <button id="logoutBtn" class="small">退出</button>
  `;
  $("logoutBtn").onclick = async () => {
    await api("/api/logout", { method: "POST", body: "{}" });
    await loadState();
  };
}

function renderProblems() {
  const select = $("problemSelect");
  const cards = $("problemCards");
  select.innerHTML = "";
  cards.innerHTML = "";
  let accepted = 0;
  for (const problem of state.manifest.problems) {
    const record = recordFor(problem.id);
    if (record && record.accepted) accepted++;
    const option = document.createElement("option");
    option.value = problem.id;
    option.textContent = `${problem.id} - ${problem.title}`;
    select.appendChild(option);

    const card = document.createElement("article");
    card.className = "card";
    card.innerHTML = `
      <div class="card-title">
        <strong>${problem.title}</strong>
        <span class="${record && record.accepted ? "tag ac" : "tag"}">${record && record.accepted ? "AC" : (record ? record.bestScore : "未评测")}</span>
      </div>
      <p>${problem.source}</p>
      <code>${problem.id}</code>
    `;
    card.onclick = () => {
      select.value = problem.id;
      window.scrollTo({ top: 0, behavior: "smooth" });
    };
    cards.appendChild(card);
  }
  $("counter").textContent = `${accepted} / ${state.manifest.problems.length}`;
}

function renderRecords() {
  const records = $("records");
  const entries = Object.entries(state.records || {});
  if (!entries.length) {
    records.innerHTML = `<p class="hint">还没有本地评测记录。</p>`;
    return;
  }
  records.innerHTML = entries.map(([id, item]) => `
    <div class="record">
      <div>
        <strong>${item.title || id}</strong>
        <span>${id}</span>
      </div>
      <b class="${item.accepted ? "ok" : ""}">${item.accepted ? "AC" : item.bestScore}</b>
    </div>
  `).join("");
}

async function loadState() {
  const data = await api("/api/state");
  state.manifest = data.manifest;
  state.account = data.account;
  state.records = data.records || {};
  renderAccount();
  renderProblems();
  renderRecords();
}

function setBusy(busy) {
  $("runBtn").disabled = busy;
  $("exportBtn").disabled = busy;
  $("progressBar").style.width = busy ? "72%" : "0";
}

document.querySelectorAll(".tab").forEach((tab) => {
  tab.onclick = () => {
    document.querySelectorAll(".tab").forEach((x) => x.classList.remove("active"));
    tab.classList.add("active");
    $("loginForm").classList.toggle("hidden", tab.dataset.tab !== "login");
    $("registerForm").classList.toggle("hidden", tab.dataset.tab !== "register");
  };
});

$("loginForm").onsubmit = async (event) => {
  event.preventDefault();
  try {
    await api("/api/login", { method: "POST", body: JSON.stringify(formData(event.target)) });
    await loadState();
  } catch (err) {
    $("output").textContent = err.message;
  }
};

$("registerForm").onsubmit = async (event) => {
  event.preventDefault();
  try {
    await api("/api/register", { method: "POST", body: JSON.stringify(formData(event.target)) });
    await loadState();
  } catch (err) {
    $("output").textContent = err.message;
  }
};

$("refreshBtn").onclick = loadState;

$("runBtn").onclick = async () => {
  const problemId = $("problemSelect").value;
  const sourcePath = $("sourcePath").value.trim();
  if (!sourcePath) {
    $("output").textContent = "请填写源文件路径。";
    return;
  }
  setBusy(true);
  $("output").textContent = "评测中...";
  try {
    const data = await api("/api/run", {
      method: "POST",
      body: JSON.stringify({ problemId, sourcePath })
    });
    $("output").textContent = data.output || "Done.";
    await loadState();
  } catch (err) {
    $("output").textContent = err.message;
  } finally {
    setBusy(false);
  }
};

$("exportBtn").onclick = async () => {
  const problemId = $("problemSelect").value;
  try {
    const data = await api("/api/export", {
      method: "POST",
      body: JSON.stringify({ problemId, format: "md" })
    });
    $("output").textContent = data.output || "Exported.";
  } catch (err) {
    $("output").textContent = err.message;
  }
};

loadState().catch((err) => {
  $("output").textContent = err.message;
});
