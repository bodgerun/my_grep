#!/bin/bash

source ../tests/utils.sh

program=../tests/create_long_line
fname=../tests/long_lines.txt     # to match patterns with
pname=../tests/long_patterns.txt  # to take patterns from
out_0=../tests/out_orig.txt
out_1=../tests/out_mine.txt
fails=0

gcc -Wall -Wextra -Werror -std=c11 $program.c -o $program

# creating a file with 4 very long lines:
$program $fname 97 1000000
$program $fname 98 1000000
$program $fname 99 1000000
$program $fname 100 1000000

# creating a file with 2 long patterns:
$program $pname 100 5000
$program $pname 101 5000

__header__ "my_grep - long lines"

grep      -f $pname $fname > $out_0
code_0=$?
./my_grep -f $pname $fname > $out_1
code_1=$?
diff $out_0 $out_1    

if [ $? -eq 0 ]; then
  echo $green"OK: outputs are the same"$reset
else
  (( fails++ ))
  echo $red"FAIL: outputs differ"$reset
fi

if [ $code_0 -eq $code_1 ]; then
  echo $green"OK: codes are the same ($code_0 : $code_1)"$reset
else 
  (( fails++ ))
  echo $red"FAIL: codes differ ($code_0 : $code_1)"$reset
fi

__border__

rm -f $program $pname $fname $out_0 $out_1

exit $fails
