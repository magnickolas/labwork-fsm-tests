#!/bin/bash
mutate ./src/div.c --mutantDir ./mutants --cmd "./scripts/build_with_mutant.sh MUTANT"
