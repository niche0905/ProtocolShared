$ErrorActionPreference = "Stop"

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$Root = Resolve-Path (Join-Path $ScriptDir "..\..\..")

$OutBin = Join-Path $Root "bin"
$ExeBaseName = "GenPackets"
$SpecPath = Join-Path $Root "tools\packetgen\build\spec\GenPackets_debug.spec"

if (!(Test-Path $OutBin)) {
  New-Item -ItemType Directory -Path $OutBin | Out-Null
}

# PyInstaller 체크
python -m PyInstaller --version *> $null
if ($LASTEXITCODE -ne 0) {
  throw "PyInstaller not found for this Python. Install: pip install pyinstaller"
}

Write-Host "[BUILD] $ExeBaseName.exe (using spec)"
$WorkDir = Join-Path $Root "tools\packetgen\build\work"

python -m PyInstaller `
  --noconfirm `
  --clean `
  --workpath $WorkDir `
  $SpecPath

if ($LASTEXITCODE -ne 0) {
  throw "PyInstaller build failed."
}

$Target = Join-Path $OutBin "$ExeBaseName.exe"
Write-Host "[DONE] $Target"
