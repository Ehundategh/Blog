$ErrorActionPreference = "Stop"

$repoOwner = "Ehundategh"
$repoName = "Blog"
$repoFullName = "$repoOwner/$repoName"
$gh = "C:\Program Files\GitHub CLI\gh.exe"

if (-not (Test-Path -LiteralPath $gh)) {
    throw "GitHub CLI not found at $gh"
}

Set-Location -LiteralPath $PSScriptRoot

git config user.name $repoOwner
git config user.email "$repoOwner@users.noreply.github.com"
git branch -M main

& $gh auth status

$repoExists = $false
try {
    & $gh repo view $repoFullName | Out-Null
    $repoExists = $true
} catch {
    $repoExists = $false
}

if (-not $repoExists) {
    & $gh repo create $repoFullName --public --source . --remote origin
} elseif (-not (git remote get-url origin 2>$null)) {
    git remote add origin "https://github.com/$repoFullName.git"
}

if (-not (git log --oneline -1 2>$null)) {
    git add .
    git commit -m "init oi wiki style blog"
}

git push -u origin main

try {
    & $gh api -X POST "repos/$repoFullName/pages" -f build_type=workflow | Out-Null
} catch {
    Write-Host "GitHub Pages may already be enabled. Continuing..."
}

Write-Host ""
Write-Host "Repository: https://github.com/$repoFullName"
Write-Host "Actions:    https://github.com/$repoFullName/actions"
Write-Host "Website:    https://$repoOwner.github.io/$repoName/"

