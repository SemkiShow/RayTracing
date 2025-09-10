#!/bin/bash

set -e
shopt -s globstar

if [ -z "$1" ]; then
    echo "You must specify the release version!"
    exit 1
fi

# Compiling for Linux
mkdir -p build_release
cmake -B build_release -DCMAKE_BUILD_TYPE=Release
cmake --build build_release -j${nproc}
cp build_release/bin/main .

# Compiling for Windows
mkdir -p build_release_windows
cmake -B build_release_windows -DCMAKE_TOOLCHAIN_FILE=mingw-w64-x86_64.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build_release_windows -j${nproc}
cp build_release_windows/bin/main.exe .

# Zipping the build
zip release.zip main main.exe
rm main main.exe

# Creating a GitHub release
gh release create $1 release.zip
rm release.zip
