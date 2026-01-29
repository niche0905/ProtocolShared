@echo off
setlocal

rem scripts 폴더 기준
pushd "%~dp0"

rem 경로 설정 (ProtocolShared 루트)
set ROOT=%~dp0..\..\..\
for %%I in ("%ROOT%") do set ROOT=%%~fI

set SRC=%ROOT%\tools\packetgen\src
set OUTBIN=%ROOT%\bin
set EXENAME=GenPackets

if not exist "%OUTBIN%" mkdir "%OUTBIN%"

rem PyInstaller 체크 (PATH에 pyinstaller 없어도 됨)
python -m PyInstaller --version >nul 2>nul
if errorlevel 1 (
  echo [ERROR] PyInstaller not found for this Python. Install: pip install pyinstaller
  popd
  exit /b 1
)

rem 빌드
echo [BUILD] %EXENAME%.exe
python -m PyInstaller ^
  --noconfirm ^
  --clean ^
  --onefile ^
  --name "%EXENAME%" ^
  --distpath "%OUTBIN%" ^
  --workpath "%ROOT%\tools\packetgen\build\work" ^
  --specpath "%ROOT%\tools\packetgen\build\spec" ^
  "%SRC%\main.py"

if errorlevel 1 (
  echo [ERROR] PyInstaller build failed.
  popd
  exit /b 1
)

echo [DONE] "%OUTBIN%\%EXENAME%.exe"

popd
endlocal
pause
