@echo off
setlocal

rem ================================
rem BuildProtoAll.bat
rem ================================

pushd "%~dp0"

rem --- ProtocolShared 루트 ---
set ROOT=%~dp0..\..\..\
for %%I in ("%ROOT%") do set ROOT=%%~fI

rem --- ServerEngine 루트 ---
set ENGINE_ROOT=%ROOT%\..\..
for %%I in ("%ENGINE_ROOT%") do set ENGINE_ROOT=%%~fI

rem --- 경로 설정 ---
set PROTO_DIR=%ROOT%\proto
set OUT_CPP_DIR=%ROOT%\cpp
set PROTOC=%ENGINE_ROOT%\External\protobuf_build\Release\protoc.exe
set PB_SRC=%ENGINE_ROOT%\External\protobuf\src

if not exist "%OUT_CPP_DIR%" (
    mkdir "%OUT_CPP_DIR%"
)

echo [BUILD] All proto -> CPP
echo [INFO ] PROTO_DIR = %PROTO_DIR%
echo [INFO ] OUT_CPP   = %OUT_CPP_DIR%
echo [INFO ] PROTOC    = %PROTOC%
echo.

if not exist "%PROTOC%" (
    echo [ERROR] protoc not found:
    echo         %PROTOC%
    pause
    goto END
)

for /r "%PROTO_DIR%" %%F in (*.proto) do (
    echo [PROTO] %%F
    "%PROTOC%" -I "%PROTO_DIR%" -I "%PB_SRC%" --cpp_out="%OUT_CPP_DIR%" "%%F"
    if errorlevel 1 (
        echo [ERROR] Failed to compile:
        echo         %%F
        pause
        goto END
    )
)

echo.
echo [DONE] All proto compiled successfully

:END
popd
endlocal
pause
