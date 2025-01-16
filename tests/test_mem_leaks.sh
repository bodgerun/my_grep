#!/bin/bash

if [ $# -lt 1 ]; then
  echo "Usage: ./test_mem_leaks.sh INPUT ..."
  exit -1
fi

source ../tests/utils.sh

log=../tests/leaks_log.txt
fails=0

__header__ "my_grep - leaks"

for input in $@; do
  while IFS= read line; do
    leaks > $log 2>&1 -atExit -- ./my_grep $line

    if [ $? -eq 0 ]; then
      echo $green"OK:   $line"$reset
    else
      if [ $fails -lt 255 ]; then
        (( fails++ ))
      fi
      cat $log | grep LEAK:
      echo $red"FAIL: $line"$reset
    fi
  done < $input
done

__footer__ $fails

rm -f $log

exit $fails
