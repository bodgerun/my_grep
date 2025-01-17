#!/bin/bash

if [ $# -lt 3 ]; then
  echo "Usage: ./test_1_diff_auto.sh FLAGS PATTERNS FILE ..."
  exit -1
fi

source ../tests/utils.sh

flags_list=$1
pats=$2
out_0=out_orig.txt
out_1=out_mine.txt
fails=0

__header__ "my_grep - diff - auto"

shift 2

while IFS= read flags; do
  grep      $flags $pats $@ > $out_0
  ./my_grep $flags $pats $@ > $out_1
  diff $out_0 $out_1
    
  if [ $? -eq 0 ]; then
    echo $green"OK:   $flags $pats $@"$reset
  else
    if [ $fails -lt 255 ]; then
      (( fails++ ))
    fi
    echo $red"FAIL: $flags $pats $@"$reset
  fi
done < $flags_list

__footer__ $fails

rm -f $out_0 $out_1

exit $fails
