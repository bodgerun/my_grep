#!/bin/bash

if [ $# -lt 1 ]; then
  echo "Usage: ./test_diff_man.sh INPUT ..."
  exit -1
fi

source ../tests/utils.sh

out_0=out_orig.txt
out_1=out_mine.txt
fails=0

__header__ "my_grep - diff - man"

for input in $@; do
  while IFS= read line; do
    grep      $line > $out_0
    ./my_grep $line > $out_1
    diff $out_0 $out_1

    if [ $? -eq 0 ]; then
      echo $green"OK:   $line"$reset
    else
      if [ $fails -lt 255 ]; then
        (( fails++ ))
      fi
      echo $red"FAIL: $line"$reset
    fi
  done < $input
done

__footer__ $fails

rm -f $out_0 $out_1

exit $fails
