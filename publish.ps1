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

function Invoke-GhApiJson {
    param(
        [string] $Method,
        [string] $Path,
        [object] $Body
    )

    $tempFile = New-TemporaryFile
    try {
        $json = $Body | ConvertTo-Json -Depth 20
        $utf8NoBom = New-Object System.Text.UTF8Encoding($false)
        [IO.File]::WriteAllText($tempFile.FullName, $json, $utf8NoBom)
        $response = & $gh api -X $Method $Path --input $tempFile
        if ($LASTEXITCODE -ne 0) {
            throw "gh api $Method $Path failed with exit code $LASTEXITCODE"
        }
        return ($response | ConvertFrom-Json)
    } finally {
        Remove-Item -LiteralPath $tempFile -Force -ErrorAction SilentlyContinue
    }
}

function Publish-WithGitHubApi {
    Write-Host "Falling back to GitHub API upload..."

    $files = git -c "safe.directory=$safeDirectory" ls-files
    if ($LASTEXITCODE -ne 0) {
        throw "git ls-files failed with exit code $LASTEXITCODE"
    }

    $tree = @()
    foreach ($file in $files) {
        $fullPath = Join-Path $PSScriptRoot $file
        $content = [Convert]::ToBase64String([IO.File]::ReadAllBytes($fullPath))
        $blob = Invoke-GhApiJson "POST" "repos/$repoFullName/git/blobs" @{
            content = $content
            encoding = "base64"
        }

        $tree += @{
            path = $file.Replace("\", "/")
            mode = "100644"
            type = "blob"
            sha = $blob.sha
        }
    }

    $treeObject = Invoke-GhApiJson "POST" "repos/$repoFullName/git/trees" @{
        tree = $tree
    }

    $refText = & $gh api "repos/$repoFullName/git/ref/heads/main" 2>$null
    $refExists = ($LASTEXITCODE -eq 0)
    $parents = @()
    if ($refExists) {
        $refObject = $refText | ConvertFrom-Json
        $parents = @($refObject.object.sha)
    }

    $commit = Invoke-GhApiJson "POST" "repos/$repoFullName/git/commits" @{
        message = "Publish blog"
        tree = $treeObject.sha
        parents = $parents
    }

    if ($refExists) {
        Invoke-GhApiJson "PATCH" "repos/$repoFullName/git/refs/heads/main" @{
            sha = $commit.sha
            force = $true
        } | Out-Null
    } else {
        Invoke-GhApiJson "POST" "repos/$repoFullName/git/refs" @{
            ref = "refs/heads/main"
            sha = $commit.sha
        } | Out-Null
    }

    Invoke-GhApiJson "PATCH" "repos/$repoFullName" @{
        default_branch = "main"
    } | Out-Null
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

git -c "safe.directory=$safeDirectory" push -u origin main
if ($LASTEXITCODE -ne 0) {
    Publish-WithGitHubApi
}

$oldErrorActionPreference = $ErrorActionPreference
$ErrorActionPreference = "Continue"
& $gh api -X POST "repos/$repoFullName/pages" -f build_type=workflow *> $null
$pagesExitCode = $LASTEXITCODE
$ErrorActionPreference = $oldErrorActionPreference
if ($pagesExitCode -ne 0) {
    Write-Host "GitHub Pages may already be enabled. Continuing..."
}

Write-Host ""
Write-Host "Repository: https://github.com/$repoFullName"
Write-Host "Actions:    https://github.com/$repoFullName/actions"
Write-Host "Website:    https://$repoOwner.github.io/$repoName/"
