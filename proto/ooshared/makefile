# Project Name
NAME = ooshared
# Compiler
CCX = g++
TARGET = $(NAME).out

# Linker
LINKER = $(CXX) -o
# Directories
INCLUDE_DIR = include
SOURCE_DIR  = src
BINARY_DIR  = bin

SOURCES    := $(wildcard $(SOURCE_DIR)/*.cpp)
INCLUDES   := $(wildcard $(INCLUDE_DIR)/*.h)
OBJECTS    := $(SOURCES:$(SOURCE_DIR)/%.cpp=$(BINARY_DIR)/%.o)

# Libraries
LIBS  = -lpthread
# Debugger
DB    = gdb
DBOPT =
# Compiler Flags
CPPFLAGS = -std=c++11 -Wall -I$(INCLUDE_DIR) -g -D__NO_INLINE__
# Linker Flags
LFLAGS = -Wall $(LIBS) -Wl,--no-as-needed

# Link
$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking Complete"

# Compile
$(OBJECTS): $(BINARY_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@$(CXX) $(CPPFLAGS) -c $< -o $@
	@echo "Compiled "$<" Successfully"

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
