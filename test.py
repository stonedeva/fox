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

        build = subprocess.run(f"./build/foxc {dir_name}/{file.name}",
                                capture_output = True,
                                text = True, shell = True)
        print(f"[Test] Compiling {dir_name}/{file.name}")
        if build.returncode != 0:
            print(build.stderr)

        exe = subprocess.run("./output", capture_output=True, 
                                   text=True, shell=True)
        print(f"[Test] Executing ./output")
        
        result = compare_results(file.name.replace(".fox", ".txt"), exe.stdout)
        if exe.returncode != 0 or not result[0]:
            print(f"\nResult for: '{file.name}' is incorrect")
            print("======================")
            print(f"Result: {exe.stdout}")
            print("======================")
            print(f"Expected: {result[1]}")
