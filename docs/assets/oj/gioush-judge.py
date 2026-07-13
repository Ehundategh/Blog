#!/usr/bin/env python3
import argparse
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import time
import urllib.request
import zipfile
from datetime import datetime, timezone
from pathlib import Path

DEFAULT_MANIFEST = "https://ehundategh.github.io/Blog/oj/problems.json"


def home_dir():
    return Path.home() / ".gioush-judge"


def cache_dir():
    path = home_dir() / "cache"
    path.mkdir(parents=True, exist_ok=True)
    return path


def records_path():
    home_dir().mkdir(parents=True, exist_ok=True)
    return home_dir() / "records.json"


def profile_path():
    home_dir().mkdir(parents=True, exist_ok=True)
    return home_dir() / "profile.json"


def now_iso():
    return datetime.now(timezone.utc).isoformat()


def load_profile():
    path = profile_path()
    if not path.exists():
        return {"name": "", "handle": ""}
    return json.loads(path.read_text(encoding="utf-8-sig"))


def save_profile(profile):
    profile_path().write_text(json.dumps(profile, ensure_ascii=False, indent=2), encoding="utf-8")


def read_text_or_url(source):
    if re.match(r"^https?://", source):
        with urllib.request.urlopen(source) as response:
            return response.read().decode("utf-8-sig")
    return Path(source).read_text(encoding="utf-8-sig")


def load_manifest(source):
    return json.loads(read_text_or_url(source))


def problem_map(manifest):
    return {problem["id"]: problem for problem in manifest["problems"]}


def download(url, dest):
    dest.parent.mkdir(parents=True, exist_ok=True)
    if dest.exists() and dest.stat().st_size > 0:
        return dest
    print(f"Downloading {url}")
    with urllib.request.urlopen(url) as response:
        data = response.read()
    dest.write_bytes(data)
    return dest


def natural_key(text):
    return [int(part) if part.isdigit() else part.lower() for part in re.split(r"(\d+)", text)]


def collect_cases(zip_path, problem_id):
    extract_dir = cache_dir() / problem_id / "data"
    if extract_dir.exists():
        shutil.rmtree(extract_dir)
    extract_dir.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(zip_path) as archive:
        archive.extractall(extract_dir)

    inputs = {}
    answers = {}
    for path in extract_dir.rglob("*"):
        if not path.is_file():
            continue
        suffix = path.suffix.lower()
        if suffix not in (".in", ".ans"):
            continue
        key = path.with_suffix("").name
        if suffix == ".in":
            inputs[key] = path
        else:
            answers[key] = path

    cases = []
    for key in sorted(inputs.keys(), key=natural_key):
        if key in answers:
            cases.append((key, inputs[key], answers[key]))
    if not cases:
        raise RuntimeError("No .in/.ans cases found in data zip")
    return cases


def compile_cpp(source, out_exe):
    compiler = shutil.which("g++")
    if compiler is None:
        raise RuntimeError("g++ not found in PATH")
    cmd = [compiler, str(source), "-std=c++17", "-O2", "-pipe", "-o", str(out_exe)]
    print("Compiling:", " ".join(cmd))
    started = time.perf_counter()
    proc = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    elapsed = time.perf_counter() - started
    if proc.returncode != 0:
        print(proc.stdout, end="")
        print(proc.stderr, end="", file=sys.stderr)
        raise RuntimeError("Compile Error")
    print(f"Compile OK ({elapsed:.2f}s)")


def tokens(path_or_text, is_path=True):
    if is_path:
        text = Path(path_or_text).read_text(errors="replace")
    else:
        text = path_or_text
    return text.split()


def compare_output(expected_path, actual_text):
    return tokens(expected_path, True) == tokens(actual_text, False)


