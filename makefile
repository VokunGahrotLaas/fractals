CXX = g++
args =
break =
std = gnu++20
Werror = -Werror
Wpedantic = -Wpedantic
ADDITIONAL_FLAGS = -Wall -Wextra $(Werror) -Wconversion $(Wpedantic) -std=$(std)

mode = release
ifeq ($(mode),debug)
O = 0
MODE_FLAGS = -g -DDEBUG_FRACTALS
else
O = 2
MODE_FLAGS = -s
endif

sanitize = no
ifeq ($(sanitize),yes)
MODE_FLAGS += -fsanitize=address
endif

native = no
ifeq ($(native),yes)
MODE_FLAGS += -march=native
endif

BASE_FLAGS = $(IMPOSED_FLAGS) $(ADDITIONAL_FLAGS) $(MODE_FLAGS)

empty =
space = $(empty) $(empty)
tab = $(empty)	$(empty)
comma = ,
define newline

$(empty)
endef

RAW_LIBS = sdl2 SDL2_image
INCLUDES = $(shell pkg-config --cflags $(RAW_LIBS))
LIBS = $(shell pkg-config --libs $(RAW_LIBS))
CXXFLAGS = $(BASE_FLAGS) $(INCLUDES) $(LIBS)
SRC = $(wildcard *.cpp)
EXEC = fractals

all: $(EXEC)

$(EXEC): $(SRC)
	@$(CXX) -o $@ $^ $(CXXFLAGS)

run: $(EXEC)
	@echo "Running $<..."
	@echo "================================"
	@-./$< $(args)
	@echo "================================"
	@echo "Finished running $<"
	@echo ""

gdb: $(EXEC)
	@echo "Debugging $< with gdb..."
	@echo "================================"
ifeq ($(break),)
	@-gdb -q -ex=r --args $< $(args)
else
	@-gdb -q -ex "b $(break)" -ex=r --args $< $(args)
endif
	@echo "================================"
	@echo "Finished debugging $< with gdb"
	@echo ""

valgrind: $(EXEC)
	@echo "Debugging $< with valgrind..."
	@echo "================================"
	@-valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$< $(args)
	@echo "================================"
	@echo "Finished debugging $< with valgrind"
	@echo ""

clean:
	@$(RM) $(EXEC)

tests: $(EXEC)
	@echo "Testing $<..."
	@echo "================================"
# tests here
	@echo "================================"
	@echo "Finished testing $<"
	@echo ""

phony_explicit:

.PHONY = all run gdb valgrind clean tests phony_explicit
