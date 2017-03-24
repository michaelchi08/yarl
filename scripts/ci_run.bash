#!/bin/bash
set -e  # exit on first error

compile() {
    make
}

run_module_tests() {
    cd $1 && ./tests/$1_tests --silence-stdcout && cd -
}

# MAIN
compile
# run_module_tests wave_utils
# run_module_tests wave_optimization
