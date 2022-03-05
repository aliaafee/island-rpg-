CC=g++
CFLAGS=-g -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window

SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))
DEPS=$(patsubst $(SRC)/%.cpp,$(OBJ)/%.d,$(SRCS))

BIN = bin/app

SRC_DIR = src
BUILD_DIR = build

all: $(BIN)

# Build the release
release: CFLAGS=-O2 -DNDEBUG -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window
release: clean
release: $(BIN)

# Link all object files to the final executable
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Handle changes in header files
-include $(DEPS)

# Compile all cpp with h files in src dir to object files
$(OBJ)/%.o: $(SRC)/%.cpp makefile
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $<

# Cleanup
clean:
	rm -f -r $(BIN) $(OBJ)/*.o
