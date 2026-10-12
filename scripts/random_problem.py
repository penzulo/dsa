#!/usr/bin/env python3
"""Pick a random problem from the dsa/ problem set to practice.

The problem URL (or, for non-LeetCode problems, the problem description)
comes from the first line of each solution.cpp -- the file itself is the
single source of truth, so there is no slug checklist to maintain here.
"""

import random
import re
import sys
from pathlib import Path

DSA = Path(__file__).resolve().parent.parent / "dsa"
LEETCODE_RE = re.compile(r"^https://leetcode\.com/problems/[\w-]+/$")


def header_comment(text: str) -> list[str]:
    """Leading '// ...' comment block of a file, as bare text lines.

    Stops at the first line that is neither a comment nor blank.
    """
    out: list[str] = []
    for line in text.splitlines():
        stripped = line.strip()
        if stripped.startswith("//"):
            out.append(stripped[2:].strip())
        elif stripped == "":
            if out:
                out.append("")
        else:
            break
    while out and out[-1] == "":
        out.pop()
    return out


def prettify(name: str) -> str:
    tokens = name.split("_")
    return " ".join(t[:1].upper() + t[1:] for t in tokens)


def report(dir_path: Path) -> int:
    number, _, name = dir_path.name.partition("_")
    print(f"#{number} - {prettify(name)}")
    print(f"  dir:  dsa/{dir_path.name}")

    solution = dir_path / "solution.cpp"
    if not solution.is_file():
        print("  note: dsa folder exists but solution.cpp is missing")
        return 0

    lines = header_comment(solution.read_text())
    if not lines or not lines[0].startswith("Problem:"):
        print("  note: missing '// Problem:' header in solution.cpp")
        return 0

    first = lines[0][len("Problem:"):].strip()
    if first.startswith("https://leetcode.com/"):
        if not LEETCODE_RE.match(first):
            print(f"  note: first line URL does not look like LeetCode: {first}")
        print(f"  url:  {first}")
    else:
        print("  url:  -- (not a LeetCode problem) --")
        for extra in lines[1:]:
            print(f"        {extra}")
    return 0


def main() -> int:
    dirs = sorted(
        d for d in DSA.iterdir() if d.is_dir() and re.match(r"^\d+_", d.name)
    )
    if not dirs:
        print(f"No problem directories found under {DSA}", file=sys.stderr)
        return 1

    return report(random.choice(dirs))


if __name__ == "__main__":
    raise SystemExit(main())