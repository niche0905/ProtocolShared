# ProtocolShared

Server / Client 간 네트워크 프로토콜, 패킷 프레이밍, 공통 설정 파일을 공유하기 위한 저장소입니다.  
이 레포는 **독립 실행 목적이 없으며**, 각 프로젝트(ServerEngine, Client 등)에서 **Git Submodule** 형태로 사용됩니다.

---

## 📁 Repository Structure

### include/
- `ExFraming.h` : 네트워크 패킷 공통 헤더 구조
- `ExPacketIds.h` : 서버/클라가 공유하는 PacketId 정의
- `ExProtocolVersion.h` : 프로토콜 버전, 매직넘버

### proto/
- `ExProtocol.proto` : Protobuf 메시지 정의
- **.pb.cc / .pb.h 는 이 레포에 포함하지 않음**
  - 각 프로젝트에서 빌드 시점에 생성

### config/
- `ExCommon.ini` : 서버/클라이언트 공통 설정
- `ExServer.ini` : 서버 설정 템플릿
- `ExClient.ini` : 클라이언트 설정 템플릿  
> 이 파일들은 **템플릿 용도**이며, 실제 배포/개발 환경 값은 각 프로젝트에서 별도의 `.local.ini` 형태로 관리하는 것을 권장합니다.

---

## 🧩 How to Use (as Submodule)

ServerEngine 프로젝트에서:

```bash
git submodule add https://github.com/niche0905/ProtocolShared External/ProtocolShared
git commit -m "Add ProtocolShared submodule"
```

또는 clone 시
```bash
git clone --recurse-submodules <ServerEngine>
# or
git submodule update --init --recursive
```

# Update Workflow
이 저장소는 단독으로 수정하지 않습니다.
항상 부모 프로젝트(ServerEngine / Client) 에서 submodule로 수정합니다.

변경 절차
1. ServerEngine 레포에서
```bash
External/ProtocolShared
```
내부 파일 수정
2. ProtocolShared 레포에 커밋 + 푸시
3. ServerEngine 루트로 돌아와서
```bash
git add External/ProtocolShared
git commit -m "Update ProtocolShared"
git push
```
ProtocolShared 커밋 + ServerEngine 포인터 커밋