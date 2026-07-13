param(
    [Parameter(ValueFromRemainingArguments = $true)]
    [string[]]$Args
)

$ErrorActionPreference = "Stop"
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$DefaultManifest = "https://ehundategh.github.io/Blog/oj/problems.json"
$Port = 8765
$Manifest = $DefaultManifest
$OpenBrowser = $true

for ($i = 0; $i -lt $Args.Count; $i++) {
    if ($Args[$i] -eq "--port" -and $i + 1 -lt $Args.Count) {
        $Port = [int]$Args[++$i]
    } elseif ($Args[$i] -eq "--manifest" -and $i + 1 -lt $Args.Count) {
        $Manifest = $Args[++$i]
    } elseif ($Args[$i] -eq "--no-open") {
        $OpenBrowser = $false
    }
}

function Judge-Home {
    $path = Join-Path $env:USERPROFILE ".gioush-judge"
    New-Item -ItemType Directory -Force -Path $path | Out-Null
    return $path
}

function Safe-Name([string]$Name) {
    return ([regex]::Replace($Name, "[^A-Za-z0-9_.-]", "_"))
}

function Account-Home([string]$Handle) {
    $path = Join-Path (Join-Path (Judge-Home) "accounts") (Safe-Name $Handle)
    New-Item -ItemType Directory -Force -Path $path | Out-Null
    return $path
}

function Active-Home {
    $session = Load-Session
    if ($session.handle) {
        return Account-Home ([string]$session.handle)
    }
    return Judge-Home
}

function Accounts-Path {
    return Join-Path (Judge-Home) "accounts.json"
}

function Session-Path {
    return Join-Path (Judge-Home) "session.json"
}

function Profile-Path {
    return Join-Path (Active-Home) "profile.json"
}

function Records-Path {
    return Join-Path (Active-Home) "records.json"
}

function Read-TextOrUrl([string]$Source) {
    if ($Source -match "^https?://") {
        return (Invoke-WebRequest -UseBasicParsing -Uri $Source).Content
    }
    return [System.IO.File]::ReadAllText((Resolve-Path -LiteralPath $Source), [System.Text.Encoding]::UTF8)
}

function Read-Json-File([string]$Path, $Default) {
    if (-not (Test-Path -LiteralPath $Path)) {
        return $Default
    }
    $text = [System.IO.File]::ReadAllText($Path, [System.Text.Encoding]::UTF8)
    if ([string]::IsNullOrWhiteSpace($text)) {
        return $Default
    }
    return ($text | ConvertFrom-Json)
}

function Write-Json-File([string]$Path, $Value) {
    New-Item -ItemType Directory -Force -Path (Split-Path -Parent $Path) | Out-Null
    $json = $Value | ConvertTo-Json -Depth 80
    [System.IO.File]::WriteAllText($Path, $json, [System.Text.UTF8Encoding]::new($false))
}

function Load-Manifest {
    return (Read-TextOrUrl $Manifest | ConvertFrom-Json)
}

function Load-Accounts {
    $raw = Read-Json-File (Accounts-Path) ([pscustomobject]@{ accounts = @() })
    if (-not $raw.accounts) {
        $raw | Add-Member -NotePropertyName accounts -NotePropertyValue @() -Force
    }
    return $raw
}

function Load-Session {
    return Read-Json-File (Session-Path) ([pscustomobject]@{ handle = "" })
}

function Current-Account {
    $session = Load-Session
    if (-not $session.handle) { return $null }
    $accounts = Load-Accounts
    foreach ($account in @($accounts.accounts)) {
        if ($account.handle -eq $session.handle) { return $account }
    }
    return $null
}

function Hash-Password([string]$Password, [string]$Salt) {
    $sha = [System.Security.Cryptography.SHA256]::Create()
    $bytes = [System.Text.Encoding]::UTF8.GetBytes($Salt + ":" + $Password)
    $hash = $sha.ComputeHash($bytes)
    return ([System.BitConverter]::ToString($hash)).Replace("-", "").ToLowerInvariant()
}

function New-Salt {
    $bytes = New-Object byte[] 16
    [System.Security.Cryptography.RandomNumberGenerator]::Create().GetBytes($bytes)
    return [Convert]::ToBase64String($bytes)
}

function Read-Body($Request) {
    $text = $Request.Body
    if ([string]::IsNullOrWhiteSpace($text)) {
        return [pscustomobject]@{}
    }
    return ($text | ConvertFrom-Json)
}

function Send-Text($Response, [string]$Text, [string]$Type, [int]$Status) {
    $bytes = [System.Text.Encoding]::UTF8.GetBytes($Text)
    $reason = if ($Status -eq 200) { "OK" } elseif ($Status -eq 400) { "Bad Request" } elseif ($Status -eq 401) { "Unauthorized" } elseif ($Status -eq 403) { "Forbidden" } elseif ($Status -eq 404) { "Not Found" } elseif ($Status -eq 405) { "Method Not Allowed" } elseif ($Status -eq 409) { "Conflict" } else { "Internal Server Error" }
    $header = "HTTP/1.1 $Status $reason`r`nContent-Type: $Type; charset=utf-8`r`nContent-Length: $($bytes.Length)`r`nConnection: close`r`n`r`n"
    $headBytes = [System.Text.Encoding]::ASCII.GetBytes($header)
    $Response.Stream.Write($headBytes, 0, $headBytes.Length)
    $Response.Stream.Write($bytes, 0, $bytes.Length)
}

