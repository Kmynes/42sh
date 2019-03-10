#!/usr/bin/env bash

mkdir -p build

cd build

[ "$#" -eq 0 ] && cmake ..

make

