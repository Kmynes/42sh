#!/bin/bash

red="\x1B[31m"
green="\x1B[32m"

clear
printf "Your are in the docker container\n\n"
rm -rf build

printf "Running of test it will take a while..."
make test

if [ $? -eq 0 ]; then
  printf "Docker test complete with ${green}[SUCESS]"
else
  printf "Docker test complete with ${red}[ERROR]"
fi

rm -rf build
exit