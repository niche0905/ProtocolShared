# DescReader.py
from dataclasses import dataclass
from typing import List, Optional, Tuple
from google.protobuf import descriptor_pb2

# packet_options.proto에서 정의한 extension field numbers
FIELD_PACKET_ID = 50001
FIELD_DIR       = 50002
FIELD_ROUTE     = 50003

# dir enum 값 (packet_options.proto 기준)
DIR_C2S = 1
DIR_S2C = 2

@dataclass(frozen=True)
class Packet:
    name: str          # "se.auth.C_LoginReq" 같은 풀네임
    id: int
    direction: str     # "recv" | "send"
    route: int         # 숫자 그대로(필요하면 문자열 매핑 가능)

def _read_varint(buf: bytes, i: int) -> Tuple[int, int]:
    """return (value, next_index)"""
    shift = 0
    value = 0
    while True:
        b = buf[i]
        i += 1
        value |= (b & 0x7F) << shift
        if (b & 0x80) == 0:
            return value, i
        shift += 7

def _parse_options_varints(options_bytes: bytes) -> dict:
    """
    Protobuf wire parse (varint only) for MessageOptions.
    Returns dict[field_number] = value.
    """
    i = 0
    out = {}
    n = len(options_bytes)

    while i < n:
        tag, i = _read_varint(options_bytes, i)
        field_no = tag >> 3
        wire_ty = tag & 0x7

        if wire_ty == 0:  # varint
            val, i = _read_varint(options_bytes, i)
            out[field_no] = val
        elif wire_ty == 2:  # length-delimited (skip)
            length, i = _read_varint(options_bytes, i)
            i += length
        elif wire_ty == 5:  # 32-bit (skip)
            i += 4
        elif wire_ty == 1:  # 64-bit (skip)
            i += 8
        else:
            # unknown wire type -> stop safely
            break

    return out

class DescReader:
    def read_packets(self, desc_path: str) -> List[Packet]:
        fds = descriptor_pb2.FileDescriptorSet()
        with open(desc_path, "rb") as f:
            fds.ParseFromString(f.read())

        packets: List[Packet] = []

        for f in fds.file:
            pkg = f.package  # e.g., "se.auth"
            for msg in f.message_type:
                full_name = f"{pkg}.{msg.name}" if pkg else msg.name

                opt_bytes = msg.options.SerializeToString()
                if not opt_bytes:
                    continue

                opts = _parse_options_varints(opt_bytes)

                if FIELD_PACKET_ID not in opts:
                    continue  # 패킷이 아닌 메시지

                packet_id = int(opts.get(FIELD_PACKET_ID))
                dir_val   = int(opts.get(FIELD_DIR, 0))
                route_val = int(opts.get(FIELD_ROUTE, 0))

                if dir_val == DIR_C2S:
                    direction = "recv"  # 서버가 받는 패킷
                elif dir_val == DIR_S2C:
                    direction = "send"  # 서버가 보내는 패킷
                else:
                    continue

                packets.append(Packet(
                    name=full_name,
                    id=packet_id,
                    direction=direction,
                    route=route_val,
                ))

        # id 중복 검증
        seen = {}
        for p in packets:
            if p.id in seen:
                raise RuntimeError(f"Duplicate packet_id: {p.id} ({seen[p.id]} vs {p.name})")
            seen[p.id] = p.name

        packets.sort(key=lambda p: p.id)
        return packets
