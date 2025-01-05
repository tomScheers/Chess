CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -I/lib/curl-install/include
LDFLAGS = -Llib/curl-install/lib -lcurl
SRC_DIR = src
BIN_DIR = bin
TARGET = $(BIN_DIR)/chess

# Find all .c files in src and its subdirectories
SRC_FILES := $(shell find $(SRC_DIR) -type f -name '*.c')

# Object files will be stored in the same directory structure under obj/
OBJ_DIR = obj
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Create the object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the binary, with the correct LDFLAGS
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_FILES) -o $(TARGET) $(LDFLAGS)

# Clean up object files and binary
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: clean
