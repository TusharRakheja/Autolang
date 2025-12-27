import sys
import re

EXPECTED = [
    ("Map f", {(1, 2), (2, 3), (3, 1)}),
    ("Map f o f", {(1, 3), (2, 1), (3, 2)}),
    ("Map f ^ 2", {(1, 3), (2, 1), (3, 2)}),
    ("Map f o f o f", {(1, 1), (2, 2), (3, 3)}),
    ("Map f ^ 3", {(1, 1), (2, 2), (3, 3)}),
    ("Map f ^= 3", {(1, 1), (2, 2), (3, 3)}),
]

def parse_tuple_set(s):
    """
    Parses {(1, 2), (3, 4)} into a Python set of tuples.
    """
    tuples = re.findall(r"\(\s*(-?\d+)\s*,\s*(-?\d+)\s*\)", s)
    return {(int(a), int(b)) for a, b in tuples}

def main(path):
    with open(path, "r") as f:
        lines = f.readlines()

    if len(lines) != len(EXPECTED):
        print(f"ERROR: Expected {len(EXPECTED)} lines, got {len(lines)}")
        sys.exit(1)

    for i, (line, (label, expected_set)) in enumerate(zip(lines, EXPECTED), 1):
        if ": " not in line:
            print(f"ERROR: Line {i}: missing ':'")
            sys.exit(1)

        lhs, rhs = line.split(": ")
        lhs = lhs.strip()

        if lhs != label:
            print(f"ERROR: Line {i}: expected label '{label}', got '{lhs}'")
            sys.exit(1)

        actual_set = parse_tuple_set(rhs)

        if actual_set != expected_set:
            print(f"ERROR: Line {i}: set mismatch")
            print(f"   Expected: {expected_set}")
            print(f"   Got:      {actual_set}")
            sys.exit(1)

    print("SUCCESS: Map output test passed")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python test_map_output.py <output_file>")
        sys.exit(2)

    main(sys.argv[1])
