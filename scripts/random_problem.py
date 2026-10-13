#!/usr/bin/env python3
"""Pick a random problem from the dsa/ problem set to practice.

Emits a single JSON object on stdout so it can be piped through nushell's
`from json`, jq, or any other JSON tool:

    just random | from json          # nushell: record/table + tabulate
    just random | jq '.url'          # bash: extract the URL

The problem URL (or, for non-LeetCode problems, the problem description)
comes from the first line of each solution.cpp -- the file itself is the
single source of truth, so there is no slug checklist to maintain here.
"""

import json
import random
import sys

from problem_meta import DSA, problem_dirs, report


def main() -> int:
    dirs = problem_dirs()
    if not dirs:
        json.dump({"error": f"No problem directories found under {DSA}"}, sys.stdout)
        return 1

    json.dump(report(random.choice(dirs)), sys.stdout, indent=2, ensure_ascii=False)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
