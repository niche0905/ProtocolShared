@echo off
setlocal EnableExtensions EnableDelayedExpansion

rem =========================================================
rem GenPacketHandlers.bat
rem - protoc / xcopy 없이 GenPackets.exe만으로 PacketHandler 생성
rem - 배치 파일 위치 기준으로 경로 계산
rem =========================================================

pushd "%~dp0"

set "PROTO_FILE=%~dp0..\..\..\proto\protocol.desc"
set "GEN_EXE=%~dp0..\..\..\bin\GenPackets.exe"
set "OUT_DIR=%~dp0..\..\..\include\Generated"
set "TEMPLATE_DIR=%~dp0..\Template"

set "CLIENT_OUT_NAME=ClientPacketHandler"
set "SERVER_OUT_NAME=ServerPacketHandler"

rem ---- sanity check ----
if not exist "%GEN_EXE%" (
    echo [ERROR] GenPackets.exe not found: "%GEN_EXE%"
    goto :FAIL
)

if not exist "%PROTO_FILE%" (
    echo [ERROR] Protocol.proto not found: "%PROTO_FILE%"
    goto :FAIL
)

if not exist "%OUT_DIR%" (
    mkdir "%OUT_DIR%" >nul 2>&1
    if errorlevel 1 (
        echo [ERROR] failed to create OUT_DIR: "%OUT_DIR%"
        goto :FAIL
    )
)

echo.
echo [INFO ] GEN_EXE    = "%GEN_EXE%"
echo [INFO ] PROTO_FILE = "%PROTO_FILE%"
echo [INFO ] OUT_DIR    = "%OUT_DIR%"
echo [INFO ] TPL_DIR    = "%TEMPLATE_DIR%"
echo.

rem =========================================================
rem (A) Client용 PacketHandler 생성
rem =========================================================
echo [BUILD] %CLIENT_OUT_NAME%.h
"%GEN_EXE%" --desc="%PROTO_FILE%" --protocol_include="Protocol.pb.h" --side=client --template=PacketHandler.j2 --template_dir="%TEMPLATE_DIR%" --out_dir="%OUT_DIR%" --name="%CLIENT_OUT_NAME%"
if errorlevel 1 (
    echo [ERROR] GenPackets client handler failed.
    goto :FAIL
)

rem =========================================================
rem (B) Server용 PacketHandler 생성
rem =========================================================
echo [BUILD] %SERVER_OUT_NAME%.h
"%GEN_EXE%" --desc="%PROTO_FILE%" --protocol_include="Protocol.pb.h" --side=server --template=PacketHandler.j2 --template_dir="%TEMPLATE_DIR%" --out_dir="%OUT_DIR%" --name="%SERVER_OUT_NAME%"
if errorlevel 1 (
    echo [ERROR] GenPackets server handler failed.
    goto :FAIL
)

echo.
echo [DONE ] Generated:
echo        "%OUT_DIR%\%CLIENT_OUT_NAME%.h"
echo        "%OUT_DIR%\%SERVER_OUT_NAME%.h"
echo.

popd
endlocal
exit /b 0

:FAIL
echo.
echo [FAIL ] PacketHandler generation failed.
popd
endlocal
pause
exit /b 1
