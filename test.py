#!/usr/bin/env python3
from pathlib import Path
import subprocess
import sys

dir_name = "tests"
if len(sys.argv) > 1:
    dir_name = sys.argv[1]

directory = Path(dir_name)

def compare_results(path, output):
    with open(f"{dir_name}/{path}", "r") as file:
        content = file.read()
    return (output == content), content

for file in directory.iterdir():
    if file.is_file():
        if not file.name.endswith(".fox"):
            continue

        subprocess.run(["./build/foxc", f"{dir_name}/{file.name}"])
        execution = subprocess.run("./output", capture_output=True, text=True, shell=True)

        result = compare_results(file.name.replace(".fox", ".txt"), execution.stdout)
        if not result[0]:
            print(f"\nResult for: '{file.name}' is incorrect")
            print("======================")
            print(f"Result: {execution.stdout}")
            print("======================")
            print(f"Expected: {result[1]}")
