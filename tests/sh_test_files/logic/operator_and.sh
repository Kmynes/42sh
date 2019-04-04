#!/usr/bin/env bash

f=0
t=1

if [[ $f && $t ]]
then
    echo "KO"
fi

if [[ $t && $f ]]
then
    echo "KO"
fi

if [[ $f && $t ]]
then
    echo "KO"
fi

if [[ $t && $t ]]
then
    echo "OK"
fi