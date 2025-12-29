import re
import sys
from collections import Counter
from dataclasses import dataclass
from pathlib import Path
from typing import List, Tuple

README_EXPECTED_DEBUG_PATH = Path("README_expected.txt")
REPL_OUT_PROCESSED_DEBUG_PATH = Path("repl_out_processed.txt")

DATA_TXT_PATH = Path("data.txt")
README_PATH = Path("README.md")
REPL_OUT_PATH = Path("repl_out.txt")

# Required header/prefix (after normalization, so keep as \n)
REPL_HEADER_PREFIX = (
    "Autolang, Version 2.0\n"
    "Copyright (c) 2016 Tushar Rakheja (The MIT License).\n"
    "\n"
    'To change the prompt, use the variable "__prompt__".\n'
    "\n"
    ">>> "
)

HEADER_FILTER_SUBSTRINGS = [
    "Autolang, Version 2.0",
    "Copyright (c) 2016 Tushar Rakheja (The MIT License)",
    'To change the prompt, use the variable "__prompt__"',
]

EXPECTED_DATA_TXT = (
    "1 minute.\n"
    "{4, 'l'}\n"
    "(5, 'l')\n"
    "True | story.\n"
    "See?\"\\nSee?\""
)


@dataclass(frozen=True)
class ExpectedLine:
    text: str
    ordering_not_important: bool


def verify_data_txt() -> None:
    if not DATA_TXT_PATH.exists():
        raise AssertionError("data.txt was not found after REPL tests.")

    actual = normalize_text_newlines(DATA_TXT_PATH.read_text(encoding="utf-8"))

    expected = EXPECTED_DATA_TXT

    if actual != expected:
        raise AssertionError(
            "data.txt contents do not match expected final state.\n\n"
            "Expected:\n"
            f"{expected!r}\n\n"
            "Actual:\n"
            f"{actual!r}"
        )


def write_expected_debug(expected: List[ExpectedLine]) -> None:
    with README_EXPECTED_DEBUG_PATH.open("w", encoding="utf-8", newline="\n") as f:
        for e in expected:
            f.write(e.text + "\n")


def write_actual_debug(actual_lines: List[str]) -> None:
    with REPL_OUT_PROCESSED_DEBUG_PATH.open("w", encoding="utf-8", newline="\n") as f:
        for line in actual_lines:
            f.write(line + "\n")


def normalize_text_newlines(text: str) -> str:
    """
    Normalize line endings and related artifacts so comparisons are stable across OSes.
    - Convert CRLF and CR to LF.
    - Strip UTF-8 BOM if present.
    """
    # Strip BOM if present
    if text.startswith("\ufeff"):
        text = text.lstrip("\ufeff")
    # Normalize newlines
    text = text.replace("\r\n", "\n").replace("\r", "\n")
    return text


def normalize_line(line: str) -> str:
    """
    Normalize a single line for cross-platform comparisons.
    - Normalize whitespace at ends.
    - Optionally compress internal runs of spaces/tabs to a single space.
      (Leave this OFF by default to keep comparisons strict, except for known newline issues.)
    """
    # Strip only; do not compress internal whitespace unless you explicitly want that behavior
    return line.strip()


def extract_perl_blocks(text: str) -> List[str]:
    return re.findall(r"```perl\s*(.*?)\s*```", text, flags=re.DOTALL)


def strip_comment_and_track_ordering(line: str) -> Tuple[str, bool]:
    ordering = "# Ordering not important" in line
    line = re.sub(r"#.*$", "", line).strip()
    return line, ordering


def expected_lines_from_readme(readme_text: str) -> List[ExpectedLine]:
    blocks = extract_perl_blocks(readme_text)
    out: List[ExpectedLine] = []

    for block in blocks:
        for raw in block.splitlines():
            raw = normalize_line(raw)

            # Remove all prompt/input lines
            if raw.startswith(">>> "):
                continue

            cleaned, ordering = strip_comment_and_track_ordering(raw)
            cleaned = normalize_line(cleaned)
            if cleaned:
                out.append(ExpectedLine(text=cleaned, ordering_not_important=ordering))

    return out


def verify_repl_header(repl_text: str) -> None:
    if not repl_text.startswith(REPL_HEADER_PREFIX):
        got = repl_text[: max(200, len(REPL_HEADER_PREFIX))]
        raise AssertionError(
            "repl_out.txt does not start with the required REPL header/prefix.\n"
            f"Expected prefix (length {len(REPL_HEADER_PREFIX)}):\n{REPL_HEADER_PREFIX}\n\ngot beginning:\n"
            f"{got}"
        )


