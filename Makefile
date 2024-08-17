##VAR
CC = clang
FILES = src/main.c
BIN = bin/bin

all: mainapp

mainapp:
	$(CC) $(FILES) -o $(BIN)

clean: $(BIN)
	rm $(BIN)

run: $(BIN)
	@$(BIN)
