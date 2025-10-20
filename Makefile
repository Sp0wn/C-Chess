##VAR
CC = clang
FILE = main.c
UI = src/UI/IO.c
BIN = bin/bin
FLAGS = -lncursesw

all: mainapp

mainapp:
	$(CC) $(FILE) $(UI) $(FLAGS) -o $(BIN)

clean: $(BIN)
	rm $(BIN)

run: $(BIN)
	@$(BIN)
