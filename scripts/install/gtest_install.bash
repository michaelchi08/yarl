#!/bin/bash
set -e

sudo apt-get install -qq libgtest-dev
cd /usr/src/gtest
sudo mkdir build && cd build
sudo cmake .. && sudo make
sudo cp *.a /usr/lib
