import argparse
from typing import Iterator, Tuple
import subprocess
from sys import exit
from enum import Enum


def iter_test_samples(filename: str) -> Iterator[Tuple[str, str]]:
    with open(filename, "r") as test_file:
        for test in test_file.readlines():
            test_input, test_output = map(
                lambda x: "".join(x),
                zip(*map(lambda x: x.split("/"), test.strip().split())),
            )
            yield test_input, test_output


class TestingResult(Enum):
    SUCCESS = 0
    INCORRECT = 1
    TIMEOUT = 2
    ERROR = 3


def run_tests(*, tests_filename: str, executable: str, verbose: bool) -> TestingResult:
    for test_input, test_output in iter_test_samples(tests_filename):
        try:
            output = subprocess.check_output(
                [executable], input=test_input.encode(), timeout=1
            ).decode()
        except subprocess.TimeoutExpired:
            return TestingResult.TIMEOUT
        except subprocess.CalledProcessError:
            return TestingResult.ERROR
        assert type(output) is type(test_output)
        if output != test_output:
            if verbose:
                print("Failed on input:", test_input)
                print("Program output:", output)
                print("Expected output:", test_output)
            return TestingResult.INCORRECT
    return TestingResult.SUCCESS


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("filename", type=str, help="Input FSM file")
    parser.add_argument(
        "-e", "--executable", type=str, help="Executable path", required=True
    )
    parser.add_argument(
        "-v", "--verbose", action="store_true", help="Whether to print fail case"
    )
    args = parser.parse_args()
    exit(
        run_tests(
            tests_filename=args.filename,
            executable=args.executable,
            verbose=args.verbose,
        ).value
    )
