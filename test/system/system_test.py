import sys
import os
import importlib
import subprocess
import filecmp
import argparse
import json
import pexpect
import time

def setup_output_dir(output_dir):
    if not os.path.exists(output_dir):
        os.mkdir(output_dir)

def execute_query(process, prompt, query, searchwindowsize=50):
    time_start = time.perf_counter()
    for line in query:
        process.send(line)
        process.expect(prompt, searchwindowsize=searchwindowsize)
    time_end = time.perf_counter()
    return time_end - time_start

def execute_testcase(exe, case_path, out_path, timing=False):
    with open(case_path) as fp:
        content = fp.readlines()
    if timing:
        # Assume select query appear after all insert query
        insert_content = filter(lambda l: l.startswith('insert'), content)
        select_content = filter(lambda l: l.startswith('select'), content)
        # Setup child process
        prompt = 'db > '
        out_file = open(out_path, 'w')
        p = pexpect.spawnu(exe, timeout=None, echo=False)
        p.delaybeforesend = None
        p.logfile_read = out_file
        p.expect(prompt)
        # Measure insert time
        insert_time = execute_query(p, prompt, insert_content)
        # Measure select time
        select_time = execute_query(p, prompt, select_content)
        # Exit program
        p.sendline('.exit')
        p.wait()
        out_file.close()
    else:
        content.insert(0, ".output {out_path}\n".format(out_path=out_path))
        p = subprocess.Popen([exe], stdin=subprocess.PIPE)
        for line in content:
            p.stdin.write(line.encode())
        p.stdin.close()
        try:
            p.wait(timeout=30)
        except subprocess.TimeoutExpired:
            print("Timeout")

def execute_testsuite(exe, suite_path, suite_out_path, suite_ans_path, n_timing):
    correct_count = 0
    suite_name = os.path.basename(suite_path)
    suite_mod_path = os.path.join(suite_path, "suite.py")
    suite = None
    if os.path.exists(suite_mod_path):
        module_path = ".".join(["testcases", suite_name, "suite"])
        mod = importlib.import_module(module_path)
        suite = getattr(mod, "Suite")

    case_files = list()
    for name in os.listdir(suite_path):
        if name.startswith("t") and name.endswith(".txt"):
            case_files.append(name)

    print("Starting test suite ``{suite}``".format(suite=suite_name))
    failed_cases = list()
    for case in sorted(case_files):
        if suite:
            suite.setUp()

        case_path = os.path.join(suite_path, case)
        out_path = os.path.join(suite_out_path, case)
        ans_path = os.path.join(suite_ans_path, case)

        if n_timing == 0:
            execute_testcase(exe, case_path, out_path, timing=False)
        else:
            execute_testcase(exe, case_path, out_path, timing=True)

        if suite:
            suite.tearDown()

        if os.path.isfile(out_path):
            is_result_match = filecmp.cmp(out_path, ans_path)
        else:
            is_result_match = False

        if is_result_match:
            print("The test file {case} passed".format(case=case))
            correct_count += 1
        else:
            print("The test file {case} failed".format(case=case))
            failed_cases.append(case)

    print("The test suite ``{}`` total passed {}/{}".format(suite_name,
            correct_count, len(case_files)))
    print("Failed cases: {}".format(failed_cases))
    print()
    return correct_count, len(case_files), failed_cases

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("shell", help="The path of the compiled shell")
    parser.add_argument("test_case", help="The test case to be run, default: all", nargs="*", default="all")
    parser.add_argument("--exclude", help="The excluded test cases don't need to run", nargs="*", default=[])
    parser.add_argument("-t", "--timing", help="Number of times for timing test cases", type=int, default=0)
    args = parser.parse_args()

    if not isinstance(args.test_case, list):
        args.test_case = "all"
    
    file_path = os.path.dirname(__file__)
    testcase_path = os.path.join(file_path, "testcases")
    output_path = os.path.join(file_path, "output")
    answer_path = os.path.join(file_path, "answer")
    n_timing = args.timing

    if args.test_case == "all":
        args.test_case = os.listdir(testcase_path)
    
    for e_test_case in args.exclude:
        args.test_case.remove(e_test_case)

    result = dict()
    for test_suite in args.test_case:
        if test_suite == "__pycache__":
            continue

        suite_path = os.path.join(testcase_path, test_suite)
        suite_out_path = os.path.join(output_path, test_suite)
        suite_ans_path = os.path.join(answer_path, test_suite)

        if os.path.isdir(suite_path):
            result[test_suite] = dict()
            setup_output_dir(suite_out_path)
            ret = execute_testsuite(sys.argv[1], suite_path, suite_out_path, suite_ans_path, n_timing)
            correct_count, total_count, failed_cases = ret
            result[test_suite]["correct"] = correct_count
            result[test_suite]["total"] = total_count
            result[test_suite]["failed"] = failed_cases

    with open("result.json", "w") as fp:
        json.dump(result, fp)


if __name__ == "__main__":
    main()