function Send-Json($Response, $Value, [int]$Status) {
    $json = $Value | ConvertTo-Json -Depth 80
    Send-Text $Response $json "application/json" $Status
}

function Send-Error($Response, [string]$Message, [int]$Status) {
    Send-Json $Response ([pscustomobject]@{ ok = $false; error = $Message }) $Status
}

function Content-Type([string]$Path) {
    $ext = [System.IO.Path]::GetExtension($Path).ToLowerInvariant()
    if ($ext -eq ".html") { return "text/html" }
    if ($ext -eq ".js") { return "text/javascript" }
    if ($ext -eq ".css") { return "text/css" }
    if ($ext -eq ".svg") { return "image/svg+xml" }
    return "text/plain"
}

function Send-Static($Response, [string]$Name) {
    $safe = $Name.TrimStart("/").Replace("/", [System.IO.Path]::DirectorySeparatorChar)
    if ($safe -eq "") { $safe = "index.html" }
    $path = Join-Path (Join-Path $ScriptDir "web") $safe
    $full = [System.IO.Path]::GetFullPath($path)
    $root = [System.IO.Path]::GetFullPath((Join-Path $ScriptDir "web"))
    if (-not $full.StartsWith($root)) {
        Send-Error $Response "Bad path." 400
        return
    }
    if (-not (Test-Path -LiteralPath $full)) {
        Send-Error $Response "Not found." 404
        return
    }
    Send-Text $Response ([System.IO.File]::ReadAllText($full, [System.Text.Encoding]::UTF8)) (Content-Type $full) 200
}

function Save-Profile-FromAccount($Account) {
    $profile = [pscustomobject]@{
        name = $Account.name
        handle = $Account.handle
        updatedAt = [DateTimeOffset]::UtcNow.ToString("o")
    }
    Write-Json-File (Profile-Path) $profile
}

function Api-State($Response) {
    $manifestData = Load-Manifest
    $records = Read-Json-File (Records-Path) ([pscustomobject]@{})
    $account = Current-Account
    $publicAccount = $null
    if ($account) {
        $publicAccount = [pscustomobject]@{ name = $account.name; handle = $account.handle; createdAt = $account.createdAt }
    }
    Send-Json $Response ([pscustomobject]@{
        ok = $true
        manifest = $manifestData
        account = $publicAccount
        records = $records
    }) 200
}

function Api-Register($Response, $Body) {
    if (-not $Body.name -or -not $Body.handle -or -not $Body.password) {
        Send-Error $Response "Name, handle and password are required." 400
        return
    }
    $accounts = Load-Accounts
    foreach ($account in @($accounts.accounts)) {
        if ($account.handle -eq $Body.handle) {
            Send-Error $Response "Handle already exists on this machine." 409
            return
        }
    }
    $salt = New-Salt
    $account = [pscustomobject]@{
        name = [string]$Body.name
        handle = [string]$Body.handle
        salt = $salt
        passwordHash = Hash-Password ([string]$Body.password) $salt
        createdAt = [DateTimeOffset]::UtcNow.ToString("o")
    }
    $accounts.accounts = @($accounts.accounts) + $account
    Write-Json-File (Accounts-Path) $accounts
    Write-Json-File (Session-Path) ([pscustomobject]@{ handle = $account.handle })
    Save-Profile-FromAccount $account
    Send-Json $Response ([pscustomobject]@{ ok = $true; account = [pscustomobject]@{ name = $account.name; handle = $account.handle } }) 200
}

function Api-Login($Response, $Body) {
    if (-not $Body.handle -or -not $Body.password) {
        Send-Error $Response "Handle and password are required." 400
        return
    }
    $accounts = Load-Accounts
    foreach ($account in @($accounts.accounts)) {
        if ($account.handle -eq $Body.handle) {
            $hash = Hash-Password ([string]$Body.password) ([string]$account.salt)
            if ($hash -ne $account.passwordHash) {
                Send-Error $Response "Password is incorrect." 403
                return
            }
            Write-Json-File (Session-Path) ([pscustomobject]@{ handle = $account.handle })
            Save-Profile-FromAccount $account
            Send-Json $Response ([pscustomobject]@{ ok = $true; account = [pscustomobject]@{ name = $account.name; handle = $account.handle } }) 200
            return
        }
    }
    Send-Error $Response "Handle was not found on this machine." 404
}

function Api-Logout($Response) {
    Write-Json-File (Session-Path) ([pscustomobject]@{ handle = "" })
    Send-Json $Response ([pscustomobject]@{ ok = $true }) 200
}

