#!/bin/bash

if [ $# -lt 1 ]; then
  echo "Usage: ./test_4_code_man.sh INPUT ..."
  exit -1
fi

source ../tests/utils.sh

fails=0

__header__ "my_grep - code - man"

for input in $@; do
  while IFS= read line; do  
    grep      $line > /dev/null 2>&1
    code_0=$?
    ./my_grep $line > /dev/null 2>&1
    code_1=$?

    if [ $code_0 -eq $code_1 ] || ([ $code_0 -gt 1 ] && [ $code_1 -gt 1 ]); then
      echo $green"OK   ($code_0 : $code_1):	$line"$reset
    else
      if [ $fails -lt 255 ]; then
        (( fails++ ))
      fi
      echo $red"FAIL ($code_0 : $code_1):	$line"$reset
    fi
  done < $input
done

__footer__ $fails

exit $fails
