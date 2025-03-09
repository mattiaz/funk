CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -I include

# Directories
SRC_DIR = source
INC_DIR = include
OBJ_DIR = build
BIN_DIR = bin
TEST_DIR = tests

# Files
SRCS := $(shell find $(SRC_DIR) -name '*.cc')
OBJS := $(SRCS:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)
TEST_SRCS := $(shell find $(TEST_DIR) -name '*.cc')
TEST_BINS := $(TEST_SRCS:$(TEST_DIR)/%.cc=$(BIN_DIR)/$(TEST_DIR)/%)

# Main targets
TARGET = $(BIN_DIR)/funk
LIB_TARGET = $(BIN_DIR)/libfunk.a

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)/$(TEST_DIR)
	@mkdir -p $(shell find $(SRC_DIR) -type d | sed 's/$(SRC_DIR)/$(OBJ_DIR)/g')

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Build the static library
$(LIB_TARGET): $(filter-out $(OBJ_DIR)/main.o, $(OBJS))
	ar rcs $@ $^

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Compile test files
$(BIN_DIR)/$(TEST_DIR)/%: $(TEST_DIR)/%.cc $(LIB_TARGET)
	$(CXX) $(CXXFLAGS) $< -L$(BIN_DIR) -lfunk -lgtest -lgtest_main -pthread -o $@

# Build just the library
lib: directories $(LIB_TARGET)

# Build tests
tests: directories lib $(TEST_BINS)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Format code using clang-format
format:
	find $(SRC_DIR) $(INC_DIR) $(TEST_DIR) -name "*.cc" -o -name "*.h" | xargs clang-format -i

.PHONY: all clean format directories lib tests
