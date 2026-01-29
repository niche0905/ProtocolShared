$ErrorActionPreference = "Stop"

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$Root = Resolve-Path (Join-Path $ScriptDir "..\..\..")

# 엔트리포인트를 main.py로 통일
$Src = Join-Path $Root "tools\packetgen\src\main.py"
$OutBin = Join-Path $Root "bin"
$ExeBaseName = "GenPackets"   # --name에는 확장자 없이 주는 게 일반적

if (!(Test-Path $OutBin)) {
  New-Item -ItemType Directory -Path $OutBin | Out-Null
}

# PyInstaller가 이 Python에 설치되어 있는지 확인 (PATH 의존 X)
python -m PyInstaller --version *> $null
if ($LASTEXITCODE -ne 0) {
  throw "PyInstaller not found for this Python. Install: pip install pyinstaller"
}

Write-Host "[BUILD] $ExeBaseName.exe"

python -m PyInstaller `
  --noconfirm `
  --clean `
  --onefile `
  --name $ExeBaseName `
  --distpath $OutBin `
  --workpath (Join-Path $Root "tools\packetgen\build\work") `
  --specpath (Join-Path $Root "tools\packetgen\build\spec") `
  $Src

if ($LASTEXITCODE -ne 0) {
  throw "PyInstaller build failed."
}

$Target = Join-Path $OutBin "$ExeBaseName.exe"
Write-Host "[DONE] $Target"
