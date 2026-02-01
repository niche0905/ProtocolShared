import argparse
from DescReader import DescReader
from Generator import Generator, GenConfig
from Model import Side
from PacketPolicy import split_packets_by_side

def build_argparser():
    ap = argparse.ArgumentParser(
        description="Packet Generator Tool (desc-based)"
    )

    ap.add_argument(
        "--desc",
        required=True,
        help="Path to the descriptor set (.desc)"
    )
    ap.add_argument(
        "--protocol_include",
        required=True,
        default="Protocol.pb.h",
        help="Protocol include path"
    )
    ap.add_argument(
        "--side",
        required=True,
        choices=["server", "client"],
        help="Target side to generate packet handler for"
    )
    ap.add_argument(
        "--template",
        default="PacketHandler.j2"
    )
    ap.add_argument(
        "--template_dir",
        default="Templates"
    )
    ap.add_argument(
        "--out_dir",
        default="Generated"
    )
    ap.add_argument(
        "--name",
        default="PacketHandler"
    )

    return ap
    
def main():
    args = build_argparser().parse_args()
    
    side = Side(args.side)
    packets = DescReader().read_packets(args.desc)
    
    recv_packets, send_packets = split_packets_by_side(packets, side)
    
    gen = Generator(GenConfig(template_dir=args.template_dir, out_dir=args.out_dir))
    ctx = {
        "protocol_include": args.protocol_include,
        "packets": packets,
        "recv_packets": recv_packets,
        "send_packets": send_packets,
        "output": args.name,
        "side": side.value,
    }
    
    gen.render_to_file(args.template, f"{args.name}.h", ctx) 
    
if __name__ == "__main__":
    main()
    