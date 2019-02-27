#!/usr/bin/env bash
git stash -q --keep-index
make check
RESULT=$?
git stash pop -q
if [ $RESULT -ne 0 ]; then
    printf "\nmake check failed\nFix it before you can commit or use
git commit --no-verify to skip verification"
    exit 1
fi
exit 0