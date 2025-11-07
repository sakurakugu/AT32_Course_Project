# -*- coding: utf-8 -*-

"""
Optimize Keil µVision build log HTML (*.build_log.htm) and copy to build/.

功能：
- 将大量 "compiling ..." 行折叠为一句汇总："编译了 N 个文件"。
- 将 "assembling ..." 行折叠为一句汇总："汇编了 N 个文件"。
- 将常见英文术语替换为中文，提升可读性；支持外部配置映射。
- 输出到指定目录（默认：build/），文件名加 .optimized 后缀。

用法示例：
  python tools/optimize_build_log.py --file build/output/homework.build_log.htm --out-dir build
  python tools/optimize_build_log.py  # 默认处理 build/output/*.build_log.htm
  python tools/optimize_build_log.py --map tools/translations.json  # 使用自定义翻译映射
"""

import argparse
import glob
import json
import os
import re
import sys
import unicodedata
from typing import List, Tuple, Optional


def _summarize_actions(lines: List[str]) -> List[str]:
    """统计并移除以 'compiling ' 与 'assembling ' 开头的行，分别插入汇总。"""
    compiling_re = re.compile(r"^\s*compiling\s+.+", re.IGNORECASE)
    assembling_re = re.compile(r"^\s*assembling\s+.+", re.IGNORECASE)
    compile_count = 0
    asm_count = 0
    
    # 记录首次出现编译行的位置，用于插入汇总
    first_compile_idx: Optional[int] = None
    first_asm_idx: Optional[int] = None
    kept_lines: List[str] = []
    for ln in lines:
        if compiling_re.match(ln):
            compile_count += 1
            if first_compile_idx is None:
                first_compile_idx = len(kept_lines)
            continue
        if assembling_re.match(ln):
            asm_count += 1
            if first_asm_idx is None:
                first_asm_idx = len(kept_lines)
            continue
        kept_lines.append(ln)

    # 计算插入顺序，避免索引偏移错误
    inserts: List[Tuple[int, str]] = []
    if compile_count > 0:
        inserts.append((first_compile_idx or 0, f"编译了 {compile_count} 个文件"))
    if asm_count > 0:
        inserts.append((first_asm_idx or 0, f"汇编了 {asm_count} 个文件"))

    for idx, text in sorted(inserts, key=lambda x: x[0]):
        kept_lines.insert(idx, text)

    return kept_lines


