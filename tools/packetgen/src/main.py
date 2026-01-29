import argparse
from ProtoReader import ProtoReader
from Generator import Generator, GenConfig

def build_argparser():
    ap = argparse.ArgumentParser(description="Packet Generator Tool")
    ap.add_argument("--proto", required=True, help="Path to the .proto file")
    ap.add_argument("--start_id", type=int, default=1000)
    ap.add_argument("--recv", default="C_")
    ap.add_argument("--send", default="S_")
    ap.add_argument("--template", default="PacketHandler.j2")
    ap.add_argument("--template_dir", default="Templates")
    ap.add_argument("--out_dir", default="Generated")
    ap.add_argument("--name", default="PacketHandler")
    return ap
    
def main():
    args = build_argparser().parse_args()
    
    reader = ProtoReader(args.start_id, args.recv, args.send)
    packets = reader.read_packets(args.proto)
    
    gen = Generator(GenConfig(template_dir=args.template_dir, out_dir=args.out_dir))
    ctx = {
        "packets": packets,
        "recv_packets": [p for p in packets if p.direction == "recv"],
        "send_packets": [p for p in packets if p.direction == "send"],
        "output": args.name,
        "start_id": args.start_id,
        "recv_prefix": args.recv,
        "send_prefix": args.send,
    }
    
    # TODO: Template 파일도 명령행 인자로 받도록 수정 (PacketHandler.tpl)
    gen.render(args.template, f"{args.name}.h", ctx) 
    
if __name__ == "__main__":
    main()
    