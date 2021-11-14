#!/bin/bash
SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
TESTS_FILE=${1:-tests.txt}
PASSING_MUTANTS=${2-passing_mutants.txt}
> ${PASSING_MUTANTS}
for mutant in $(find mutants -type f -name "div.mutant.*.c"); do
    echo "***${mutant}***"
    sh ${SCRIPT_DIR}/build_with_mutant.sh ${mutant} &>/dev/null
    python3 ${SCRIPT_DIR}/run_tests.py -e build/div ${TESTS_FILE}
    exit_code=$?
    if [[ ${exit_code} = 0 ]]; then
        echo ${mutant} >>${PASSING_MUTANTS}
        diff --color ./src/div.c "${mutant}"
    elif [[ ${exit_code} = 2 ]]; then
        echo "***Timeout***"
    elif [[ ${exit_code} = 3 ]]; then
        echo "***Runtime error***"
    fi
done
