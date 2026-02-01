from enum import Enum
from dataclasses import dataclass

class Side(Enum):
    SERVER = "server"
    CLIENT = "client"

@dataclass(frozen=True)
class Packet:
    name: str       # "se.auth.C_LoginReq" 같은 풀네임
    id: int
    dir: int        # C2S or S2c
    route: int      # 숫자 그대로(필요하면 문자열 매핑 가능)
