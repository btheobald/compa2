# Project Name
NAME = exo
# Compiler
CCX = g++
TARGET = $(NAME).out

# Linker
LINKER = $(CXX) -o
# Directories
INCLUDE_DIR = include
SOURCE_DIR  = src
BINARY_DIR  = bin
LIB_DIR     = lib

SOURCES    := $(wildcard $(SOURCE_DIR)/*.cpp)
INCLUDES   := $(wildcard $(INCLUDE_DIR)/*.hpp)
OBJECTS    := $(SOURCES:$(SOURCE_DIR)/%.cpp=$(BINARY_DIR)/%.o)

# Libraries
LIBS  = `pkg-config --static --libs glfw3` -lAntTweakBar -lGLU
# Debugger
DB    = gdb
DBOPT =
# Compiler Flags
CPPFLAGS = -std=c++11 -Wall -I$(INCLUDE_DIR) `pkg-config --cflags glfw3` -lGLU -g -Ofast
# Linker Flags
LFLAGS = -Wall $(LIBS)

# Link
$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking Complete"

# Compile
$(OBJECTS): $(BINARY_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@$(CXX) $(CPPFLAGS) -c $< -o $@
	@echo "Compiled "$<" Successfully"

output.txt:$(TARGET)
	./$(TARGET) > output.txt

plot:output.txt
	gnuplot plot

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
