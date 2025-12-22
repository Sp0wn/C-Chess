include Makefile.config

all: mainapp

mainapp:
	$(CC) $(FILE) -o $(BIN)

clean: $(BIN)
	rm $(BIN)

run: $(BIN)
	@$(BIN)
