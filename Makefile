
CC = clang
BOARD = set.o
MENU = ui.o

all: mainapp

mainapp: main.o $(BOARD) $(MENU)
	$(CC) main.o $(BOARD) $(MENU) -o C-Chess

main: main.c
	$(CC) -c -w main.c

clean:
	rm main.o $(BOARD) $(MENU)
