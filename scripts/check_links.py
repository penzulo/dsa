#!/usr/bin/env python3
"""Verify every problem file carries a '// Problem:' header.

Checks, for each dsa/*/<file> with <file> in {solution.cpp,
solution_suboptimal.cpp, solution_wrong.cpp}:
  - the first line starts with '// Problem:' (so the URL/description is
    never split across lines by clang-format, which is told to leave
    '// Problem:' comments untouched via CommentPragmas);
  - any LeetCode URL matches https://leetcode.com/problems/<slug>/.

Non-LeetCode headers (e.g. the 9xxx company-OA problems) only need the
'// Problem:' prefix; their description lines are free-form.

Exits non-zero when any file violates the rules.
"""

import re
import sys
from pathlib import Path

DSA = Path(__file__).resolve().parent.parent / "dsa"
SUPPORTED = ("solution.cpp", "solution_suboptimal.cpp", "solution_wrong.cpp")
LEETCODE_RE = re.compile(r"^https://leetcode\.com/problems/[\w-]+/$")


def main() -> int:
    bad = 0
    for d in sorted(DSA.iterdir()):
        if not d.is_dir():
            continue
        for name in SUPPORTED:
            f = d / name
            if not f.is_file():
                continue
            first = f.read_text().splitlines()[0]
            if not first.startswith("// Problem:"):
                print(f"{f}: first line must start with '// Problem:'")
                bad += 1
                continue
            url = first[len("// Problem:"):].strip()
            if url.startswith("https://leetcode.com/") and not LEETCODE_RE.match(url):
                print(f"{f}: malformed LeetCode URL: {url}")
                bad += 1

    if bad:
        print(f"{bad} file(s) failed the header check", file=sys.stderr)
        return 1
    print("All problem headers OK")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())