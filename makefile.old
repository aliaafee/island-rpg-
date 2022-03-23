CC=g++
CFLAGS=-std=c++17 -Iinclude -g -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window

SRC=src
OBJ=obj
BINDIR=bin
TEST=tests
SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))
DEPS=$(patsubst $(SRC)/%.cpp,$(OBJ)/%.d,$(SRCS))
TESTS=$(wildcard $(TEST)/*.cpp)
TESTBINS=$(patsubst $(TEST)/%.cpp,$(TEST)/bin/%,$(TESTS))

BIN = $(BINDIR)/island-rpg

SRC_DIR = src
BUILD_DIR = build

all: $(BIN)

# Build the release
release: CFLAGS=-Iinclude -O2 -DNDEBUG -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window
release: clean
release: $(BIN)
release: clean_objs

# Link all object files to the final executable
$(BIN): $(BINDIR) $(OBJ) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) 

# Handle changes in header files
-include $(DEPS)

# Compile all cpp with h files in src dir to object files
$(OBJ)/%.o: $(SRC)/%.cpp makefile
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $<

# Execute all tests
test: $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test || echo -e "\033[0;31m# Failed Test\033[0m" ; done

# Compile all tests
$(TEST)/bin/%: $(TEST)/%.cpp $(OBJ) $(filter-out $(OBJ)/main.o,$(OBJS))
	$(CC) $(CFLAGS) -o $@ $< $(filter-out $(OBJ)/main.o,$(OBJS))

$(OBJ):
	mkdir obj

$(BINDIR):
	mkdir bin

$(TEST)/bin:
	mkdir $(TEST)/bin

# Cleanup
clean:
	rm -f -r $(BINDIR) $(OBJ)
	rm -f -r $(TEST)/bin/

clean_objs:
	rm -f -r $(OBJ)
