import re
import sys
from typing import List


def write_test_fixtures() -> None:
    data_txt = (
        "1 minute.\n"
        "{4, 'l'}\n"
        "(5, 'l')\n"
        "True | story."
    )

    unpack_txt = (
        "# unpack : Unpacks tuples of the form (a, (b, c)) into (a, b, c).\n"
        "(e, (f, g)) -> (e, f, g);\n"
        "\n"
        "# unpackall : From a set of tuples of the form (a, (b, c)), return a set of (a, b, c).\n"
        "s -> (|s| == 1) ? { unpack[s[0]] } : ({ unpack[s[0]] } U unpackall[s[(1, |s|)]]);"
    )

    with open("data.txt", "w", encoding="utf-8", newline="\n") as f:
        f.write(data_txt)

    with open("unpack.txt", "w", encoding="utf-8", newline="\n") as f:
        f.write(unpack_txt)


def extract_perl_repl_blocks(text: str) -> List[List[str]]:
    perl_blocks = re.findall(r"```perl\s*(.*?)\s*```", text, flags=re.DOTALL)

    lines: List[str] = []
    for block in perl_blocks:
        for raw_line in block.splitlines():
            if not raw_line.startswith(">>> "):
                continue
            if raw_line.startswith(">>> under apply") or raw_line.startswith(">>> under fold"):
                continue

            line = raw_line[4:]
            line = re.sub(r"#.*$", "", line).strip()
            if line:
                lines.append(line)

    groups: List[List[str]] = []
    current: List[str] = []

    for line in lines:
        current.append(line)
        if line == "quit":
            groups.append(current)
            current = []

    if current:
        current.append("quit")
        groups.append(current)

    return groups


def write_repl_files(groups: List[List[str]]) -> None:
    for idx, group in enumerate(groups, start=1):
        filename = f"repl_{idx}.al"
        with open(filename, "w", encoding="utf-8", newline="\n") as f:
            for line in group:
                f.write(line + "\n")


def main() -> int:
    write_test_fixtures()

    with open("README.md", "r", encoding="utf-8") as f:
        text = f.read()

    groups = extract_perl_repl_blocks(text)
    write_repl_files(groups)

    # Machine-readable output for scripts:
    print(len(groups))

    # Return code: keep it conventional (0 = success). Use stdout for the number.
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
