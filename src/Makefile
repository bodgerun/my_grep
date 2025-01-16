CC     := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11

SRCMOD := my_grep.c \
          my_grep_args.c \
          my_grep_free.c \
          my_grep_match.c \
          my_grep_out.c \
          my_grep_pats.c \
          my_grep_utils.c

OBJMOD := $(SRCMOD:.c=.o)

TESTS          := ../tests/
FILE_1         := $(TESTS)file_1.txt
FILE_2         := $(TESTS)file_2.txt
FLAGS          := $(TESTS)flags.txt
PATS_0         := $(TESTS)pats_0.txt
PATS_1         := $(TESTS)pats_1.txt
PATS_2         := $(TESTS)pats_2.txt
MAN_0          := $(TESTS)man_0.txt   # for valgrind
MAN_1          := $(TESTS)man_1.txt   # normal cases
MAN_2          := $(TESTS)man_2.txt   # error cases
TEST_ALL       := $(TESTS)test_all.sh
TEST_DIFF_AUTO := $(TESTS)test_diff_auto.sh
TEST_DIFF_MAN  := $(TESTS)test_diff_man.sh
TEST_CODE_AUTO := $(TESTS)test_code_auto.sh
TEST_CODE_MAN  := $(TESTS)test_code_man.sh
TEST_LONG      := $(TESTS)test_long.sh
TEST_LEAKS     := $(TESTS)test_mem_leaks.sh
TEST_VALGRIND  := $(TESTS)test_mem_valgrind.sh

ifeq ($(shell uname), Darwin) # MacOS
VALGRIND := @echo "\nValgrind is not supported on MacOS\n"
LEAKS    := $(TEST_LEAKS) $(MAN_0) $(MAN_2)
LINTER   := clang-format
else                          # Linux
VALGRIND := $(TEST_VALGRIND) $(MAN_0) $(MAN_2)
LEAKS    := @echo "\nLeaks is not supported on Linux\n"
LINTER   := clang-format-13
endif

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: clang my_grep

my_grep: $(OBJMOD)
	$(CC) $(CFLAGS) $^ -o $@ 
	$(RM) *.o

my_grep.o:       my_grep.c \
                 my_grep_args.h \
                 my_grep_free.h \
                 my_grep_match.h \
                 my_grep_out.h \
                 my_grep_pats.h \
                 my_grep_utils.h \
                 my_grep_types.h 

my_grep_args.o:  my_grep_args.c \
                 my_grep_args.h \
                 my_grep_utils.h \
                 my_grep_types.h

my_grep_free.o:  my_grep_free.c \
                 my_grep_free.h \
                 my_grep_types.h

my_grep_match.o: my_grep_match.c \
                 my_grep_match.h \
                 my_grep_args.h \
                 my_grep_free.h \
                 my_grep_out.h \
                 my_grep_utils.h \
                 my_grep_types.h

my_grep_out.o:   my_grep_out.c \
                 my_grep_out.h \
                 my_grep_types.h

my_grep_pats.o:  my_grep_pats.c \
                 my_grep_pats.h \
                 my_grep_utils.h \
                 my_grep_types.h

my_grep_utils.o: my_grep_utils.c \
                 my_grep_utils.h \
                 my_grep_types.h

clang:
	cp ../materials/linters/.clang-format .
	$(LINTER) -i *.h *.c ../tests/*.c
	$(RM) .clang-format

clean:
	$(RM) *.o my_grep

rebuild: clean clang my_grep

test: my_grep
	$(TEST_ALL)

test_diff_auto_0: my_grep
	$(TEST_DIFF_AUTO) $(FLAGS) $(PATS_0) $(FILE_1) $(FILE_2)

test_diff_auto_1: my_grep
	$(TEST_DIFF_AUTO) $(FLAGS) $(PATS_1) $(FILE_1) $(FILE_2)

test_diff_auto_2: my_grep
	$(TEST_DIFF_AUTO) $(FLAGS) $(PATS_2) $(FILE_1) $(FILE_2)

test_diff_man: my_grep
	$(TEST_DIFF_MAN) $(MAN_1)

test_code_auto_0: my_grep
	$(TEST_CODE_AUTO) $(FLAGS) $(PATS_0) $(FILE_1) $(FILE_2)

test_code_auto_1: my_grep
	$(TEST_CODE_AUTO) $(FLAGS) $(PATS_1) $(FILE_1) $(FILE_2)

test_code_auto_2: my_grep
	$(TEST_CODE_AUTO) $(FLAGS) $(PATS_2) $(FILE_1) $(FILE_2)

test_code_man: my_grep
	$(TEST_CODE_MAN) $(MAN_1) $(MAN_2)

test_long: my_grep
	$(TEST_LONG)

test_valgrind: my_grep
	$(VALGRIND)

test_leaks: my_grep
	$(LEAKS)

test_style:
	cp ../materials/linters/.clang-format .
	$(LINTER) -n *.h *.c ../tests/*.c
	$(RM) .clang-format

test_cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

.PHONY: all \
        clang \
        clean \
        rebuild \
        test \
        test_diff_auto_0 \
        test_diff_auto_1 \
        test_diff_auto_2 \
        test_diff_man \
        test_code_auto_0 \
        test_code_auto_1 \
        test_code_auto_2 \
        test_code_man \
        test_long \
        test_valgrind \
        test_leaks \
        test_style \
        test_cppcheck
