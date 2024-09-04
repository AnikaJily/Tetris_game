CC = gcc
FLAGS =  -g -Wall -Wextra -Wall -std=c11 -fprofile-arcs -ftest-coverage --coverage

GCOV_FLAGS = 
DEBUG = 0



OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	CHECK_FLAGS = -lcheck -I tests -L tests
endif

ENTRY_POINTS := $(shell grep -r -l  "int main" --exclude Makefile)
ENTRY_POINTS_OBJ := $(ENTRY_POINTS:.c=.o)
SOURCES := $(filter-out $(ENTRY_POINTS) $(shell find ./tests -name '*.c'), $(shell find . -name '*.c' ! -path "./tests/*"))
OBJECTS := $(SOURCES:.c=.o)

TEST_SOURCES := $(shell find ./tests -name '*.c')
TEST_OBJECTS := $(TEST_SOURCES:.c=.o)
GCOV_FILES := $(shell find . -name '*.gcda' ) $(shell find . -name '*.gcno') $(shell find . -name '*.dSYM')  

all: main

test: $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) $(TEST_OBJECTS)  -o test.out $(CHECK_FLAGS) -lncurses

main: $(OBJECTS) clang
	$(CC) $(FLAGS) $(OBJECTS) main.c -o main.out -lncurses
	./main.out

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@



clean:
	rm -f $(OBJECTS) 
	rm -f $(TEST_OBJECTS)
	rm -f $(ENTRY_POINTS_OBJ)
	rm -rf $(GCOV_FILES)
	rm -rf report
	rm -f main.out test.out
	rm -rf *.dSYM
	rm main

clean-all: clean
	rm -f s21_decimal.a


gcov_report: FLAGS += $(GCOV_FLAGS)
gcov_report: clang test
	./test.out
	mkdir -p report
	gcovr --verbose --html-details -o report/report.html --exclude tests/
	open report/report.html



clang:
	clang-format -style=Google -i $(SOURCES) $(TEST_SOURCES) $(ENTRY_POINTS)
	clang-format -style=Google -i *.h



.PHONY: all clean clang test gcov_report main