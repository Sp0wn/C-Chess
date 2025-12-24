include Makefile.config

all: mainapp

mainapp:
	$(CC) $(FILE) $(UI_SRC) $(FLAGS) -o $(BIN)

ui:
	$(CC) -c $(UI_SRC) -o $(UI_BIN)

clean: $(BIN)
	rm $(BIN)

clean_ui: $(UI_BIN)
	rm $(UI_BIN)

run: $(BIN)
	@$(BIN)
