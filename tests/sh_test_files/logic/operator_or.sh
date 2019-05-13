#!/usr/bin/env bash

f=0
t=1

if [[ $f || $f ]]
then
    echo "KO"
fi

if [[ $t || $f ]]
then
    echo "OK"
fi

if [[ $f || $t ]]
then
    echo "OK"
fi

if [[ $t || $t ]]
then
    echo "OK"
fi