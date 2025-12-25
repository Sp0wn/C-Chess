include Makefile.config

# Default target
all: $(BIN)

# Build the binary
$(BIN): $(BUILD_DIR)/main.o $(OBJ_FILES)
	$(CC) $(FLAGS) -o $@ $(BUILD_DIR)/main.o $(OBJ_FILES)

# Compile main
$(BUILD_DIR)/main.o: main.c
	$(CC) -c $< -o $@

# Compile objects
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@

# Objects target
libs: $(OBJ_FILES)

# Clean objects
clean_libs: 
	rm -rf $(BUILD_DIR)/*

# Clean everything
clean: clean_libs
	rm $(BIN)

# Run the program
run: $(BIN)
	@$(BIN)

.PHONY: all clean libs clean_libs run
