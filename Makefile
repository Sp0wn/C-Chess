
CC = clang
GAME = Game/output.o Game/set.o
MENU = Menu/input.o Menu/ui.o

all: mainapp

mainapp:
	$(CC) main.o $(GAME) $(MENU) -o C-Chess

main: main.c
	$(CC) -c -w main.c

clean:
	rm main.o C-Chess
