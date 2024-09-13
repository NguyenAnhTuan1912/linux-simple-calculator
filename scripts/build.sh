#!/bin/bash

excludeFiles="install"
definitionFilePaths=$(find . -name "*.cpp" | grep -iv $excludeFiles | tr "\n" " ")
declarationFilePaths="./lib"
output="bin"
filename="tunacalc"

# Build
g++ -I./include -o "$output/$filename" $definitionFilePaths
g++ install.cpp -o "$output/install"