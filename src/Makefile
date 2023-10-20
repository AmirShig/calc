
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g
FILES=$(wildcard ./Backend/*.c)
OBJ=$(patsubst %.c,%.o, ${FILES})
GCOV_FLAGS=--coverage
UNAME := $(shell uname)

MSG=Minor bug fixes
BRANCH=$(shell git branch --show-current)

TEST= ./Unit_tests/*.c

ifeq ($(UNAME), Linux)
	LINUX_FLAGS = -lcheck -lpthread -lrt -lm -lsubunit
endif

ifeq ($(UNAME), Darwin)
	LINUX_FLAGS = -lcheck
endif

all: clean install dist test dvi run 

install: uninstall
	mkdir build
	cd Frontend/SmartCalc_front/ && qmake && make && make clean && rm Makefile && cd ../../ && mv Frontend/SmartCalc_front/SmartCalc_front.app build

uninstall:
	rm -rf build

run:
	open ./build/SmartCalc_front.app 

dvi:
	open ./SmartCalc_Guide.md
	
dist:
	mkdir Smart_Calculator/
	mkdir Smart_Calculator/src
	cp -R Backend Frontend Unit_Tests build Makefile Smart_Calculator/src
	tar cvzf Smart_Calculator.tgz Smart_Calculator/
	rm -rf Smart_Calculator

test: clean 
	$(CC) $(CFLAGS) -o test $(TEST) $(FILES) $(LINUX_FLAGS)
	./test

gcov_report: clean
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(FILES) -o test $(TEST) $(LINUX_FLAGS)
	./test
	lcov --capture --directory . --output-file=coverage.info
	genhtml coverage.info --output-directory=res
	open ./res/index.html

clean: uninstall
	-rm -rf *.dSYM test *.gcda *.gcno *.info Smart_Calculator.tgz res/
	clear

check_style:
	cp ../materials/linters/.clang-format .
	clang-format -n ./Backend/*.c ./Backend/*.h ./Frontend/SmartCalc_front/*.cpp ./Frontend/SmartCalc_front/*.h ./Unit_tests/*.c ./Unit_tests/*.h

leaks: 
	@leaks -atExit -- ./test

valgrind:
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

push:
	git add .
	git commit -m "$(BRANCH): $(MSG)"
	git push origin $(BRANCH)

pull:
	git pull origin $(BRANCH)

gitback:
	git stash save --keep-index