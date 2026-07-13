param(
    [Parameter(ValueFromRemainingArguments = $true)]
    [string[]]$Args
)

$ErrorActionPreference = "Stop"
$DefaultManifest = "https://ehundategh.github.io/Blog/oj/problems.json"

function Judge-Home {
    if ($env:GIOUSH_JUDGE_HOME) {
        $path = $env:GIOUSH_JUDGE_HOME
    } else {
        $path = Join-Path $env:USERPROFILE ".gioush-judge"
    }
    New-Item -ItemType Directory -Force -Path $path | Out-Null
    return $path
}

function Cache-Dir {
    $path = Join-Path (Judge-Home) "cache"
    New-Item -ItemType Directory -Force -Path $path | Out-Null
    return $path
}

function Records-Path {
    return Join-Path (Judge-Home) "records.json"
}

function Profile-Path {
    return Join-Path (Judge-Home) "profile.json"
}

function Now-Iso {
    return [DateTimeOffset]::UtcNow.ToString("o")
}

function Read-TextOrUrl([string]$Source) {
    if ($Source -match "^https?://") {
        return (Invoke-WebRequest -UseBasicParsing -Uri $Source).Content
    }
    return [System.IO.File]::ReadAllText((Resolve-Path -LiteralPath $Source), [System.Text.Encoding]::UTF8)
}

function Load-Manifest([string]$Source) {
    return (Read-TextOrUrl $Source | ConvertFrom-Json)
}

function Problem-Map($Manifest) {
    $map = @{}
    foreach ($problem in $Manifest.problems) {
        $map[$problem.id] = $problem
    }
    return $map
}

function Load-Profile {
    $path = Profile-Path
    if (-not (Test-Path -LiteralPath $path)) {
        return [pscustomobject]@{ name = ""; handle = "" }
    }
    return ([System.IO.File]::ReadAllText($path, [System.Text.Encoding]::UTF8) | ConvertFrom-Json)
}

function Save-Profile($Profile) {
    $json = $Profile | ConvertTo-Json -Depth 20
    [System.IO.File]::WriteAllText((Profile-Path), $json, [System.Text.UTF8Encoding]::new($false))
}

function Load-Records {
    $path = Records-Path
    if (-not (Test-Path -LiteralPath $path)) {
        return [pscustomobject]@{}
    }
    return ([System.IO.File]::ReadAllText($path, [System.Text.Encoding]::UTF8) | ConvertFrom-Json)
}

function Save-Records($Records) {
    $json = $Records | ConvertTo-Json -Depth 40
    [System.IO.File]::WriteAllText((Records-Path), $json, [System.Text.UTF8Encoding]::new($false))
}

function Download-File([string]$Url, [string]$Dest) {
    New-Item -ItemType Directory -Force -Path (Split-Path -Parent $Dest) | Out-Null
    if ((Test-Path -LiteralPath $Dest) -and ((Get-Item -LiteralPath $Dest).Length -gt 0)) {
        return $Dest
    }
    Write-Host "Downloading $Url"
    Invoke-WebRequest -UseBasicParsing -Uri $Url -OutFile $Dest
    return $Dest
}

function Natural-Key([string]$Text) {
    return ([regex]::Replace($Text, "\d+", { param($m) $m.Value.PadLeft(12, "0") }))
}

function Collect-Cases([string]$ZipPath, [string]$ProblemId) {
    $extractDir = Join-Path (Join-Path (Cache-Dir) $ProblemId) "data"
    if (Test-Path -LiteralPath $extractDir) {
        Remove-Item -LiteralPath $extractDir -Recurse -Force
    }
    New-Item -ItemType Directory -Force -Path $extractDir | Out-Null
    Expand-Archive -LiteralPath $ZipPath -DestinationPath $extractDir -Force

    $inputs = @{}
    $answers = @{}
    Get-ChildItem -LiteralPath $extractDir -Recurse -File | ForEach-Object {
        $suffix = $_.Extension.ToLowerInvariant()
        $key = [System.IO.Path]::GetFileNameWithoutExtension($_.Name)
        if ($suffix -eq ".in") { $inputs[$key] = $_.FullName }
        if ($suffix -eq ".ans") { $answers[$key] = $_.FullName }
    }

    $cases = @()
    foreach ($key in ($inputs.Keys | Sort-Object { Natural-Key $_ })) {
        if ($answers.ContainsKey($key)) {
            $cases += [pscustomobject]@{ name = $key; input = $inputs[$key]; answer = $answers[$key] }
        }
    }
    if ($cases.Count -eq 0) {
        throw "No .in/.ans cases found in data zip."
    }
    return $cases
}

