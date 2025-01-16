#!/bin/bash

if [ $# -lt 3 ]; then
  echo "Usage: ./test_code_man.sh FLAGS PATTERNS FILE ..."
  exit -1
fi

source ../tests/utils.sh

flags_list=$1
pats=$2
fails=0

__header__ "my_grep - code - man"

shift 2

while IFS= read flags; do
  grep      $flags $pats $@ > /dev/null 2>&1
  code_0=$?
  ./my_grep $flags $pats $@ > /dev/null 2>&1
  code_1=$?

  if [ $code_0 -eq $code_1 ] || ([ $code_0 -gt 1 ] && [ $code_1 -gt 1 ]); then
    echo $green"OK   ($code_0 : $code_1):	$flags $pats $@"$reset
  else
    if [ $fails -lt 255 ]; then
      (( fails++ ))
    fi
    echo $red"FAIL ($code_0 : $code_1):	$flags $pats $@"$reset
  fi
done < $flags_list

__footer__ $fails

exit $fails
