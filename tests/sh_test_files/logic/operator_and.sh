#!/usr/bin/env bash
if [[0 && 0]]
then
    echo "KO"
fi

if [[1 && 0]]
then
    echo "KO"
fi

if [[0 && 1]]
then
    echo "KO"
fi

if [[1 && 1]]
then
    echo "OK"
fi