function Compile-Cpp([string]$Source, [string]$ExePath) {
    $compiler = Get-Command g++ -ErrorAction SilentlyContinue
    if ($null -eq $compiler) {
        throw "g++ was not found in PATH."
    }
    Write-Host "Compiling: g++ $Source -std=c++17 -O2 -pipe -o $ExePath"
    & $compiler.Source $Source -std=c++17 -O2 -pipe -o $ExePath
    if ($LASTEXITCODE -ne 0) {
        throw "Compile Error"
    }
    Write-Host "Compile OK"
}

function Split-Tokens-FromText([string]$Text) {
    if ([string]::IsNullOrWhiteSpace($Text)) {
        return @()
    }
    return ($Text -split "\s+" | Where-Object { $_ -ne "" })
}

function Split-Tokens-FromFile([string]$Path) {
    return Split-Tokens-FromText ([System.IO.File]::ReadAllText($Path))
}

function Compare-Output([string]$ExpectedPath, [string]$ActualText) {
    $a = Split-Tokens-FromFile $ExpectedPath
    $b = Split-Tokens-FromText $ActualText
    if ($a.Count -ne $b.Count) { return $false }
    for ($i = 0; $i -lt $a.Count; $i++) {
        if ($a[$i] -ne $b[$i]) { return $false }
    }
    return $true
}

function Run-Case([string]$Exe, $Case, $Problem, [string]$WorkRoot) {
    $caseDir = Join-Path $WorkRoot $Case.name
    New-Item -ItemType Directory -Force -Path $caseDir | Out-Null

    if ($Problem.inputFile) {
        Copy-Item -LiteralPath $Case.input -Destination (Join-Path $caseDir $Problem.inputFile) -Force
    }

    $timeoutMs = [Math]::Max(1000, [int]$Problem.timeLimitMs * 3)
    $inputText = [System.IO.File]::ReadAllText($Case.input)
    $psi = [System.Diagnostics.ProcessStartInfo]::new()
    $psi.FileName = $Exe
    $psi.WorkingDirectory = $caseDir
    $psi.UseShellExecute = $false
    $psi.RedirectStandardInput = $true
    $psi.RedirectStandardOutput = $true
    $psi.RedirectStandardError = $true
    $proc = [System.Diagnostics.Process]::Start($psi)
    $started = Get-Date
    $proc.StandardInput.Write($inputText)
    $proc.StandardInput.Close()
    if (-not $proc.WaitForExit($timeoutMs)) {
        $proc.Kill()
        return [pscustomobject]@{ case = $Case.name; result = "TLE"; timeMs = $timeoutMs }
    }
    $elapsed = [int]((Get-Date) - $started).TotalMilliseconds
    $stdout = $proc.StandardOutput.ReadToEnd()
    [void]$proc.StandardError.ReadToEnd()
    if ($proc.ExitCode -ne 0) {
        return [pscustomobject]@{ case = $Case.name; result = "RE"; timeMs = $elapsed }
    }

    $actual = $stdout
    if ($Problem.outputFile) {
        $outPath = Join-Path $caseDir $Problem.outputFile
        if (Test-Path -LiteralPath $outPath) {
            $actual = [System.IO.File]::ReadAllText($outPath)
        }
    }
    $ok = Compare-Output $Case.answer $actual
    return [pscustomobject]@{ case = $Case.name; result = $(if ($ok) { "AC" } else { "WA" }); timeMs = $elapsed }
}

function Set-RecordProperty($Object, [string]$Name, $Value) {
    $prop = $Object.PSObject.Properties[$Name]
    if ($null -eq $prop) {
        $Object | Add-Member -NotePropertyName $Name -NotePropertyValue $Value
    } else {
        $prop.Value = $Value
    }
}

function Save-Record($Problem, [string]$Source, $Results, [int]$Score) {
    $records = Load-Records
    $pid = $Problem.id
    $accepted = @($Results | Where-Object { $_.result -ne "AC" }).Count -eq 0
    $entry = [pscustomobject]@{
        time = Now-Iso
        source = $Source
        score = $Score
        result = $(if ($accepted) { "AC" } else { "Unaccepted" })
        profile = Load-Profile
        cases = @($Results)
    }

    $oldProp = $records.PSObject.Properties[$pid]
    $old = if ($null -eq $oldProp) { $null } else { $oldProp.Value }
    $submissions = @()
    if ($null -ne $old -and $old.submissions) {
        $submissions = @($old.submissions)
    }
    $submissions += $entry
    if ($submissions.Count -gt 30) {
        $submissions = $submissions[($submissions.Count - 30)..($submissions.Count - 1)]
    }

    $best = $Score
    $oldAccepted = $false
    if ($null -ne $old) {
        $best = [Math]::Max([int]$old.bestScore, $Score)
        $oldAccepted = [bool]$old.accepted
    }
    $record = [pscustomobject]@{
        title = $Problem.title
        bestScore = $best
        accepted = ($oldAccepted -or $accepted)
        lastRunAt = $entry.time
        submissions = @($submissions)
    }
    Set-RecordProperty $records $pid $record
    Save-Records $records
}

