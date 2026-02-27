from dataclasses  import dataclass
from pathlib import Path
import jinja2

def short_name(packet):
    """
    Packet name에서 namespace 제거용
    예: se.auth.C_LoginReq -> C_LoginReq
    """
    return packet.name.split('.')[-1]

def cpp_type(full_name: str) -> str:
    """
    Proto full name (e.g. se.room.C_EnterReq)
    -> C++ type (e.g. SE::ROOM::C_EnterReq)
    """
    parts = full_name.split('.')
    namespaces = [p.lower() for p in parts[:-1]]
    type_name = parts[-1]

    return "::".join(namespaces + [type_name])

@dataclass
class GenConfig:
    template_dir: str
    out_dir: str
    overwrite: bool = True
    
class Generator:
    def __init__(self, cfg: GenConfig):
        self.cfg = cfg
        loader = jinja2.FileSystemLoader(cfg.template_dir)
        self.env = jinja2.Environment(
            loader = loader,
            autoescape = False,
            trim_blocks = True,
            lstrip_blocks = True,
        )
        self.env.globals["short_name"] = short_name
        self.env.globals["cpp_type"] = cpp_type
        
    def render_to_file(self, template_name: str, out_name, ctx: dict):
        tpl = self.env.get_template(template_name)
        result = tpl.render(**ctx)
        
        out_path = Path(self.cfg.out_dir) / out_name
        out_path.parent.mkdir(parents=True, exist_ok=True)
        
        if out_path.exists() and not self.cfg.overwrite:
            raise RuntimeError(f"Refusing to overwrite: {out_path}")
            
        out_path.write_text(result, encoding='utf-8')
        return out_path
