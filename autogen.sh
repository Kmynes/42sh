#!/usr/bin/env bash

mkdir -p build

cd build

cmake ..

make

./42sh

cd ..

rm -r build