ARCH = $(shell uname)
# Project Name
NAME = pEcho
# Compiler (Dependant on ARCH)
ifeq ($(ARCH), Linux)
CCX = g++
endif
ifeq ($(ARCH), win32)
CXX = i686-w64-mingw32-g++
endif
ifeq ($(ARCH), win64)
CXX = x86_64-w64-mingw32-g++
endif
ifeq ($(ARCH), MINGW64_NT-10.0)
CXX = g++
endif

ifeq ($(ARCH), Linux)
TARGET = $(NAME).out
endif
ifeq ($(ARCH), $(filter $(ARCH), win32 win64 MINGW64_NT-10.0))
TARGET = $(NAME).exe
endif

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
LIBS  =
# Debugger
DB    = gdb
DBOPT =
# Compiler Flags
CPPFLAGS = -std=c++11 -Wall -I$(INCLUDE_DIR) -D__NO_INLINE__ -O3 -g
# Linker Flags
LFLAGS = -Wall
ifeq ($(ARCH), $(filter $(ARCH), win32 win64 MINGW64_NT-10.0))
LFLAGS = -Wall -static-libgcc -static-libstdc++
endif

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
	@rm -f $(TARGET)
	@echo "Cleanup Complete"
