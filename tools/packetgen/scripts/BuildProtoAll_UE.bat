@echo off
setlocal

rem ================================
rem BuildProtoAll_UE.bat
rem - Generate protobuf C++ for Unreal Engine
rem - Adds dllexport_decl=PROTOCOLSHAREDUE_API
rem ================================

pushd "%~dp0"

set ROOT=%~dp0..\..\..\
for %%I in ("%ROOT%") do set ROOT=%%~fI

set UE_ROOT=%ROOT%\..\..

rem --- 경로 설정 ---
set PROTO_DIR=%ROOT%\proto
set OUT_CPP_DIR=%UE_ROOT%\Source\ProtocolSharedUE\Private\Generated

set PROTOC=%UE_ROOT%\External\ProtobufBuild\Win64\bin\protoc.exe
set PB_SRC=%UE_ROOT%\External\protobuf\src

echo [BUILD] All proto -> UE CPP (dllexport_decl=PROTOCOLSHAREDUE_API)
echo [INFO ] PROTO_DIR  = %PROTO_DIR%
echo [INFO ] OUT_CPP    = %OUT_CPP_DIR%
echo [INFO ] PROTOC     = %PROTOC%
echo.

if not exist "%PROTOC%" (
    echo [ERROR] protoc not found:
    echo         %PROTOC%
    pause
    goto END
)

if exist "%OUT_CPP_DIR%" (
    echo [CLEAN] %OUT_CPP_DIR%
    rmdir /s /q "%OUT_CPP_DIR%"
)
mkdir "%OUT_CPP_DIR%" >nul 2>&1

for /r "%PROTO_DIR%" %%F in (*.proto) do (
    echo [PROTO] %%F
    "%PROTOC%" -I "%PROTO_DIR%" -I "%PB_SRC%" --cpp_out=dllexport_decl=PROTOCOLSHAREDUE_API:"%OUT_CPP_DIR%" "%%F"
    if errorlevel 1 (
        echo [ERROR] Failed to compile:
        echo         %%F
        pause
        goto END
    )
)

echo.
echo [DONE] UE proto compiled successfully

:END
popd
endlocal
pause