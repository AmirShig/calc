.PHONY: validate, main_test

CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
LINUX_FLAGS=-lsubunit -lrt -lpthread -lm

CHECKS=$(wildcard ./tests/test_*.check)
TEST_SRC=$(wildcard ./tests/test_*.c)

MSG=Minor bug fixes
BRANCH=$(shell git branch --show-current)
OS := $(shell uname -s)

ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all:
	make clean
	make validate


validate:
	$(CC) $(CFLAGS) entrance.c validation.c -o $@

main_test:
	$(CC) $(CFLAGS) stack_operations.c parser.c validation.c entrance.c calculation.c -lm -o $@
	# $(CC) $(CFLAGS) test_main.c validation.c -o $@

clean:
	rm -rf *.a *.o 
	rm -rf unit_test gcov_test
	rm -rf *.gcda *.gcno *.info report/
	rm -rf *.dSYM
	rm -rf validate main_test a.out

rebuild:
	make clean
	make all

test:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) ./tests/s21_test_matrix.c s21_matrix.a -o unit_test -lcheck -lm
else
	$(CC) $(CFLAGS) ./tests/s21_test_matrix.c s21_matrix.a -o unit_test -lcheck $(LINUX_FLAGS)
endif
	./unit_test

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) ./tests/s21_test_matrix.c ./s21_functions/*.c -o gcov_test -lcheck -lm
else
	$(CC) $(CFLAGS) $(GCOV_FLAGS) ./tests/s21_test_matrix.c ./s21_functions/*.c -o gcov_test -lcheck $(LINUX_FLAGS)
endif
	./gcov_test
	lcov -t "stest" -o s21_test.info --no-external -c -d .
	genhtml -o report s21_test.info
	rm -rf *.gcda *.gcno *.info
	$(OPEN_CMD) ./report/index.html

check_style:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h

valgrind:
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./main_test

push:
	git add .
	git commit -m "$(BRANCH): $(MSG)"
	git push origin $(BRANCH)

pull:
	git pull origin $(BRANCH)

gitback:
	git stash save --keep-index
