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


def report(dir_path: Path) -> dict:
    number, _, name = dir_path.name.partition("_")
    payload: dict = {
        "number": int(number),
        "title": prettify(name),
        "dir": f"dsa/{dir_path.name}",
        "url": None,
        "source": None,
        "description": None,
        "note": None,
    }

    solution = dir_path / "solution.cpp"
    if not solution.is_file():
        payload["note"] = "dsa folder exists but solution.cpp is missing"
        return payload

    lines = header_comment(solution.read_text())
    if not lines or not lines[0].startswith("Problem:"):
        payload["note"] = "missing '// Problem:' header in solution.cpp"
        return payload

    first = lines[0][len("Problem:"):].strip()
    if first.startswith("https://leetcode.com/"):
        if not LEETCODE_RE.match(first):
            payload["note"] = f"first line URL does not look like LeetCode: {first}"
        payload["url"] = first
    else:
        # Non-LeetCode problem: rip out the "Source: ..." line for its own
        # field and keep the rest of the comment block as the description.
        description: list[str] = []
        for extra in lines[1:]:
            if extra.startswith("Source:") and payload["source"] is None:
                payload["source"] = extra[len("Source:"):].strip()
            elif extra:
                description.append(extra)
        payload["description"] = description

    return payload


def main() -> int:
    dirs = sorted(
        d for d in DSA.iterdir() if d.is_dir() and re.match(r"^\d+_", d.name)
    )
    if not dirs:
        json.dump({"error": f"No problem directories found under {DSA}"}, sys.stdout)
        return 1

    json.dump(report(random.choice(dirs)), sys.stdout, indent=2, ensure_ascii=False)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())