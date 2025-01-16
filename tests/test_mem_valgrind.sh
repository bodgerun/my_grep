#!/bin/bash

if [ $# -lt 1 ]; then
  echo "Usage: ./test_mem_valgrind.sh INPUT ..."
  exit -1
fi

source ../tests/utils.sh

valgrind="valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes"

__header__ "my_grep - valgrind"

for input in $@; do
  while IFS= read line; do
    echo
    $valgrind ./my_grep $line > /dev/null
    echo 
    __border__
  done < $input
done

exit 0