function Api-Run($Response, $Body) {
    $account = Current-Account
    if (-not $account) {
        Send-Error $Response "Please login first." 401
        return
    }
    if (-not $Body.problemId -or -not $Body.sourcePath) {
        Send-Error $Response "Problem id and source path are required." 400
        return
    }
    $judge = Join-Path $ScriptDir "gioush-judge.ps1"
    $oldHome = $env:GIOUSH_JUDGE_HOME
    $env:GIOUSH_JUDGE_HOME = Account-Home ([string]$account.handle)
    $output = & powershell -NoProfile -ExecutionPolicy Bypass -File $judge --manifest $Manifest run ([string]$Body.problemId) ([string]$Body.sourcePath) 2>&1
    $code = $LASTEXITCODE
    $env:GIOUSH_JUDGE_HOME = $oldHome
    Send-Json $Response ([pscustomobject]@{
        ok = ($code -eq 0)
        exitCode = $code
        output = ($output -join "`n")
    }) 200
}

function Api-Export($Response, $Body) {
    $account = Current-Account
    if (-not $account) {
        Send-Error $Response "Please login first." 401
        return
    }
    if (-not $Body.problemId) {
        Send-Error $Response "Problem id is required." 400
        return
    }
    $format = "md"
    if ($Body.format) { $format = [string]$Body.format }
    $judge = Join-Path $ScriptDir "gioush-judge.ps1"
    $oldHome = $env:GIOUSH_JUDGE_HOME
    $env:GIOUSH_JUDGE_HOME = Account-Home ([string]$account.handle)
    $output = & powershell -NoProfile -ExecutionPolicy Bypass -File $judge --manifest $Manifest export ([string]$Body.problemId) --format $format 2>&1
    $code = $LASTEXITCODE
    $env:GIOUSH_JUDGE_HOME = $oldHome
    Send-Json $Response ([pscustomobject]@{
        ok = ($code -eq 0)
        exitCode = $code
        output = ($output -join "`n")
    }) 200
}

function Handle-Request($Context) {
    $request = $Context.Request
    $response = $Context.Response
    try {
        $path = $request.Path
        if ($request.Method -eq "GET" -and $path -eq "/api/state") {
            Api-State $response
            return
        }
        if ($request.Method -eq "POST" -and $path -eq "/api/register") {
            Api-Register $response (Read-Body $request)
            return
        }
        if ($request.Method -eq "POST" -and $path -eq "/api/login") {
            Api-Login $response (Read-Body $request)
            return
        }
        if ($request.Method -eq "POST" -and $path -eq "/api/logout") {
            Api-Logout $response
            return
        }
        if ($request.Method -eq "POST" -and $path -eq "/api/run") {
            Api-Run $response (Read-Body $request)
            return
        }
        if ($request.Method -eq "POST" -and $path -eq "/api/export") {
            Api-Export $response (Read-Body $request)
            return
        }
        if ($request.Method -eq "GET") {
            Send-Static $response $path
            return
        }
        Send-Error $response "Method not allowed." 405
    } catch {
        try {
            Send-Error $response $_.Exception.Message 500
        } catch {
        }
    }
}

function Read-HttpRequest($Stream) {
    $reader = New-Object System.IO.StreamReader($Stream, [System.Text.Encoding]::UTF8, $false, 4096, $true)
    $first = $reader.ReadLine()
    if (-not $first) { return $null }
    $parts = $first.Split(" ")
    $method = $parts[0]
    $path = $parts[1]
    $headers = @{}
    while ($true) {
        $line = $reader.ReadLine()
        if ($null -eq $line -or $line -eq "") { break }
        $pos = $line.IndexOf(":")
        if ($pos -gt 0) {
            $headers[$line.Substring(0, $pos).ToLowerInvariant()] = $line.Substring($pos + 1).Trim()
        }
    }
    $body = ""
    if ($headers.ContainsKey("content-length")) {
        $length = [int]$headers["content-length"]
        if ($length -gt 0) {
            $buffer = New-Object char[] $length
            $read = $reader.Read($buffer, 0, $length)
            $body = -join $buffer[0..([Math]::Max(0, $read - 1))]
        }
    }
    return [pscustomobject]@{ Method = $method; Path = $path; Body = $body }
}

$listener = [System.Net.Sockets.TcpListener]::new([System.Net.IPAddress]::Parse("127.0.0.1"), $Port)
$prefix = "http://127.0.0.1:$Port/"
$listener.Start()
Write-Host "Gioush Judge GUI is running at $prefix"
Write-Host "Press Ctrl+C to stop."
if ($OpenBrowser) {
    Start-Process $prefix | Out-Null
}

while ($true) {
    $client = $listener.AcceptTcpClient()
    try {
        $stream = $client.GetStream()
        $request = Read-HttpRequest $stream
        if ($request) {
            $response = [pscustomobject]@{ Stream = $stream }
            Handle-Request ([pscustomobject]@{ Request = $request; Response = $response })
        }
    } finally {
        $client.Close()
    }
}
