# if $CC is not set, use gcc as a sensible default
CC ?= gcc
CXX ?= g++

# if $CFLAGS is not set, be very pedantic and compile
# as C11, that should catch some common errors, also
# fortify the source, which is a must for security.
CFLAGS ?= -Wall \
    -D_FORTIFY_SOURCE=2 \
    -Wextra -Wcast-align -Wcast-qual -Wpointer-arith \
    -Waggregate-return -Wunreachable-code -Wfloat-equal \
    -Wformat=2 -Wredundant-decls -Wundef \
    -Wdisabled-optimization -Wshadow -Wmissing-braces \
    -Wstrict-aliasing=2 -Wstrict-overflow=5 -Wconversion \
    -Wno-unused-parameter \
    -pedantic -std=c99 \
    

CFLAGS_DEBUG := -g3 \
    -O \
    -DDEBUG

CFLAGS_RELEASE := -O2 \
    -march=native \
    -mtune=native \
    -ftree-vectorize





LIB_TAP = ./tests/libs/libtap
LIB_JSMN = ./libs/jsmn

.PHONY: $(LIB_JSMN) $(LIB_TAP)
$(LIB_JSMN):
	@$(MAKE) -C $@;

$(LIB_TAP):
	@$(MAKE) -C $@;


INCLUDEDIRS := \
	$(LIB_JSMN) \
	./src

LIBRARY_CFLAGS = $(addprefix -I, $(INCLUDEDIRS))

SOURCES = $(wildcard src/*.c)
SOURCES += ./libs/jsmn/jsmn.c
OBJECTS = $(SOURCES:.c=.o) 

TEST_SOURCES = tests/mocking_tests.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_EXEC = runmockingjsontests.out
TEST_INCLUDEDIRS := \
	$(LIB_TAP)
TEST_CFLAGS = $(addprefix -I, $(TEST_INCLUDEDIRS)) 
OUTPUT_LIBRARY = libmockingjson.a

# Main target
$(OUTPUT_LIBRARY): CFLAGS += $(LIBRARY_CFLAGS)
$(OUTPUT_LIBRARY): $(OBJECTS)
	ar r $(OUTPUT_LIBRARY) $(OBJECTS)

$(TEST_EXEC): CXXFLAGS += $(TEST_CFLAGS) $(LIBRARY_CFLAGS)
$(TEST_EXEC): $(OUTPUT_LIBRARY) $(TEST_OBJECTS) $(LIB_TAP)
	$(CXX) $(TEST_OBJECTS) -o $(TEST_EXEC) \
	-ltap -L$(LIB_TAP) \
	-lmockingjson -L./ \
	-lm


test: $(TEST_EXEC)
	./$(TEST_EXEC)


# To obtain object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(OUTPUT_LIBRARY) $(OBJECTS) $(TEST_OBJECTS) $(TEST_EXEC)


# the default target is debug
all: debug

# when the target is debug,
# add CFLAGS_DEBUG to CFLAGS
debug: CFLAGS += $(CFLAGS_DEBUG)
debug: $(OUTPUT_LIBRARY)

# when the target is release,
# add CFLAGS_RELEASE to CFLAGS
release: CFLAGS += $(CFLAGS_RELEASE)
release: $(OUTPUT_LIBRARY)



.PHONY: debug release test clean all
.DEFAULT_GOAL := all