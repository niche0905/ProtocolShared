from dataclasses  import dataclass
from pathlib import Path
import jinja2

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
        
    def render_to_file(self, template_name: str, out_name, ctx: dict):
        tpl = self.env.get_template(template_name)
        result = tpl.render(**ctx)
        
        out_path = Path(self.cfg.out_dir) / out_name
        out_path.parent.mkdir(parents=True, exist_ok=True)
        
        if out_path.exists() and not self.cfg.overwrite:
            raise RuntimeError(f"Refusing to overwrite: {out_path}")
            
        out_path.write_text(result, encoding='utf-8')
        return out_path
