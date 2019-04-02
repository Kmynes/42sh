#!/usr/bin/env bash

f=0
t=1

if [[$z && $t]]
then
    echo "KO"
fi

if [[$t && $z]]
then
    echo "KO"
fi

if [[$z && $t]]
then
    echo "KO"
fi

if [[$t && $t]]
then
    echo "OK"
fi