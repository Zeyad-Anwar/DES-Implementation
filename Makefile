# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c11
DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -O2

# Directories
SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BUILD_DIR = build

# Source files
SOURCES = $(SRC_DIR)/des.c $(SRC_DIR)/des_tables.c $(SRC_DIR)/utils.c
MAIN_SRC = $(SRC_DIR)/main.c
TEST_SOURCES = $(TEST_DIR)/test_des.c $(TEST_DIR)/test_utils.c

# Object files
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
MAIN_OBJ = $(BUILD_DIR)/main.o
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%.o,$(TEST_SOURCES))

# Executables
TARGET = $(BUILD_DIR)/des
TEST_TARGET = $(BUILD_DIR)/test_des

# Default target
all: $(TARGET)

# Main executable
$(TARGET): $(OBJECTS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) $^ -o $@

# Test executable
test: CFLAGS += $(DEBUG_FLAGS)
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test files
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)

# Phony targets
.PHONY: all test clean debug