def _load_translations(path: Optional[str]) -> List[Tuple[str, str]]:
    """加载翻译映射。优先使用用户提供的 JSON 文件，其次使用默认映射。"""
    default = [
        (r"\bVision Build Log\b", "Vision 构建日志"),
        (r"\bTool Versions:", "工具版本："),
        (r"\bIDE-Version:", "IDE版本："),
        (r"\bToolchain:", "工具链："),
        (r"\bVersion:", "版本："),
        (r"\bToolchain Path:", "工具链路径："),
        (r"\bC Compiler:", "C 编译器："),
        (r"\bAssembler:", "汇编器："),
        (r"\bLinker/Locator:", "链接器/定位器："),
        (r"\bLibrary Manager:", "库管理器："),
        (r"\bHex Converter:", "Hex 转换器："),
        (r"\bCPU DLL:", "CPU DLL："),
        (r"\bTarget DLL:", "目标 DLL："),
        (r"\bDialog DLL:", "对话 DLL："),
        (r"\bProject File Date:", "项目文件日期："),
        (r"\bProject:", "项目："),
        (r"\bOutput:", "输出："),
        (r"\bUsing Compiler", "使用的编译器"),
        (r"\bunknown type name", "未知类型名称"),
        (r"\buse of undeclared identifier", "未声明标识符的使用"),
        (r"\bdeclared with C language linkage here", "在 C 语言链接中声明"),
        (r"\bFolder:", "文件夹："),
        (r"\bRebuild target\b", "重新构建目标"),
        (r"\blink(?:ing)?\.\.\.", "链接中..."),
        (r"\bError:", "错误："),
        (r"\bWarning:", "警告："),
        (r"\bSoftware Packages used:", "使用的软件包："),
        (r"\bPackage Vendor:", "软件包供应商："),
        (r"\bCollection of Component include folders:", "组件包含目录："),
        (r"\bCollection of Component Files used:", "使用的组件文件集合："),
        (r"\bBuild Time Elapsed:", "构建耗时："),
        (r"\bTarget not created\.", "未生成目标。"),
        (r"\bUndefined symbol\b", "未定义符号"),
        (r"Not enough information to list image symbols\.", "没有足够信息列出镜像符号。"),
        (r"Not enough information to list load addresses in the image map\.", "没有足够信息列出镜像映射中的加载地址。"),
        (r"Program Size:", "程序大小："),
        (r"Finished:", "完成："),
        (r"\binformation\b", "信息"),
        (r"\bwarning\b", "警告"),
        (r"\berror messages\b", "错误"),
        (r"FromELF: creating hex file\.\.\.", "从 ELF 创建 Hex 文件..."),
        (r"\bPattern\b", "模式"),
        (r"only matches removed unused sections.", "仅匹配移除的未使用部分。"),
    ]

    if path and os.path.isfile(path):
        try:
            with open(path, "r", encoding="utf-8") as f:
                data = json.load(f)
            if isinstance(data, dict):
                return list(data.items())
            if isinstance(data, list):
                # 支持 [ [pattern, repl], ... ] 或 [ {"pattern": "...", "repl": "..."}, ... ]
                pairs: List[Tuple[str, str]] = []
                for item in data:
                    if isinstance(item, list) and len(item) == 2:
                        pairs.append((str(item[0]), str(item[1])))
                    elif isinstance(item, dict) and "pattern" in item and "repl" in item:
                        pairs.append((str(item["pattern"]), str(item["repl"])))
                if pairs:
                    return pairs
        except Exception:
            pass

    # 尝试默认位置
    default_json = os.path.join(os.path.dirname(__file__), "translations.json")
    if os.path.isfile(default_json):
        try:
            with open(default_json, "r", encoding="utf-8") as f:
                data = json.load(f)
            if isinstance(data, dict):
                return list(data.items())
        except Exception:
            pass

    return default


def _apply_translations(text: str, translations: List[Tuple[str, str]]) -> str:
    for pattern, repl in translations:
        text = re.sub(pattern, repl, text, flags=re.IGNORECASE)
    return text


def _beautify_stats(text: str) -> str:
    """美化“完成统计”行并规范可选复数后缀。"""
    # 仅在以“完成：”开头的行中，将 ' and ' → ' 和 '
    def _and_to_he(line: str) -> str:
        return line.replace(" and ", " 和 ")

    def _replace_line(match: re.Match) -> str:
        return _and_to_he(match.group(0))

    text = re.sub(r"(?m)^完成：.*$", _replace_line, text)
    # 规范 Error(s)/Warning(s)/Information(s)
    text = re.sub(r"(?i)\bError\(s\)", "错误", text)
    text = re.sub(r"(?i)\bWarning\(s\)", "警告", text)
    text = re.sub(r"(?i)\bInformation\(s\)", "信息", text)
    # 若前面已将英文替换为中文，清理残留的 (s)
    text = re.sub(r"错误\(s\)", "错误", text)
    text = re.sub(r"警告\(s\)", "警告", text)
    text = re.sub(r"信息\(s\)", "信息", text)
    return text

import re
import unicodedata
from typing import List

