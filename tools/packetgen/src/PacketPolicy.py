from typing import List, Tuple
from Model import Packet, Side
from Constants import DIR_C2S, DIR_S2C

def split_packets_by_side(packets: List[Packet],side: Side) -> Tuple[List[Packet], List[Packet]]:
    recv = []
    send = []

    for p in packets:
        if side == Side.SERVER:
            if p.dir == DIR_C2S:
                recv.append(p)
            elif p.dir == DIR_S2C:
                send.append(p)

        elif side == Side.CLIENT:
            if p.dir == DIR_S2C:
                recv.append(p)
            elif p.dir == DIR_C2S:
                send.append(p)

    return recv, send
