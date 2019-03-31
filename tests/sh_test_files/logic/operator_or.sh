#!/usr/bin/env bash
if [[0 || 0]]
then
    echo "KO"
fi

if [[1 || 0]]
then
    echo "OK"
fi

if [[0 || 1]]
then
    echo "OK"
fi

if [[1 || 1]]
then
    echo "OK"
fi