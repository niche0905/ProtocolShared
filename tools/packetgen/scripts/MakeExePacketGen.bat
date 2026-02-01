@echo off
setlocal

rem scripts 폴더 기준
pushd "%~dp0"

rem 경로 설정 (ProtocolShared 루트)
set ROOT=%~dp0..\..\..\
for %%I in ("%ROOT%") do set ROOT=%%~fI

set OUTBIN=%ROOT%\bin
set EXENAME=GenPackets
set SPECPATH=%ROOT%\tools\packetgen\build\spec\GenPackets.spec

if not exist "%OUTBIN%" mkdir "%OUTBIN%"

rem PyInstaller 체크
python -m PyInstaller --version >nul 2>nul
if errorlevel 1 (
  echo [ERROR] PyInstaller not found for this Python. Install: pip install pyinstaller
  popd
  pause
  exit /b 1
)

rem 빌드 (SPEC 사용)
echo [BUILD] %EXENAME%.exe (using spec)
set WORKDIR=%ROOT%\tools\packetgen\build\work

python -m PyInstaller ^
  --noconfirm ^
  --clean ^
  --workpath "%ROOT%\tools\packetgen\build\work" ^
  --distpath "%ROOT%\bin" ^
  "%SPECPATH%"

if errorlevel 1 (
  echo [ERROR] PyInstaller build failed.
  popd
  pause
  exit /b 1
)

echo [DONE] "%OUTBIN%\%EXENAME%.exe"

popd
endlocal
pause
