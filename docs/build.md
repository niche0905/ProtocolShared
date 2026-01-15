### ProtocolShared 사용 규칙

이 저장소는 다음을 공유한다.

- Protobuf 스키마: `proto/*.proto`
- 패킷 프레이밍/헤더 규약(C++): `include/**`
- 기본 설정 템플릿: `config/**`

또한 서버/클라이언트는 동일한 Protobuf 소스 버전을 사용해야 한다.

- Protobuf 소스 버전은 각 프로젝트의 `External/protobuf` submodule 커밋으로 고정한다.
- 고정 기준(권장): `third_party_versions/protobuf.txt`의 `commit=<SHA>` 값

### (ServerEngine) Protobuf 빌드 방법 (Windows / VS2022)

ServerEngine은 Protobuf 소스(`External/protobuf`)를 빌드하여 아래 산출물을 사용한다.

- `protoc.exe` (코드 생성기)
- `libprotobuf.lib` (런타임 라이브러리)

사전 조건:

- Visual Studio 2022 또는 Visual Studio 2022 Build Tools (C++ 포함)
- CMake (PATH 등록 필요)
- submodule 초기화 완료:
    - `git submodule update --init --recursive`

빌드(Release):

- PowerShell:
    - `.\tools\build_protobuf.ps1` 
    보안 예외가 발생한다면
    `Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass` 를 먼저 입력하고 다시 .ps1 파일 실행
- 또는 CMake CLI 직접 실행:
    - `cmake -S External/protobuf -B External/protobuf_build -G "Visual Studio 17 2022" -A x64 -Dprotobuf_BUILD_TESTS=OFF`
    - `cmake --build External/protobuf_build --config Release --target protoc libprotobuf`

빌드 결과 위치:

- `External/protobuf_build/Release/protoc.exe`
- `External/protobuf_build/Release/libprotobuf.lib`