#!/usr/bin/env python3
from __future__ import annotations

import argparse
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parent
OUTPUT_DIR = ROOT / "tex"
EXAM_DIR_RE = re.compile(r"^\d{6}$")
LATEX_AUX_SUFFIXES = [
    ".aux",
    ".log",
    ".out",
    ".toc",
    ".fls",
    ".fdb_latexmk",
    ".synctex.gz",
]
HYPERTARGET_PREFIX_RE = re.compile(r"\\hypertarget\{[^}]*\}\{%\s*", re.DOTALL)
HEADING_EXTRA_BRACE_RE = re.compile(
    r"(\\(?:section|subsection|subsubsection|paragraph)\{[^{}]*\})\}",
    re.DOTALL,
)
LABEL_RE = re.compile(r"\\label\{[^}]*\}")
BOLD_RE = re.compile(r"\*\*(.+?)\*\*", re.DOTALL)
LONGTABLE_RE = re.compile(
    r"\\begin\{longtable\}\[\]\{@\{\}ll@\{\}\}\s*"
    r"(.*?)\\midrule\s*"
    r"\\endhead\s*"
    r"(.*?)"
    r"\\bottomrule\s*"
    r"\\end\{longtable\}",
    re.DOTALL,
)


def natural_key(text: str) -> list[object]:
    return [int(part) if part.isdigit() else part.lower() for part in re.split(r"(\d+)", text)]


def escape_latex(text: str) -> str:
    replacements = {
        "\\": r"\textbackslash{}",
        "&": r"\&",
        "%": r"\%",
        "$": r"\$",
        "#": r"\#",
        "_": r"\_",
        "{": r"\{",
        "}": r"\}",
        "~": r"\textasciitilde{}",
        "^": r"\textasciicircum{}",
    }
    return "".join(replacements.get(ch, ch) for ch in text)


def read_text(path: Path) -> str:
    return path.read_text(encoding="utf-8")


def render_plain_text_block(text: str) -> str:
    escaped = escape_latex(text.rstrip())
    if not escaped:
        return r"{\small\ttfamily（空）}" + "\n"
    return "{\\small\\ttfamily\n" + escaped + "\n}\n"


