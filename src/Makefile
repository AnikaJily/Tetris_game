CC = gcc
FLAGS =  -g -Wall -Wextra -Wall -std=c11 -fprofile-arcs -ftest-coverage --coverage

GCOV_FLAGS = 
DEBUG = 0
LIB_NAME = tetris
PROJECT_NAME = tetris
LIB_PATH = $(wildcard brick_game/tetris/*.c)

OS := $(shell uname)
UBUNTU := $(shell hostnamectl | grep -o 'Ubuntu')
MAC_X86 := $(shell uname -a | grep -o _X86_64)
MAC_M1 := $(shell uname -a | grep -o _ARM64)

ifeq ($(OS), Linux)
	TEST_LIBS = -lcheck -pthread -lrt -lm -lsubunit
	MATH = -lm
	OPEN = xdg-open
else ifeq ($(UBUNTU), Ubuntu)
	TEST_FLAGS=-lpthread -lcheck  -Wno-nonnull -Wno-memset-transposed-args -lm -lsubunit
	OPEN = open
endif

ifeq ($(MAC_M1), _ARM64)
	TEST_LIBS := -I/opt/homebrew/opt/check/include -L/opt/homebrew/opt/check/lib -lcheck
	OPEN = open
endif
ifeq ($(MAC_X86), _X86_64)
	TEST_LIBS = $(shell pkg-config --libs --cflags check) -lm
	OPEN = open
endif

ENTRY_POINTS := $(shell grep -r -l  "int main" --exclude Makefile)
ENTRY_POINTS_OBJ := $(ENTRY_POINTS:.c=.o)
SOURCES := $(filter-out $(ENTRY_POINTS) $(shell find ./tests -name '*.c'), $(shell find . -name '*.c' ! -path "./tests/*"))
OBJECTS := $(SOURCES:.c=.o)

TEST_SOURCES := $(shell find ./tests -name '*.c')
TEST_OBJECTS := $(TEST_SOURCES:.c=.o)
GCOV_FILES := $(shell find . -name '*.gcda' ) $(shell find . -name '*.gcno') $(shell find . -name '*.dSYM')  

all: run

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

run: install
	build/$(PROJECT_NAME)

install: tetris.a $(OBJECTS) main.o
	mkdir -p build/
	$(CC) $(FLAGS) $(OBJECTS) main.o -o build/$(PROJECT_NAME) -lncurses
	rm -rf *.o

test: $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) $(TEST_OBJECTS) -o test.out $(TEST_LIBS) -lncurses

main.o: main.c
	$(CC) $(FLAGS) -c main.c -o main.o

# main: $(OBJECTS) clang
# 	$(CC) $(FLAGS) $(OBJECTS) main.c -o main.out -lncurses
# 	./main.out


uninstall:
	rm -rf build/$(PROJECT_NAME)

dvi:
	doxygen Doxyfile
	open html/index.html

dist:
	mkdir dist
	cp build/tetris dist/
	tar -czf dist/tetris.tar.gz dist/

$(LIB_NAME).o: $(LIB_PATH)
	$(CC) $(FLAGS) -c $(LIB_PATH) -o $(LIB_NAME).o

# *.0?
tetris.a: $(LIB_NAME).o 
	ar rsc tetris.a $(LIB_NAME).o
	ranlib $(LIB_NAME).a


clean:
	rm -f $(OBJECTS) 
	rm -f $(TEST_OBJECTS)
	rm -f $(ENTRY_POINTS_OBJ)
	rm -rf $(GCOV_FILES)
	rm -f tetris.a
	rm -rf report
	rm -rf *.o
	rm -f main.out test.out
	rm -rf *.dSYM
	rm main




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