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

TESTS   := ../tests/
FILE_1  := $(TESTS)file_1.txt
FILE_2  := $(TESTS)file_2.txt
FLAGS   := $(TESTS)flags_grep.txt
PATS_0  := $(TESTS)grep_pats_0.txt
PATS_1  := $(TESTS)grep_pats_1.txt
PATS_2  := $(TESTS)grep_pats_2.txt
INPUT_0 := $(TESTS)input_grep_0.txt # for valgrind
INPUT_1 := $(TESTS)input_grep_1.txt # normal cases
INPUT_2 := $(TESTS)input_grep_2.txt # error cases

ifeq ($(shell uname), Darwin) # MacOS
VALGRIND := @echo "\nValgrind is not supported on MacOS\n"
LEAKS    := $(TESTS)test_input_leaks.sh $(INPUT_0) $(INPUT_2)
LINTER   := clang-format
else                          # Linux
VALGRIND := $(TESTS)test_input_valgrind.sh grep $(INPUT_0) $(INPUT_2)
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
	$(TESTS)test_grep.sh

test_diff_pats_0: my_grep
	$(TESTS)test_grep_diff.sh $(FLAGS) $(PATS_0) $(FILE_1) $(FILE_2)

test_diff_pats_1: my_grep
	$(TESTS)test_grep_diff.sh $(FLAGS) $(PATS_1) $(FILE_1) $(FILE_2)

test_diff_pats_2: my_grep
	$(TESTS)test_grep_diff.sh $(FLAGS) $(PATS_2) $(FILE_1) $(FILE_2)

test_diff_manual: my_grep
	$(TESTS)test_input_diff.sh $(INPUT_1)

test_code_pats_0: my_grep
	$(TESTS)test_grep_code.sh $(FLAGS) $(PATS_0) $(FILE_1) $(FILE_2)

test_code_pats_1: my_grep
	$(TESTS)test_grep_code.sh $(FLAGS) $(PATS_1) $(FILE_1) $(FILE_2)

test_code_pats_2: my_grep
	$(TESTS)test_grep_code.sh $(FLAGS) $(PATS_2) $(FILE_1) $(FILE_2)

test_code_manual: my_grep
	$(TESTS)test_input_code.sh $(INPUT_1) $(INPUT_2)

test_long: my_grep
	$(TESTS)test_grep_long.sh

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
        test_diff_pats_0 \
        test_diff_pats_1 \
        test_diff_pats_2 \
        test_diff_manual \
        test_code_pats_0 \
        test_code_pats_1 \
        test_code_pats_2 \
        test_code_manual \
        test_long \
        test_valgrind \
        test_leaks \
        test_style \
        test_cppcheck