def run_case(exe, case_name, input_path, answer_path, problem, work_root):
    case_dir = work_root / case_name
    case_dir.mkdir(parents=True, exist_ok=True)

    input_file = problem.get("inputFile")
    output_file = problem.get("outputFile")
    if input_file:
        shutil.copyfile(input_path, case_dir / input_file)

    input_data = input_path.read_bytes()
    timeout = max(1, int(problem.get("timeLimitMs", 1000)) / 1000.0 * 3)
    started = time.perf_counter()
    try:
        proc = subprocess.run(
            [str(exe)],
            input=input_data,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            cwd=case_dir,
            timeout=timeout,
        )
        elapsed_ms = int((time.perf_counter() - started) * 1000)
    except subprocess.TimeoutExpired:
        return {"case": case_name, "result": "TLE", "timeMs": int(timeout * 1000)}

    if proc.returncode != 0:
        return {"case": case_name, "result": "RE", "timeMs": elapsed_ms}

    out_path = case_dir / output_file if output_file else None
    if out_path and out_path.exists():
        actual = out_path.read_text(errors="replace")
    else:
        actual = proc.stdout.decode(errors="replace")

    ok = compare_output(answer_path, actual)
    return {"case": case_name, "result": "AC" if ok else "WA", "timeMs": elapsed_ms}


def load_records():
    path = records_path()
    if not path.exists():
        return {}
    return json.loads(path.read_text(encoding="utf-8-sig"))


def save_record(problem, source, results, score):
    records = load_records()
    pid = problem["id"]
    accepted = all(item["result"] == "AC" for item in results)
    entry = {
        "time": now_iso(),
        "source": str(source),
        "score": score,
        "result": "AC" if accepted else "Unaccepted",
        "profile": load_profile(),
        "cases": results,
    }
    old = records.get(pid, {})
    submissions = old.get("submissions", [])
    submissions.append(entry)
    records[pid] = {
        "title": problem["title"],
        "bestScore": max(int(old.get("bestScore", 0)), score),
        "accepted": bool(old.get("accepted", False)) or accepted,
        "lastRunAt": entry["time"],
        "submissions": submissions[-30:],
    }
    records_path().write_text(json.dumps(records, ensure_ascii=False, indent=2), encoding="utf-8")


def command_list(args):
    manifest = load_manifest(args.manifest)
    for problem in manifest["problems"]:
        print(f"{problem['id']:<24} {problem['title']}  ({problem['source']})")


def command_records(args):
    records = load_records()
    if not records:
        print("No local records.")
        return
    for pid, item in records.items():
        mark = "AC" if item.get("accepted") else str(item.get("bestScore", 0))
        print(f"{pid:<24} {mark:<4} {item.get('title', '')}")


def command_profile(args):
    profile = load_profile()
    changed = False
    if args.name is not None:
        profile["name"] = args.name
        changed = True
    if args.handle is not None:
        profile["handle"] = args.handle
        changed = True
    if changed:
        profile["updatedAt"] = now_iso()
        save_profile(profile)
    print("Profile")
    print(f"  name:   {profile.get('name', '')}")
    print(f"  handle: {profile.get('handle', '')}")


def record_for_export(problem_id):
    records = load_records()
    if problem_id not in records:
        raise RuntimeError(f"No local record for {problem_id}")
    item = records[problem_id]
    submissions = item.get("submissions", [])
    if not submissions:
        raise RuntimeError(f"No submissions for {problem_id}")
    return item, submissions[-1]


def build_report(problem, record, submission):
    return {
        "version": 2,
        "exportedAt": now_iso(),
        "profile": submission.get("profile") or load_profile(),
        "problem": {
            "id": problem["id"],
            "title": problem["title"],
            "source": problem.get("source", ""),
            "origin": problem.get("origin", ""),
            "originUrl": problem.get("originUrl", ""),
            "statementUrl": problem.get("statementUrl", ""),
        },
        "record": {
            "bestScore": record.get("bestScore", 0),
            "accepted": bool(record.get("accepted", False)),
            "lastRunAt": record.get("lastRunAt", ""),
        },
        "submission": submission,
    }


