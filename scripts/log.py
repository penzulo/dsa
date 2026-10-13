#!/usr/bin/env python3
"""Practice diary for the dsa/ problem set.

Keeps a git-ignored journal/ of markdown notes -- the private record of what
was attempted, what went wrong and what to review:

    journal/daily/YYYY-MM-DD.md   one file per timed session
    journal/topics/<concept>.md   evolving notes per DSA concept

Only the journal/ data is ignored; this script and templates/journal_*.md are
tracked, so the setup survives a fresh clone.

Subcommands (all print JSON on stdout, ready for nushell `from json`):

    today                 scaffold (or reopen) today's daily entry
    add NNNN [--date D]   append a blank problem section to a daily entry
    topics [NAME]         list topic notes, or scaffold/open one
    summary               aggregate every logged attempt
"""

import argparse
import datetime as dt
import json
import os
import re
import subprocess
import sys
from pathlib import Path

import problem_meta

JOURNAL = problem_meta.ROOT / "journal"
DAILY = JOURNAL / "daily"
TOPICS = JOURNAL / "topics"
DAILY_TEMPLATE = problem_meta.ROOT / "templates" / "journal_daily.md"
TOPIC_TEMPLATE = problem_meta.ROOT / "templates" / "journal_topic.md"

HEADING_RE = re.compile(r"^##\s+(\d+)\s+(.*?)\s*$")
FIELD_RE = re.compile(r"^(timeLeft|score|tags):\s*(.*)$")
EMOJI_OUTCOME = {"\u2705": "done", "\u26a0\ufe0f": "partial", "\u274c": "failed"}
OUTCOMES = ("done", "partial", "failed")


def slugify(name: str) -> str:
    return re.sub(r"[\s_]+", "-", name.strip().lower())


def problem_section(number: int, title: str) -> str:
    return (
        f"## {number:04d} {title} \u2014 \u2b1c\n"
        "\n"
        "timeLeft: \u2014\n"
        "score: \u2014\n"
        "tags: \n"
        "\n"
        "- **missed**:\n"
        "- **correct**:\n"
        "- **couldn't see**:\n"
        "- **review**:\n"
    )


def open_or_report(path: Path, created: bool, do_open: bool) -> dict:
    opened = False
    if do_open:
        editor = os.environ.get("EDITOR")
        if editor:
            subprocess.run([editor, str(path)], check=False)
            opened = True
    return {"path": str(path), "created": created, "opened": opened}


def scaffold(path: Path, template: Path, token: str, value: str) -> bool:
    """Create `path` from `template` if absent; True when it was created."""
    if path.exists():
        return False
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(template.read_text().replace(token, value))
    return True


def cmd_today(args) -> dict:
    path = DAILY / f"{dt.date.today().isoformat()}.md"
    created = scaffold(path, DAILY_TEMPLATE, "{date}", path.stem)
    return open_or_report(path, created, args.open)


def cmd_add(args) -> dict:
    date = args.date or dt.date.today().isoformat()
    path = DAILY / f"{date}.md"
    payload: dict = {"date": date, "path": str(path), "added": False, "note": None}

    directory = problem_meta.find(args.number)
    if directory is None:
        payload["note"] = f"no dsa/ problem directory for number {args.number}"
        return payload

    meta = problem_meta.report(directory)
    number = meta["number"]
    payload["number"] = number
    payload["title"] = meta["title"]
    payload["url"] = meta["url"]

    if path.exists():
        text = path.read_text()
    else:
        path.parent.mkdir(parents=True, exist_ok=True)
        text = DAILY_TEMPLATE.read_text().replace("{date}", date)

    if re.search(rf"^##\s+0*{number}\b", text, re.M):
        payload["note"] = f"section for {number:04d} already present"
        return payload

    if not text.endswith("\n"):
        text += "\n"
    path.write_text(text + "\n" + problem_section(number, meta["title"]))
    payload["added"] = True
    return payload


def cmd_topics(args) -> dict:
    if not args.name:
        TOPICS.mkdir(parents=True, exist_ok=True)
        return {
            "topics": [
                {"name": p.stem, "path": str(p)} for p in sorted(TOPICS.glob("*.md"))
            ]
        }
    name = args.name.strip()
    path = TOPICS / f"{slugify(name)}.md"
    created = scaffold(path, TOPIC_TEMPLATE, "{name}", name)
    return open_or_report(path, created, args.open)


def parse_daily(path: Path) -> list[dict]:
    attempts: list[dict] = []
    current: dict | None = None
    for line in path.read_text().splitlines():
        heading = HEADING_RE.match(line)
        if heading:
            if current:
                attempts.append(current)
            number = int(heading.group(1))
            rest = heading.group(2)
            title, outcome = rest, None
            if "\u2014" in rest:
                title, _, right = rest.partition("\u2014")
                title, right = title.strip(), right.strip()
                outcome = next((o for o in OUTCOMES if o in right), None)
                if outcome is None:
                    outcome = next(
                        (o for e, o in EMOJI_OUTCOME.items() if right.startswith(e)),
                        None,
                    )
            current = {
                "date": path.stem,
                "number": number,
                "title": title,
                "outcome": outcome,
                "timeLeft": None,
                "score": None,
                "tags": [],
            }
            continue
        if current is not None:
            field = FIELD_RE.match(line)
            if field:
                key, value = field.group(1), field.group(2).strip()
                if key == "tags":
                    current["tags"] = [t.strip() for t in value.split(",") if t.strip()]
                else:
                    current[key] = value or None
    if current:
        attempts.append(current)
    return attempts


def cmd_summary(args) -> dict:
    DAILY.mkdir(parents=True, exist_ok=True)
    files = sorted(DAILY.glob("*.md"))

    attempts: list[dict] = []
    for f in files:
        attempts.extend(parse_daily(f))

    by_outcome = {o: 0 for o in OUTCOMES}
    by_tag: dict[str, dict] = {}
    for a in attempts:
        if a["outcome"] in by_outcome:
            by_outcome[a["outcome"]] += 1
        for tag in a["tags"]:
            entry = by_tag.setdefault(
                tag, {"attempts": 0, "done": 0, "partial": 0, "failed": 0}
            )
            entry["attempts"] += 1
            if a["outcome"] in entry:
                entry[a["outcome"]] += 1

    return {
        "days": len(files),
        "attempts": len(attempts),
        "by_outcome": by_outcome,
        "by_tag": by_tag,
        "flagged": sorted(
            a["number"] for a in attempts if a["outcome"] in ("partial", "failed")
        ),
        "problems": attempts,
    }


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="Practice diary for dsa/ problems.")
    sub = parser.add_subparsers(dest="command", required=True)

    today = sub.add_parser("today", help="scaffold/open today's daily entry")
    today.add_argument("--open", action="store_true", help="open in $EDITOR")
    today.set_defaults(func=cmd_today)

    add = sub.add_parser("add", help="append a blank section for a problem")
    add.add_argument("number", help="problem number, e.g. 0102")
    add.add_argument("--date", help="target date (YYYY-MM-DD), default today")
    add.set_defaults(func=cmd_add)

    topics = sub.add_parser("topics", help="list or scaffold a topic note")
    topics.add_argument("name", nargs="?", default="", help="topic, e.g. bfs")
    topics.add_argument("--open", action="store_true", help="open in $EDITOR")
    topics.set_defaults(func=cmd_topics)

    summary = sub.add_parser("summary", help="aggregate every logged attempt")
    summary.set_defaults(func=cmd_summary)

    return parser


def main() -> int:
    args = build_parser().parse_args()
    json.dump(args.func(args), sys.stdout, indent=2, ensure_ascii=False)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