def _format_program_size(text: str) -> str:
    """将“程序大小”行格式化为中文，列对齐，追加 KB/MB 单位。"""
    line_re = re.compile(r"(?im)^(?:Program\s+Size:|程序大小：)\s*(.*)$")

    name_map = {
        "Code": "代码",
        "RO-data": "只读数据",
        "RW-data": "读写数据",
        "ZI-data": "零初始化数据",
    }

    def _visual_width(s: str) -> int:
        """计算字符串的可视宽度，中文宽字符记为2，其他为1。"""
        w = 0
        for ch in s:
            eaw = unicodedata.east_asian_width(ch)
            w += 2 if eaw in ("W", "F") else 1
        return w

    def _repl(m: re.Match) -> str:
        tail = m.group(1)
        items = re.findall(r"(?i)\b(Code|RO-data|RW-data|ZI-data)\s*=\s*(\d+)", tail)
        if not items:
            return f"程序大小： {tail}".rstrip()

        # 计算宽度
        prefix_width = max(_visual_width(name_map.get(key, key)) + 1 for key, _ in items)
        num_width = max(len(num_s) for _, num_s in items)

        # 提前计算所有 KB/MB 数值宽度
        kb_vals = []
        mb_vals = []
        for _, num_s in items:
            try:
                val = int(num_s)
            except ValueError:
                val = 0
            kb_vals.append(val / 1024.0)
            mb_vals.append(val / (1024.0 * 1024.0))

        # 找到最长的小数宽度（含整数部分）
        kb_width = max(len(f"{x:.2f}") for x in kb_vals)
        mb_width = max(len(f"{x:.2f}") for x in mb_vals)

        parts: List[str] = []
        for i, (key, num_s) in enumerate(items):
            val = int(num_s)
            kb = kb_vals[i]
            mb = mb_vals[i]
            cn = name_map.get(key, key)
            pad = prefix_width - (_visual_width(cn) + 1)

            parts.append(
                f"\n\t{cn}="
                + (" " * pad)
                + f"{val:<{num_width}}"
                + f" ({kb:>{kb_width}.2f}KB) ({mb:>{mb_width}.2f}MB)"
            )

        return "程序大小：" + "".join(parts)

    return line_re.sub(_repl, text)


def optimize_build_log(html_text: str, translations_path: Optional[str] = None) -> str:
    """对整个 HTML 文本做优化。保留原有结构，仅优化 <pre> 内容。"""
    # 粗略定位 <pre> ... </pre> 内容块
    pre_open = html_text.lower().find("<pre>")
    pre_close = html_text.lower().find("</pre>")
    if pre_open == -1 or pre_close == -1 or pre_close <= pre_open:
        # 不是预期格式，做全局翻译，不做汇总
        translations = _load_translations(translations_path)
        out = _apply_translations(html_text, translations)
        out = _format_program_size(out)
        out = _beautify_stats(out)
        return out

    head = html_text[: pre_open + len("<pre>")]
    pre = html_text[pre_open + len("<pre>") : pre_close]
    tail = html_text[pre_close:]

    lines = pre.splitlines()
    lines = _summarize_actions(lines)
    new_pre = "\n".join(lines)
    new_html = head + new_pre + tail
    translations = _load_translations(translations_path)
    new_html = _apply_translations(new_html, translations)
    new_html = _format_program_size(new_html)
    new_html = _beautify_stats(new_html)
    return new_html


def process_file(src_path: str, out_dir: str, translations_path: Optional[str] = None) -> str:
    """处理单个文件：优化并复制到指定目录。"""
    # 读入时忽略潜在编码问题
    with open(src_path, "r", encoding="utf-8", errors="ignore") as f:
        content = f.read()

    optimized = optimize_build_log(content, translations_path)

    base = os.path.basename(src_path)
    name, ext = os.path.splitext(base)
    # 输出文件名：去掉原扩展，改成“.html”
    out_name = f"{name}.html"
    os.makedirs(out_dir, exist_ok=True)
    out_path = os.path.join(out_dir, out_name)

    with open(out_path, "w", encoding="utf-8") as f:
        f.write(optimized)

    return out_path


def main():
    parser = argparse.ArgumentParser(description="优化 Keil 构建日志并复制到 build/")
    parser.add_argument("--file", "-f", help="指定单个 .build_log.htm 文件路径")
    parser.add_argument(
        "--input-dir",
        "-i",
        help="搜索目录（默认：build/output）",
        default=None,
    )
    parser.add_argument(
        "--out-dir",
        "-o",
        help="输出目录（默认：build）",
        default="build",
    )
    parser.add_argument(
        "--map",
        help="JSON 翻译映射文件路径（可选）",
        default=None,
    )
    args = parser.parse_args()

    # 计算输入文件集合
    files: List[str]
    if args.file:
        files = [args.file]
    else:
        root = args.input_dir or os.path.join("build", "output")
        files = glob.glob(os.path.join(root, "*.build_log.htm"))

    if not files:
        print("未找到任何 .build_log.htm 文件")
        sys.exit(1)

    for fp in files:
        outp = process_file(fp, args.out_dir, args.map)
        print(f"已生成优化日志: {outp}")


if __name__ == "__main__":
    main()