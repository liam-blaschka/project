# Compiler
CC = g++

# Directories
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
BUILD_DIR = build
BIN_DIR = bin
ASSETS_DIR = assets

# SFML directories
SFML_INC_DIR = /opt/homebrew/Cellar/sfml/2.6.0/include
SFML_LIB_DIR = /opt/homebrew/Cellar/sfml/2.6.0/lib

# nlohmann/json directories
JSON_INC_DIR = /Users/liam/json-develop/include

# Compiler flags for release build
CFLAGS = -std=c++17 -I$(INCLUDE_DIR) -I$(JSON_INC_DIR) -I$(SFML_INC_DIR) -L$(SFML_LIB_DIR) -Wall

# Compiler flags for test build
TEST_CFLAGS = -std=c++17 -I$(INCLUDE_DIR) -I$(TEST_DIR) -I$(JSON_INC_DIR) -I$(SFML_INC_DIR) -L$(SFML_LIB_DIR) -g -Wall

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Test files
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

# Object files derived from source files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
OBJ_FILES_TEST = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_FILES))

# Release target
release: $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/release -lcurl -lsfml-graphics -lsfml-window -lsfml-system
	@cp -r $(ASSETS_DIR) $(BIN_DIR)

# Test target
test: $(OBJ_FILES) $(OBJ_FILES_TEST) | $(BIN_DIR)
	$(CC) $(TEST_CFLAGS) $^ -o $(BIN_DIR)/test -lcurl -lsfml-graphics -lsfml-window -lsfml-system

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile test files into object files
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(TEST_CFLAGS) -c $< -o $@

# Create the build and bin directories if they don't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

.PHONY: release test