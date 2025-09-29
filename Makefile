# Compiler
CC = gcc

# Paths
SDL_INCLUDE_DIR = C:/Users/Drakendgarp/Downloads/Neverland/include
SDL_LIB_DIR     = C:/Users/Drakendgarp/Downloads/Neverland/SDL3-3.2.22/x86_64-w64-mingw32/lib
LWS_INCLUDE_DIR = C:/msys64/mingw64/include
LWS_LIB_DIR     = C:/msys64/mingw64/lib

# Flags
CFLAGS   = -I$(SDL_INCLUDE_DIR) -I$(LWS_INCLUDE_DIR) -Wall -g
LDFLAGS  = -L$(SDL_LIB_DIR) -L$(LWS_LIB_DIR) -lSDL3
LDFLAGS_MAIN = $(LDFLAGS) -mwindows

# Sources / Objects
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# Target
TARGET = main.exe

# Default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJ)
	@echo Linking $(TARGET)...
	$(CC) $(OBJ) -o $@ $(LDFLAGS_MAIN)

# Compile objects
%.o: %.c
	@echo Compiling $<...
	$(CC) $(CFLAGS) -c $< -o $@

# Run
run: $(TARGET)
	@echo Running $(TARGET)...
	./$(TARGET)

# Clean
clean:
	@echo Cleaning build artifacts...
	-del $(OBJ) $(TARGET) output.txt 2>nul || true

.PHONY: all clean run
