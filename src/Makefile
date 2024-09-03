

all: main


main: main.c backend.c frontend.c
	gcc -o main  main.c backend.c frontend.c -lncurses
	./main
	make clean

clean:
	rm main


clang: main.c backend.c frontend.c
	clang-format --style=google -i main.c backend.c frontend.c