function Command-List([string]$ManifestPath) {
    $manifest = Load-Manifest $ManifestPath
    foreach ($problem in $manifest.problems) {
        "{0,-24} {1}  ({2})" -f $problem.id, $problem.title, $problem.source
    }
}

function Command-Profile([string[]]$Rest) {
    $profile = Load-Profile
    for ($i = 0; $i -lt $Rest.Count; $i++) {
        if ($Rest[$i] -eq "--name" -and $i + 1 -lt $Rest.Count) {
            $profile.name = $Rest[++$i]
        } elseif ($Rest[$i] -eq "--handle" -and $i + 1 -lt $Rest.Count) {
            $profile.handle = $Rest[++$i]
        } else {
            throw "Unknown profile argument: $($Rest[$i])"
        }
    }
    if ($Rest.Count -gt 0) {
        $profile | Add-Member -NotePropertyName updatedAt -NotePropertyValue (Now-Iso) -Force
        Save-Profile $profile
    }
    Write-Host "Profile"
    Write-Host "  name:   $($profile.name)"
    Write-Host "  handle: $($profile.handle)"
}

function Command-Records {
    $records = Load-Records
    $props = @($records.PSObject.Properties)
    if ($props.Count -eq 0) {
        Write-Host "No local records."
        return
    }
    foreach ($prop in $props) {
        $item = $prop.Value
        $mark = if ($item.accepted) { "AC" } else { [string]$item.bestScore }
        "{0,-24} {1,-4} {2}" -f $prop.Name, $mark, $item.title
    }
}

function Build-Report($Problem, $Record, $Submission) {
    return [pscustomobject]@{
        version = 3
        exportedAt = Now-Iso
        profile = $(if ($Submission.profile) { $Submission.profile } else { Load-Profile })
        problem = [pscustomobject]@{
            id = $Problem.id
            title = $Problem.title
            source = $Problem.source
            origin = $Problem.origin
            originUrl = $Problem.originUrl
            statementUrl = $Problem.statementUrl
        }
        record = [pscustomobject]@{
            bestScore = $Record.bestScore
            accepted = $Record.accepted
            lastRunAt = $Record.lastRunAt
        }
        submission = $Submission
    }
}

function Report-Markdown($Report) {
    $p = $Report.profile
    $problem = $Report.problem
    $sub = $Report.submission
    $name = if ($p.name) { $p.name } else { "-" }
    $handle = if ($p.handle) { $p.handle } else { "-" }
    $source = if ($problem.source) { $problem.source } else { "-" }
    $tick = [char]96
    $lines = @(
        "# Gioush Judge Report",
        "",
        "- Player: $name",
        "- Handle: $handle",
        ("- Problem: " + $problem.title + " (" + $tick + $problem.id + $tick + ")"),
        "- Contest: $source"
    )
    if ($problem.origin) {
        if ($problem.originUrl) {
            $lines += "- Origin: [$($problem.origin)]($($problem.originUrl))"
        } else {
            $lines += "- Origin: $($problem.origin)"
        }
    }
    $lines += @(
        "- Submitted at: $($sub.time)",
        ("- Source: " + $tick + $sub.source + $tick),
        "- Result: $($sub.result)",
        "- Score: $($sub.score) / 100",
        "",
        "| Case | Result | Time |",
        "| --- | --- | --- |"
    )
    foreach ($case in $sub.cases) {
        $lines += ("| " + $tick + $case.case + $tick + " | " + $case.result + " | " + $case.timeMs + " ms |")
    }
    $lines += ""
    $lines += "This report is generated by the local judge and is only for self-practice records."
    return ($lines -join "`n")
}

