
CC = clang
BOARD = Board/set.o

all: mainapp

mainapp: main.o $(BOARD)
	$(CC) main.o $(BOARD)

main: main.c
	$(CC) -c main.c

clean:
	rm main.o $(BOARD)
