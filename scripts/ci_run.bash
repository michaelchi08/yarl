#!/bin/bash
set -e  # exit on first error
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}" )" && pwd)"
CMAKE_CONFIG_DIR="../cmake"  # cmake folder relative to this script


# submodules
git submodule init
git submodule update

# compile
mkdir -p build
cd build
cmake .. -DCMAKE_MODULE_PATH=$DIR/$CMAKE_CONFIG_DIR
make

# run tests
export LD_LIBRARY_PATH=/usr/local/lib
./tests/yarl_tests --silence-stdout