function Command-Export([string]$ManifestPath, [string[]]$Rest) {
    if ($Rest.Count -lt 1) { throw "Usage: export <problem_id> [--format md|json] [--out path]" }
    $problemId = $Rest[0]
    $format = "md"
    $out = $null
    for ($i = 1; $i -lt $Rest.Count; $i++) {
        if ($Rest[$i] -eq "--format" -and $i + 1 -lt $Rest.Count) {
            $format = $Rest[++$i]
        } elseif ($Rest[$i] -eq "--out" -and $i + 1 -lt $Rest.Count) {
            $out = $Rest[++$i]
        } else {
            throw "Unknown export argument: $($Rest[$i])"
        }
    }
    $manifest = Load-Manifest $ManifestPath
    $problems = Problem-Map $manifest
    if (-not $problems.ContainsKey($problemId)) { throw "Unknown problem id: $problemId" }
    $records = Load-Records
    $prop = $records.PSObject.Properties[$problemId]
    if ($null -eq $prop) { throw "No local record for $problemId" }
    $record = $prop.Value
    $submissions = @($record.submissions)
    if ($submissions.Count -eq 0) { throw "No submissions for $problemId" }
    $report = Build-Report $problems[$problemId] $record $submissions[-1]
    if ($format -eq "json") {
        $text = $report | ConvertTo-Json -Depth 40
        $suffix = ".json"
    } elseif ($format -eq "md") {
        $text = Report-Markdown $report
        $suffix = ".md"
    } else {
        throw "Unknown format: $format"
    }
    if (-not $out) {
        $out = Join-Path (Join-Path (Judge-Home) "exports") ($problemId + $suffix)
    }
    New-Item -ItemType Directory -Force -Path (Split-Path -Parent $out) | Out-Null
    [System.IO.File]::WriteAllText($out, $text, [System.Text.UTF8Encoding]::new($false))
    Write-Host $out
}

function Command-Run([string]$ManifestPath, [string[]]$Rest) {
    if ($Rest.Count -lt 2) { throw "Usage: run <problem_id> <source.cpp>" }
    $problemId = $Rest[0]
    $source = (Resolve-Path -LiteralPath $Rest[1]).Path
    $manifest = Load-Manifest $ManifestPath
    $problems = Problem-Map $manifest
    if (-not $problems.ContainsKey($problemId)) { throw "Unknown problem id: $problemId" }
    $problem = $problems[$problemId]
    Write-Host "$($problem.title) / $($problem.id)"
    $zipName = $problem.id + ".zip"
    $zipPath = Join-Path (Join-Path (Cache-Dir) $problem.id) $zipName
    Download-File $problem.dataUrl $zipPath | Out-Null
    $cases = Collect-Cases $zipPath $problem.id
    $workRoot = Join-Path ([System.IO.Path]::GetTempPath()) ("gioush-judge-" + [Guid]::NewGuid().ToString("N"))
    New-Item -ItemType Directory -Force -Path $workRoot | Out-Null
    try {
        $exe = Join-Path $workRoot "main.exe"
        Compile-Cpp $source $exe
        $results = @()
        $idx = 1
        foreach ($case in $cases) {
            $result = Run-Case $exe $case $problem $workRoot
            $results += $result
            "#{0,-3} {1,-3} {2}ms  {3}" -f $idx, $result.result, $result.timeMs, $case.name
            $idx++
        }
    } finally {
        if (Test-Path -LiteralPath $workRoot) {
            Remove-Item -LiteralPath $workRoot -Recurse -Force
        }
    }
    $scoreEach = if ($problem.tests.scoreEach) { [int]$problem.tests.scoreEach } else { [int](100 / [Math]::Max(1, $results.Count)) }
    $score = 0
    foreach ($item in $results) {
        if ($item.result -eq "AC") { $score += $scoreEach }
    }
    $score = [Math]::Min($score, 100)
    $accepted = @($results | Where-Object { $_.result -ne "AC" }).Count -eq 0
    Write-Host ""
    Write-Host "Score: $score / 100"
    Write-Host ("Result: " + $(if ($accepted) { "Accepted" } else { "Unaccepted" }))
    Save-Record $problem $source $results $score
}

function Print-Help {
    Write-Host "Gioush Judge Windows"
    Write-Host "Usage:"
    Write-Host "  gioush-judge.cmd list"
    Write-Host "  gioush-judge.cmd run <problem_id> <source.cpp>"
    Write-Host "  gioush-judge.cmd records"
    Write-Host "  gioush-judge.cmd profile [--name name] [--handle handle]"
    Write-Host "  gioush-judge.cmd export <problem_id> [--format md|json] [--out path]"
    Write-Host "Options:"
    Write-Host "  --manifest <path-or-url>"
}

try {
    $manifest = $DefaultManifest
    $rest = @($Args)
    if ($rest.Count -ge 2 -and $rest[0] -eq "--manifest") {
        $manifest = $rest[1]
        if ($rest.Count -gt 2) {
            $rest = @($rest[2..($rest.Count - 1)])
        } else {
            $rest = @()
        }
    }
    if ($rest.Count -eq 0) {
        Print-Help
        exit 0
    }
    $command = $rest[0]
    $tail = @()
    if ($rest.Count -gt 1) { $tail = @($rest[1..($rest.Count - 1)]) }

    switch ($command) {
        "list" { Command-List $manifest }
        "run" { Command-Run $manifest $tail }
        "records" { Command-Records }
        "profile" { Command-Profile $tail }
        "export" { Command-Export $manifest $tail }
        default {
            Print-Help
            throw "Unknown command: $command"
        }
    }
} catch {
    Write-Error $_.Exception.Message
    exit 1
}
