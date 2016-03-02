# Project Name
NAME = pEcho
# Compiler
CC = clang
TARGET = $(NAME).out

# Linker
LINKER = $(CC) -o
# Directories
INCLUDE_DIR = include
SOURCE_DIR  = src
BINARY_DIR  = bin
LIB_DIR     = lib

SOURCES    := $(wildcard $(SOURCE_DIR)/*.c)
INCLUDES   := $(wildcard $(INCLUDE_DIR)/*.h)
OBJECTS    := $(SOURCES:$(SOURCE_DIR)/%.c=$(BINARY_DIR)/%.o)

# Libraries
LIBS  =
# Debugger
DB    = gdb
DBOPT =
# Compiler Flags
CFLAGS = -Wall -Werror -I$(INCLUDE_DIR) -g -Ofast
# Linker Flags
LFLAGS = -Wall $(LIBS)

# Link
$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking Complete"

# Compile
$(OBJECTS): $(BINARY_DIR)/%.o: $(SOURCE_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" Successfully"

output.txt:$(TARGET)
	./$(TARGET) > stdout.txt

.PHONEY: setup
setup:
	@mkdir bin -p
	@mkdir src -p
	@mkdir include -p

.PHONEY: clean
clean:
	@rm -f $(BINARY_DIR)/*.o
	@rm -f *.out
	@echo "Cleanup Complete"