def normalize_repl_out_lines(repl_text: str) -> List[str]:
    lines = repl_text.splitlines()

    filtered: List[str] = []
    for line in lines:
        # Do not strip before substring checks; substring checks should survive whitespace variance anyway
        if any(s in line for s in HEADER_FILTER_SUBSTRINGS):
            continue

        line = line.replace(">>> ", "")
        line = normalize_line(line)
        if line:
            filtered.append(line)

    return filtered


def split_top_level_elements(s: str) -> List[str]:
    elems: List[str] = []
    buf: List[str] = []

    depth_paren = 0
    depth_brace = 0
    depth_bracket = 0
    in_single = False
    in_double = False
    escape = False

    def flush():
        token = "".join(buf).strip()
        if token:
            elems.append(token)

    for ch in s:
        if escape:
            buf.append(ch)
            escape = False
            continue

        if ch == "\\" and (in_single or in_double):
            buf.append(ch)
            escape = True
            continue

        if ch == "'" and not in_double:
            in_single = not in_single
            buf.append(ch)
            continue

        if ch == '"' and not in_single:
            in_double = not in_double
            buf.append(ch)
            continue

        if not in_single and not in_double:
            if ch == "(":
                depth_paren += 1
            elif ch == ")":
                depth_paren = max(0, depth_paren - 1)
            elif ch == "{":
                depth_brace += 1
            elif ch == "}":
                depth_brace = max(0, depth_brace - 1)
            elif ch == "[":
                depth_bracket += 1
            elif ch == "]":
                depth_bracket = max(0, depth_bracket - 1)

            if ch == "," and depth_paren == 0 and depth_brace == 0 and depth_bracket == 0:
                flush()
                buf = []
                continue

        buf.append(ch)

    flush()
    return elems


def as_unordered_collection(line: str) -> Counter:
    line = normalize_line(line)
    if len(line) >= 2 and ((line[0] == "{" and line[-1] == "}") or (line[0] == "[" and line[-1] == "]")):
        inner = line[1:-1].strip()
    else:
        return Counter([line])

    if not inner:
        return Counter()

    elems = split_top_level_elements(inner)
    # Mild normalization for stable comparisons (keeps semantics, reduces whitespace noise)
    elems = [" ".join(e.split()) for e in elems]
    return Counter(elems)


def compare_outputs(expected: List[ExpectedLine], actual_lines: List[str]) -> None:
    if len(expected) != len(actual_lines):
        raise AssertionError(
            f"Line count mismatch: README expected {len(expected)} lines, "
            f"repl_out.txt produced {len(actual_lines)} lines."
        )

    for idx, (exp, act) in enumerate(zip(expected, actual_lines), start=1):
        act_norm = normalize_line(act)

        if not exp.ordering_not_important:
            exp_norm = normalize_line(exp.text)
            if exp_norm != act_norm:
                raise AssertionError(
                    f"Mismatch at line {idx}:\n"
                    f"  Expected: {exp_norm!r}\n"
                    f"  Actual:   {act_norm!r}"
                )
        else:
            exp_coll = as_unordered_collection(exp.text.replace("{", "[").replace("}", "]"))
            act_coll = as_unordered_collection(act_norm.replace("{", "[").replace("}", "]"))
            if exp_coll != act_coll:
                raise AssertionError(
                    f"Unordered mismatch at line {idx} (marked '# Ordering not important'):\n"
                    f"  Expected raw: {exp.text!r}\n"
                    f"  Actual raw:   {act_norm!r}\n"
                    f"  Expected elements: {sorted(exp_coll.elements())}\n"
                    f"  Actual elements:   {sorted(act_coll.elements())}"
                )


def main() -> int:
    if not README_PATH.exists():
        print(f"ERROR: {README_PATH} not found.", file=sys.stderr)
        return 1
    if not REPL_OUT_PATH.exists():
        print(f"ERROR: {REPL_OUT_PATH} not found.", file=sys.stderr)
        return 1

    readme_text = normalize_text_newlines(README_PATH.read_text(encoding="utf-8"))
    expected = expected_lines_from_readme(readme_text)

    repl_text = normalize_text_newlines(REPL_OUT_PATH.read_text(encoding="utf-8"))
    verify_repl_header(repl_text)
    actual_lines = normalize_repl_out_lines(repl_text)

    # DEBUG OUTPUTS
    write_expected_debug(expected)
    write_actual_debug(actual_lines)

    compare_outputs(expected, actual_lines)

    verify_data_txt()

    print("OK: repl_out.txt matches README outputs (with unordered checks for '# Ordering not important').")
    print("OK: data.txt final contents verified.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
