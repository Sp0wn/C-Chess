
##VAR
CC = clang
FLAGS = -lncursesw
UI = UI/IO.o UI/Board.o
GAME = Game/set.o Game/rules.o
AI = AI/engine.o
#ONLINE =

all: mainapp

mainapp:
	$(CC) $(FLAGS) $(UI) $(GAME) $(AI) main.o -o C-Chess

main: main.c
	$(CC) $(FLAGS) -c -w main.c

clean:
	rm main.o C-Chess
