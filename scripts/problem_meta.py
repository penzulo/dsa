#!/usr/bin/env python3
"""Shared helpers for reading problem metadata out of the dsa/ tree.

The single source of truth for a problem's number, directory, title, URL and
(for non-LeetCode problems) description is the leading '// Problem:' comment
block of its solution.cpp. The random picker and the practice diary both go
through here so that convention is parsed in exactly one place.
"""

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DSA = ROOT / "dsa"
LEETCODE_RE = re.compile(r"^https://leetcode\.com/problems/[\w-]+/$")
DIR_RE = re.compile(r"^\d+_")


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


def split_name(dir_name: str) -> tuple[str, str]:
    """'0102_binary_tree_level_order_traversal' -> ('0102', 'binary_tree...')."""
    number, _, name = dir_name.partition("_")
    return number, name


def problem_dirs() -> list[Path]:
    """Every dsa/<number>_<name> directory, sorted."""
    return sorted(
        d for d in DSA.iterdir() if d.is_dir() and DIR_RE.match(d.name)
    )


def find(number: str | int) -> Path | None:
    """Problem directory whose numeric prefix equals `number` ('102' / '0102')."""
    want = int(number)
    for d in problem_dirs():
        head = d.name.split("_", 1)[0]
        if head.isdigit() and int(head) == want:
            return d
    return None


def report(dir_path: Path) -> dict:
    """Metadata for one problem directory, derived from its header comment."""
    number, name = split_name(dir_path.name)
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
