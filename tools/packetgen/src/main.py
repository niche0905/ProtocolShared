import argparse
from DescReader import DescReader
from Generator import Generator, GenConfig

def build_argparser():
    ap = argparse.ArgumentParser(description="Packet Generator Tool (desc-based)")
    ap.add_argument("--desc", required=True, help="Path to the descriptor set (.desc)")
    ap.add_argument("--template", default="PacketHandler.j2")
    ap.add_argument("--template_dir", default="Templates")
    ap.add_argument("--out_dir", default="Generated")
    ap.add_argument("--name", default="PacketHandler")
    return ap
    
def main():
    args = build_argparser().parse_args()
    
    reader = DescReader()
    packets = reader.read_packets(args.desc)
    
    gen = Generator(GenConfig(template_dir=args.template_dir, out_dir=args.out_dir))
    ctx = {
        "packets": packets,
        "recv_packets": [p for p in packets if p.direction == "recv"],
        "send_packets": [p for p in packets if p.direction == "send"],
        "output": args.name,
    }
    
    gen.render_to_file(args.template, f"{args.name}.h", ctx) 
    
if __name__ == "__main__":
    main()
    