#!/bin/bash
set -e  # exit on first error

clone_repo() {
    if [ ! -d repo ]
    then
        echo "Clonging repo to current directory"
        git clone https://github.com/chutsu/battery
    else
        echo "Updating battery to latest"
        cd battery
        git pull
        cd -
    fi
}

initialize_gitsubmodules() {
    cd battery
    git submodule init
    git submodule update
    cd -
}

install_deps() {
    cd battery
    bash scripts/install/install_deps.bash
    cd -
}

compile_battery() {
    cd battery
    mkdir -p build
    cd build
    cmake ..
    make
    cd ../..
}

# MAIN
echo "Continuing with this script will:"
echo "1. clone battery to the current directory"
echo "2. download and install its dependencies"
echo "3. compile battery for you"

while true
do
    read -r -p "Do you want to continue? (y/n): " choice
    case "$choice" in
        n|N) break;;
        y|Y)
            clone_battery
            initialize_gitsubmodules
            install_deps
            compile_battery
        break
        ;;
        *) echo 'Invalid input! Please answer y or n!';;
    esac
done
