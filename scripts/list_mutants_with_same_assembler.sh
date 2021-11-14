#!/bin/bash
MUTANTS_LIST_FILE=${1:-passing_mutants.txt}

remove_first_line() {
    tail -n +2 "$1"
}

gcc -S -o div.s ./src/div.c

for mutant in $(cat "${MUTANTS_LIST_FILE}"); do
    gcc -S -o div_mutant.s ${mutant} &>/dev/null
    diff <(remove_first_line div.s) <(remove_first_line div_mutant.s) &>/dev/null && \
    { echo ${mutant}; diff --color ./src/div.c ${mutant} >&2; }
done

rm div.s div_mutant.s
