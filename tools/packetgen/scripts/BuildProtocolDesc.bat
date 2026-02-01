@echo off
setlocal

rem ================================
rem BuildProtocolDesc.bat
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
set DESC_OUT=%PROTO_DIR%\protocol.desc

set PROTOC=%ENGINE_ROOT%\External\protobuf_build\Release\protoc.exe
set PB_SRC=%ENGINE_ROOT%\External\protobuf\src

if not exist "%OUT_CPP_DIR%" (
    mkdir "%OUT_CPP_DIR%"
)

echo [BUILD] Protocol.proto -> CPP + DESC
echo [INFO ] PROTO_DIR = %PROTO_DIR%
echo [INFO ] OUT_CPP   = %OUT_CPP_DIR%
echo [INFO ] DESC_OUT  = %DESC_OUT%
echo [INFO ] PROTOC    = %PROTOC%
echo.

if not exist "%PROTOC%" (
    echo [ERROR] protoc not found:
    echo         %PROTOC%
    pause
    goto END
)

if not exist "%PB_SRC%\google\protobuf\descriptor.proto" (
    echo [ERROR] descriptor.proto not found:
    echo         %PB_SRC%
    pause
    goto END
)

echo [BUILD] Running protoc...
"%PROTOC%" -I "%PROTO_DIR%" -I "%PB_SRC%" ^
    --cpp_out="%OUT_CPP_DIR%" ^
    --descriptor_set_out="%DESC_OUT%" ^
    --include_imports ^
    "%PROTO_DIR%\Protocol.proto"

if errorlevel 1 (
    echo [ERROR] protoc failed.
    pause
    goto END
)

echo.
echo [DONE] Protocol build success
echo   CPP  : %OUT_CPP_DIR%
echo   DESC : %DESC_OUT%

:END
popd
endlocal
pause
