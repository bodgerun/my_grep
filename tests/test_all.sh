#!/bin/bash

source ../tests/utils.sh

# test scripts:
test_diff_auto=../tests/test_diff_auto.sh
test_diff_man=../tests/test_diff_man.sh
test_code_auto=../tests/test_code_auto.sh
test_code_man=../tests/test_code_man.sh
test_long=../tests/test_long.sh

# all combinations of grep flags:
flags=../tests/flags.txt 

# files with patterns:
pats_0=../tests/pats_0.txt # empty pattern
pats_1=../tests/pats_1.txt # simple patterns
pats_2=../tests/pats_2.txt # complex patterns

# files to match patterns with:
file_1=../tests/file_1.txt
file_2=../tests/file_2.txt

# input data for special cases
man_1=../tests/man_1.txt # complex cases
man_2=../tests/man_2.txt # error cases

# total number of fails:
fails=0 

__header__ "my_grep"

# test 1
echo "1. my_grep - diff - all flags - empty pattern:"
$test_diff_auto > /dev/null $flags $pats_0 $file_1 $file_2
__process_result__ $?

# test 2
echo "2. my_grep - diff - all flags - simple patterns:"
$test_diff_auto > /dev/null $flags $pats_1 $file_1 $file_2
__process_result__ $?

# test 3
echo "3. my_grep - diff - all flags - complex patterns:"
$test_diff_auto > /dev/null $flags $pats_2 $file_1 $file_2
__process_result__ $?

# test 4
echo "4. my_grep - diff - special cases:"
$test_diff_man > /dev/null $man_1
__process_result__ $?

# test 5
echo "5. my_grep - code - all flags - empty pattern:"
$test_code_auto > /dev/null $flags $pats_0 $file_1 $file_2
__process_result__ $?

# test 6
echo "6. my_grep - code - all flags - simple patterns:"
$test_code_auto > /dev/null $flags $pats_1 $file_1 $file_2
__process_result__ $?

# test 7
echo "7. my_grep - code - all flags - complex patterns:"
$test_code_auto > /dev/null $flags $pats_2 $file_1 $file_2
__process_result__ $?

# test 8
echo "8. my_grep - code - special cases (+errors):"
$test_code_man > /dev/null $man_1 $man_2
__process_result__ $?

# test 9
echo "9. my_grep - diff & code - very long strings:"
$test_long > /dev/null
__process_result__ $?

__footer__ $fails

exit $fails
