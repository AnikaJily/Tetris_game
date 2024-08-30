

all: main


main: main.c backend.c frontend.c
	gcc -o main  main.c backend.c frontend.c -lncurses
	./main
	make clean

clean:
	rm main