def convert_markdown_to_latex(path: Path) -> str:
    if shutil.which("pandoc") is None:
        raise RuntimeError("未找到 pandoc，无法转换 Markdown。")

    result = subprocess.run(
        [
            "pandoc",
            str(path),
            "-f",
            "gfm+tex_math_dollars",
            "-t",
            "latex",
            "--listings",
            "--wrap=none",
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
    )
    if result.returncode != 0:
        raise RuntimeError(
            f"{path.relative_to(ROOT).as_posix()} 的 Markdown 转 LaTeX 失败。\n"
            f"stdout:\n{result.stdout}\n\nstderr:\n{result.stderr}"
        )

    latex = result.stdout.strip()
    if not latex:
        return r"{\small\ttfamily（空）}" + "\n"

    latex = HYPERTARGET_PREFIX_RE.sub("", latex)
    latex = LABEL_RE.sub("", latex)
    latex = HEADING_EXTRA_BRACE_RE.sub(r"\1", latex)
    latex = latex.replace(r"\tightlist", "")
    latex = latex.replace(r"\passthrough{\lstinline!", r"\lstinline!")
    latex = latex.replace("!}", "!")
    latex = BOLD_RE.sub(r"\\textbf{\1}", latex)
    latex = latex.replace("**", "")
    latex = latex.replace(r"\section{", r"\section*{")
    latex = latex.replace(r"\subsection{", r"\subsection*{")
    latex = latex.replace(r"\subsubsection{", r"\subsubsection*{")
    latex = latex.replace(r"\paragraph{", r"\paragraph*{")
    latex = LONGTABLE_RE.sub(convert_longtable_to_tabularx, latex)
    return latex + "\n"


def convert_longtable_to_tabularx(match: re.Match[str]) -> str:
    header = match.group(1).strip()
    body = match.group(2).strip()
    return (
        r"\begin{center}" + "\n"
        r"\small" + "\n"
        r"\begin{tabularx}{\linewidth}{@{}>{\raggedright\arraybackslash}X>{\raggedright\arraybackslash}X@{}}" + "\n"
        + header
        + "\n"
        + body
        + "\n"
        + r"\end{tabularx}" + "\n"
        + r"\end{center}"
    )


def latex_preamble(title: str) -> str:
    escaped_title = escape_latex(title)
    return rf"""\documentclass[10pt,a4paper]{{ctexart}}
\usepackage[a4paper,top=0.8cm,bottom=1.35cm,left=1.0cm,right=1.0cm,includehead=false]{{geometry}}
\usepackage{{multicol}}
\usepackage{{listings}}
\usepackage{{xcolor}}
\usepackage{{titlesec}}
\usepackage{{enumitem}}
\usepackage{{hyperref}}
\usepackage{{amsmath}}
\usepackage{{booktabs}}
\usepackage{{longtable}}
\usepackage{{tabularx}}
\usepackage{{array}}

\pagestyle{{empty}}
\setlength{{\parindent}}{{0pt}}
\setlength{{\parskip}}{{0.2em}}
\setlength{{\topskip}}{{0pt}}
\raggedcolumns

\definecolor{{codebg}}{{RGB}}{{247,247,247}}
\definecolor{{coderule}}{{RGB}}{{220,220,220}}
\definecolor{{codecomment}}{{RGB}}{{0,120,70}}
\definecolor{{codestring}}{{RGB}}{{163,21,21}}
\definecolor{{codekeyword}}{{RGB}}{{0,69,173}}

\lstdefinestyle{{cppstyle}}{{%
    language=C++,
    backgroundcolor=\color{{codebg}},
    basicstyle=\ttfamily\scriptsize,
    keywordstyle=\color{{codekeyword}}\bfseries,
    commentstyle=\color{{codecomment}},
    stringstyle=\color{{codestring}},
    numbers=left,
    numberstyle=\tiny\color{{gray}},
    stepnumber=1,
    numbersep=8pt,
    showstringspaces=false,
    breaklines=true,
    breakatwhitespace=false,
    tabsize=4,
    frame=single,
    framerule=0.4pt,
    rulecolor=\color{{coderule}},
    columns=fullflexible,
    keepspaces=true
}}
\lstset{{style=cppstyle}}
\providecommand{{\passthrough}}[1]{{#1}}

\titleformat{{\section}}{{\large\bfseries}}{{}}{{0pt}}{{}}
\titleformat{{\subsection}}{{\normalsize\bfseries}}{{}}{{0pt}}{{}}
\titleformat{{\subsubsection}}{{\normalsize\bfseries}}{{}}{{0pt}}{{}}
\titleformat{{\paragraph}}{{\normalsize\bfseries}}{{}}{{0pt}}{{}}
\titlespacing*{{\section}}{{0pt}}{{0.4em}}{{0.2em}}
\titlespacing*{{\subsection}}{{0pt}}{{0.35em}}{{0.15em}}
\titlespacing*{{\subsubsection}}{{0pt}}{{0.3em}}{{0.1em}}
\titlespacing*{{\paragraph}}{{0pt}}{{0.25em}}{{0.1em}}

\setlength{{\columnsep}}{{1.2em}}
\setlength{{\columnseprule}}{{0.4pt}}
\setlength{{\premulticols}}{{0pt}}
\setlength{{\postmulticols}}{{0pt}}
\setlength{{\multicolsep}}{{4pt}}

\begin{{document}}
{{\large\bfseries {escaped_title}\hfill \thepage}}
\vspace{{0.2em}}
\begin{{multicols}}{{2}}
"""


def latex_end() -> str:
    return "\\end{multicols}\n\\end{document}\n"


def render_code_section(question: str, path: Path) -> str:
    escaped_path = escape_latex(path.relative_to(ROOT).as_posix())
    listing_path = Path(os.path.relpath(path, OUTPUT_DIR)).as_posix()
    return (
        rf"\subsection*{{题目 {escape_latex(question)} - 代码}}"
        + "\n"
        + rf"{{\small\texttt{{{escaped_path}}}}}"
        + "\n\n"
        + rf"\lstinputlisting[style=cppstyle]{{{listing_path}}}"
        + "\n\n"
    )


def render_doc_section(question: str | None, path: Path) -> str:
    prefix = f"题目 {question} - " if question is not None else ""
    title = prefix + path.name
    body = convert_markdown_to_latex(path)
    return (
        rf"\textbf{{文件名：{escape_latex(title)}}}"
        + "\n"
        + "\n"
        + r"\textbf{内容：}"
        + "\n"
        + body
        + "\n"
    )


def collect_exam_tex(exam_dir: Path) -> str:
    chunks = [latex_preamble(f"CCF CSP {exam_dir.name}")]
    question_dirs = sorted(
        [path for path in exam_dir.iterdir() if path.is_dir()],
        key=lambda path: natural_key(path.name),
    )

    has_content = False
    for question_dir in question_dirs:
        section_parts: list[str] = []
        code_path = question_dir / "main.cpp"
        if code_path.exists() and code_path.is_file() and code_path.stat().st_size > 0:
            section_parts.append(render_code_section(question_dir.name, code_path))

        doc_paths = sorted(question_dir.glob("*.md"), key=lambda path: natural_key(path.name))
        for doc_path in doc_paths:
            section_parts.append(render_doc_section(question_dir.name, doc_path))

        if section_parts:
            has_content = True
            chunks.append(rf"\section*{{题目 {escape_latex(question_dir.name)}}}" + "\n\n")
            chunks.extend(section_parts)

    if not has_content:
        chunks.append(r"\section*{说明}" + "\n\n")
        chunks.append("当前考试目录下没有可收录的 main.cpp 或 Markdown 文档。\n")

    chunks.append(latex_end())
    return "".join(chunks)


def collect_root_docs_tex() -> str:
    chunks = [latex_preamble("CCF CSP 根目录文档汇总")]
    doc_paths = sorted(
        [path for path in ROOT.glob("*.md") if path.is_file()],
        key=lambda path: natural_key(path.name),
    )

    if not doc_paths:
        chunks.append(r"\section*{说明}" + "\n\n")
        chunks.append("根目录下没有 Markdown 文档。\n")
    else:
        for doc_path in doc_paths:
            chunks.append(render_doc_section(None, doc_path))

    chunks.append(latex_end())
    return "".join(chunks)


def write_file(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8", newline="\n")


def compile_tex(tex_path: Path, engine: str) -> None:
    if shutil.which(engine) is None:
        raise RuntimeError(f"未找到 LaTeX 引擎: {engine}")

    cmd = [engine, "-interaction=nonstopmode", "-halt-on-error", tex_path.name]
    for _ in range(2):
        result = subprocess.run(
            cmd,
            cwd=tex_path.parent,
            capture_output=True,
            text=True,
            encoding="utf-8",
            errors="replace",
        )
        if result.returncode != 0:
            raise RuntimeError(
                f"{tex_path.name} 编译失败。\n"
                f"stdout:\n{result.stdout}\n\nstderr:\n{result.stderr}"
            )

    stem = tex_path.stem
    for suffix in LATEX_AUX_SUFFIXES:
        aux_path = tex_path.parent / f"{stem}{suffix}"
        if aux_path.exists():
            aux_path.unlink()


def generate_all(compile_pdf: bool, engine: str) -> list[Path]:
    outputs: list[Path] = []

    exam_dirs = sorted(
        [path for path in ROOT.iterdir() if path.is_dir() and EXAM_DIR_RE.match(path.name)],
        key=lambda path: natural_key(path.name),
    )
    for exam_dir in exam_dirs:
        tex_path = OUTPUT_DIR / f"{exam_dir.name}.tex"
        write_file(tex_path, collect_exam_tex(exam_dir))
        outputs.append(tex_path)

    root_tex_path = OUTPUT_DIR / "root_docs.tex"
    write_file(root_tex_path, collect_root_docs_tex())
    outputs.append(root_tex_path)

    if compile_pdf:
        for tex_path in outputs:
            compile_tex(tex_path, engine)

    return outputs


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="为 ccf_csp 目录生成可打印的 LaTeX 资料。"
    )
    parser.add_argument(
        "--compile",
        action="store_true",
        help="生成 .tex 后顺带调用 LaTeX 引擎编译 PDF。",
    )
    parser.add_argument(
        "--engine",
        default="xelatex",
        help="编译使用的 LaTeX 引擎，默认 xelatex。",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        outputs = generate_all(compile_pdf=args.compile, engine=args.engine)
    except Exception as exc:
        print(str(exc), file=sys.stderr)
        return 1

    print("已生成以下文件：")
    for path in outputs:
        print(path.relative_to(ROOT))
        if args.compile:
            pdf_path = path.with_suffix(".pdf")
            print(pdf_path.relative_to(ROOT))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
