import argparse
import sys

try:
    from pypinyin import lazy_pinyin, Style
    PYPINYIN_AVAILABLE = True
except Exception:
    PYPINYIN_AVAILABLE = False
    lazy_pinyin = None
    Style = None


def is_cjk(char):
    """
    判断字符是否为CJK统一表意符号（包括中文字符、日文字符、韩文字符等）
    """
    cp = ord(char)
    return (
        (0x4E00 <= cp <= 0x9FFF)
        or (0x3400 <= cp <= 0x4DBF)
        or (0x20000 <= cp <= 0x2A6DF)
        or (0x2A700 <= cp <= 0x2B73F)
        or (0x2B740 <= cp <= 0x2B81F)
        or (0x2B820 <= cp <= 0x2CEAF)
        or (0xF900 <= cp <= 0xFAFF)
        or (0x2F800 <= cp <= 0x2FA1F)
    )


def extract_unique_chars(text, keep_whitespace=False):
    if not keep_whitespace:
        text = ''.join(ch for ch in text if not ch.isspace())
    return set(text)


def sort_chars(chars, mode):
    if mode == 'pinyin':
        if not PYPINYIN_AVAILABLE:
            print('错误：需要安装 pypinyin 才能使用拼音排序。请运行: pip install pypinyin', file=sys.stderr)
            sys.exit(2)

        def key(ch):
            if is_cjk(ch):
                py = ''.join(lazy_pinyin(ch, style=Style.NORMAL))
            else:
                py = ch.casefold()
            return (py, ord(ch))
    else:
        def key(ch):
            return (ch.casefold(), ord(ch))

    return sorted(chars, key=key)


def main():
    parser = argparse.ArgumentParser(description='从TXT去重所有字符并按拼音或字母排序')
    parser.add_argument('input', help='输入TXT文件路径')
    parser.add_argument('-o', '--output', help='输出文件路径（不填则打印到控制台且覆盖输出到output.txt）')
    parser.add_argument('--mode', choices=['pinyin', 'alphabet', 'ascii'], default='pinyin', help='排序方式：pinyin=按拼音，alphabet/ascii=按字母/ASCII')
    parser.add_argument('--encoding', default='utf-8', help='文件编码（默认utf-8）')
    parser.add_argument('--keep-whitespace', action='store_true', help='保留空白字符（空格、换行、制表符等）')
    parser.add_argument('--per-line', action='store_true', help='每个字符单独一行输出')
    parser.add_argument('--exclude-ascii', action='store_true', help='去除所有ASCII字符（0x00-0x7F），常用于仅保留中文')
    args = parser.parse_args()

    mode = args.mode
    if mode == 'alphabet':
        mode = 'ascii'
    elif mode == 'pingying' or mode == 'pingyin' or mode == 'pinying': # 模糊音
        mode = 'pinyin'

    try:
        with open(args.input, 'r', encoding=args.encoding, errors='ignore') as f:
            text = f.read()
    except Exception as e:
        print(f'读取文件失败：{e}', file=sys.stderr)
        sys.exit(1)

    # 移除UTF-8 BOM（如果存在）
    if text.startswith('\ufeff'):
        text = text.lstrip('\ufeff')

    chars = extract_unique_chars(text, keep_whitespace=args.keep_whitespace) # 提取唯一字符
    if args.exclude_ascii:
        chars = {ch for ch in chars if ord(ch) > 0x7F}
    sorted_chars = sort_chars(chars, mode)                                   # 排序字符

    if args.per_line:
        out_text = '\n'.join(sorted_chars)
    else:
        out_text = ''.join(sorted_chars)

    if args.output:
        try:
            with open(args.output, 'w', encoding=args.encoding) as f:
                f.write(out_text)
        except Exception as e:
            print(f'写入文件失败：{e}', file=sys.stderr)
            sys.exit(1)
    else:
        sys.stdout.write(out_text)
        try:
            with open('build/output.txt', 'w', encoding=args.encoding) as f:
                f.write(out_text)
        except Exception as e:
            print(f'写入文件失败：{e}', file=sys.stderr)
            sys.exit(1)


if __name__ == '__main__':
    main()