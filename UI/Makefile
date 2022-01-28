
##VAR
CC = clang
FLAGS = -lncurses
FILES = IO.c Board.c
BINS = IO.o Board.o

all: mainapp

mainapp: $(FILES)
	$(CC) -c $(FILES)

clean:
	rm $(BINS)
