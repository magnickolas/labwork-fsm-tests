#!/bin/bash
MUTANT=${1:-./src/div.c}
rm -rf build
cmake -S. -Bbuild -DDIV_C=${MUTANT}
cmake --build build
