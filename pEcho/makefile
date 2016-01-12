# Project Name
TARGET = pEcho

# Compiler
CC = g++
# Linker
LINKER = $(CC) -o

# Directories
INCLUDE_DIR = include
SOURCE_DIR  = src
BINARY_DIR  = bin

SOURCES    := $(wildcard $(SOURCE_DIR)/*.cpp)
INCLUDES   := $(wildcard $(INCLUDE_DIR)/*.h)
OBJECTS    := $(SOURCES:$(SOURCE_DIR)/%.cpp=$(BINARY_DIR)/%.o)

# Libraries
LIBS  =
# Debugger
DB    = gdb
DBOPT =
# Compiler Flags
CPPFLAGS = -std=c++11 -g -Wall -I$(INCLUDE_DIR) -O3

# Link
$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(CPPFLAGS) $(OBJECTS)
	@echo "Linking Complete"

# Compile
$(OBJECTS): $(BINARY_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@$(CC) $(CPPFLAGS) -c $< -o $@
	@echo "Compiled "$<" Successfully"

.PHONEY: clean
clean:
	@rm -f $(OBJECTS)
	@echo "Cleanup Complete"
.PHONEY: remove
remove:
	@rm -f $(TARGET)
	@echo "Executable Removed"
