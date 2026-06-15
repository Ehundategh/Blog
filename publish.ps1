$ErrorActionPreference = "Stop"

$repoOwner = "Ehundategh"
$repoName = "Blog"
$repoFullName = "$repoOwner/$repoName"
$gh = "C:\Program Files\GitHub CLI\gh.exe"

if (-not (Test-Path -LiteralPath $gh)) {
    throw "GitHub CLI not found at $gh"
}

Set-Location -LiteralPath $PSScriptRoot

$safeDirectory = (Resolve-Path -LiteralPath $PSScriptRoot).Path.Replace("\", "/")
git config --global --add safe.directory $safeDirectory

function Invoke-Git {
    git -c "safe.directory=$safeDirectory" @args
    if ($LASTEXITCODE -ne 0) {
        throw "git $args failed with exit code $LASTEXITCODE"
    }
}

Invoke-Git config user.name $repoOwner
Invoke-Git config user.email "$repoOwner@users.noreply.github.com"
Invoke-Git branch -M main

& $gh auth status
if ($LASTEXITCODE -ne 0) {
    throw "GitHub CLI is not authenticated."
}

$oldErrorActionPreference = $ErrorActionPreference
$ErrorActionPreference = "Continue"
& $gh repo create $repoFullName --public --source . --remote origin
$createExitCode = $LASTEXITCODE
$ErrorActionPreference = $oldErrorActionPreference

if ($createExitCode -ne 0) {
    Write-Host "Repository may already exist. Ensuring origin remote is configured..."
}

git -c "safe.directory=$safeDirectory" remote get-url origin *> $null
if ($LASTEXITCODE -ne 0) {
    Invoke-Git remote add origin "https://github.com/$repoFullName.git"
}

git -c "safe.directory=$safeDirectory" log --oneline -1 *> $null
if ($LASTEXITCODE -ne 0) {
    Invoke-Git add .
    Invoke-Git commit -m "init oi wiki style blog"
}

Invoke-Git push -u origin main

& $gh api -X POST "repos/$repoFullName/pages" -f build_type=workflow *> $null
if ($LASTEXITCODE -ne 0) {
    Write-Host "GitHub Pages may already be enabled. Continuing..."
}

Write-Host ""
Write-Host "Repository: https://github.com/$repoFullName"
Write-Host "Actions:    https://github.com/$repoFullName/actions"
Write-Host "Website:    https://$repoOwner.github.io/$repoName/"
