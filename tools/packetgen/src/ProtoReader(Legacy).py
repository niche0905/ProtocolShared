import re
from dataclasses import dataclass
from pathlib import Path
from typing import List

MESSAGE_RE = re.compile(r'^\s*message\s+([A-Za-z_]\w*)\s*\{')

# @dataclass(frozen=True)
# class Packet:
#     name: str
#     id: int
#     direction: str # "recv" | "send" | "unknown"
    
class ProtoReader:
    def __init__(self, start_id: int, recv_prefix: str, send_prefix: str):
        self.start_id = start_id
        self.recv_prefix = recv_prefix
        self.send_prefix = send_prefix
        
    def read_packets(self, proto_path: str) -> List[Packet]:
        text = Path(proto_path).read_text(encoding='utf-8', errors='ignore').splitlines()
        
        packets: List[Packet] = []
        next_id = self.start_id
        
        brace_depth = 0
        for line in text:
            # depth 추적 (최상의 message만 추출하기 위함)
            brace_depth += line.count('{') - line.count('}')
            # NOTE: 이 방식은 완전하지 않음
            
            m = MESSAGE_RE.mathch(line)
            if not m:
                continue
                
            name = m.group(1).upper()
            
            if name.startwith(self.recv_prefix):
                direction = "recv"
            elif name.startwith(self.send_prefix):
                direction = "send"
            else:
                direction = "unknown"
                
            if direction == "unknown":
                continue
                
            pakcets.append(Packet(name=name, id=next_id, direction=direction))
            next_id += 1
        
        return packets
