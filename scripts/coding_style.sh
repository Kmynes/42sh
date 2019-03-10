#!/usr/bin/env bash

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color]'


fail() {
    echo -e "${RED}----- $1 -----${NC}"
    echo -e "\n${RED}----- coding style failed -----${NC}"
    exit 1
}

succeed() {
    echo -e "${GREEN}----- $1 -----${NC}"
}

last_char_blank() {
    c=$(tail -c 1 "$1")
    [[ -z "${c// }" ]] && return 1 || return 0
}

filenames=$(find src tests -name *.c -o -name *.h)

# test 80 chars
grep -R '.\{80\}' $filenames
[ "$?" -eq 0 ] && fail "lines > 80 chars"

# test braces
grep -R ') {' $filenames
[ "$?" -eq 0 ] && fail "braces problem"
grep -R '){' $filenames
[ "$?" -eq 0 ] && fail "braces problem"

# test blank
# end_blank=0
# for filename in $filenames; do
#    last_char_blank $filename
#    [ $? -eq 1 ] && end_blank=1 && echo $filename
# done
# [ $end_blank = 1 ] && fail "end : no blank char"

succeed "coding style passed"