def report_markdown(report):
    profile = report["profile"]
    problem = report["problem"]
    submission = report["submission"]
    lines = [
        "# Gioush Judge Report",
        "",
        f"- 选手：{profile.get('name') or '-'}",
        f"- Handle：{profile.get('handle') or '-'}",
        f"- 题目：{problem['title']} (`{problem['id']}`)",
        f"- 场次：{problem.get('source') or '-'}",
    ]
    if problem.get("origin"):
        if problem.get("originUrl"):
            lines.append(f"- 来源：[{problem['origin']}]({problem['originUrl']})")
        else:
            lines.append(f"- 来源：{problem['origin']}")
    lines += [
        f"- 提交时间：{submission.get('time', '')}",
        f"- 源文件：`{submission.get('source', '')}`",
        f"- 结果：{submission.get('result', '')}",
        f"- 分数：{submission.get('score', 0)} / 100",
        "",
        "| 测试点 | 结果 | 时间 |",
        "| --- | --- | --- |",
    ]
    for item in submission.get("cases", []):
        lines.append(f"| `{item.get('case', '')}` | {item.get('result', '')} | {item.get('timeMs', 0)} ms |")
    lines.append("")
    lines.append("本报告由本地评测器生成，只作为补题自测记录。")
    return "\n".join(lines)


def command_export(args):
    manifest = load_manifest(args.manifest)
    problems = problem_map(manifest)
    if args.problem_id not in problems:
        raise RuntimeError(f"Unknown problem id: {args.problem_id}")
    record, submission = record_for_export(args.problem_id)
    report = build_report(problems[args.problem_id], record, submission)

    if args.format == "json":
        text = json.dumps(report, ensure_ascii=False, indent=2)
        suffix = ".json"
    else:
        text = report_markdown(report)
        suffix = ".md"

    out = Path(args.out) if args.out else home_dir() / "exports" / (args.problem_id + suffix)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(text, encoding="utf-8")
    print(out)


def command_run(args):
    manifest = load_manifest(args.manifest)
    problems = problem_map(manifest)
    if args.problem_id not in problems:
        raise RuntimeError(f"Unknown problem id: {args.problem_id}")

    problem = problems[args.problem_id]
    source = Path(args.source).resolve()
    if not source.exists():
        raise RuntimeError(f"Source file not found: {source}")

    print(f"{problem['title']} / {problem['id']}")
    zip_name = problem["id"] + ".zip"
    data_zip = download(problem["dataUrl"], cache_dir() / problem["id" ] / zip_name)
    cases = collect_cases(data_zip, problem["id"])

    with tempfile.TemporaryDirectory(prefix="gioush-judge-") as tmp:
        work_root = Path(tmp)
        exe = work_root / ("main.exe" if os.name == "nt" else "main")
        compile_cpp(source, exe)

        results = []
        for idx, (case_name, input_path, answer_path) in enumerate(cases, 1):
            result = run_case(exe, case_name, input_path, answer_path, problem, work_root)
            results.append(result)
            print(f"#{idx:<3} {result['result']:<3} {result['timeMs']}ms  {case_name}")

    score_each = int(problem.get("tests", {}).get("scoreEach", 100 // max(1, len(results))))
    score = sum(score_each for item in results if item["result"] == "AC")
    score = min(score, 100)
    accepted = all(item["result"] == "AC" for item in results)
    print()
    print(f"Score: {score} / 100")
    print("Result:", "Accepted" if accepted else "Unaccepted")
    save_record(problem, source, results, score)


def build_parser():
    parser = argparse.ArgumentParser(prog="gioush-judge")
    parser.add_argument("--manifest", default=DEFAULT_MANIFEST)
    sub = parser.add_subparsers(dest="command", required=True)

    sub.add_parser("list")

    run = sub.add_parser("run")
    run.add_argument("problem_id")
    run.add_argument("source")

    sub.add_parser("records")

    profile = sub.add_parser("profile")
    profile.add_argument("--name")
    profile.add_argument("--handle")

    export = sub.add_parser("export")
    export.add_argument("problem_id")
    export.add_argument("--format", choices=["json", "md"], default="md")
    export.add_argument("--out")
    return parser


def main():
    parser = build_parser()
    args = parser.parse_args()
    try:
        if args.command == "list":
            command_list(args)
        elif args.command == "run":
            command_run(args)
        elif args.command == "records":
            command_records(args)
        elif args.command == "profile":
            command_profile(args)
        elif args.command == "export":
            command_export(args)
    except Exception as exc:
        print(f"Error: {exc}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
