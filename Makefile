# --- Configs --- #

# Compiler
CXX = g++

# OS Detection and Setup
ifeq ($(OS),Windows_NT)
    # Windows Settings
    # /Q = Quiet, /F = Force
    RM_FILE_CMD = del /Q /F
    TARGET_EXT = .exe
    # Command to run the executable in Windows
    RUN_CMD = $(TARGET)
else
    # Linux/Mac Settings
    RM_FILE_CMD = rm -f
    TARGET_EXT = .out
    # Command to run the executable in Linux (needs ./)
    RUN_CMD = ./$(TARGET)
endif

# Default target name
TARGET = run$(TARGET_EXT)

# --- Directories --- #
INCLUDE_DIR = res/include
LIB_DIR = res/lib
LIB_SRCS_DIR = res/src
# Find all library source files
LIB_SRCS_FILES = $(wildcard $(LIB_SRCS_DIR)/*.cpp)

# --- Flags --- #
INCLUDE_FLAG = -I$(INCLUDE_DIR)
LIB_FLAG = -L$(LIB_DIR)

# --- Main Rules --- #

.PHONY: all test run clean

# 1. Help message
all:
	@echo "Usage: make run FILE=test/your_file.cpp"
	@echo "       make run (runs existing executable)"

# 2. Compilation Rule
#    Only checks for FILE if this rule is actually triggered
test:
ifndef FILE
	$(error Usage: make test FILE=test/your_file.cpp)
endif
	@echo "Compiling Test File: $(FILE)..."
	$(CXX) $(FILE) $(LIB_SRCS_FILES) $(INCLUDE_FLAG) $(LIB_FLAG) -o $(TARGET)

# 3. Run Logic
#    This logic happens inside Make, avoiding OS-specific shell "if" commands.

ifdef FILE
# CASE A: User provided a file. We MUST recompile.
# Dependency: 'test' rule
run: test
	@echo "Running new build $(TARGET)..."
	@$(RUN_CMD)
else
# CASE B: No file provided. We try to run existing.
# We use $(wildcard) to check if the file exists right now.
ifneq ($(wildcard $(TARGET)),)
# Sub-case B1: Target exists. Just run it. No dependencies.
run:
	@echo "Running existing $(TARGET)..."
	@$(RUN_CMD)
else
# Sub-case B2: Target does not exist. Error out.
run:
	$(error Binary '$(TARGET)' not found. Run 'make run FILE=...' first to compile)
endif
endif

# 4. Clean up
clean:
	@echo "Cleaning up..."
	-$(RM_FILE_CMD) $(TARGET)