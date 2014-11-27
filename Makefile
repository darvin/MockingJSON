# if $CC is not set, use gcc as a sensible default
CC ?= gcc


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
    -pedantic -std=c11 \
    

CFLAGS_DEBUG := -g3 \
    -O \
    -DDEBUG

CFLAGS_RELEASE := -O2 \
    -march=native \
    -mtune=native \
    -ftree-vectorize


INCLUDEDIRS := \
	./libs/jsmn

CFLAGS += $(addprefix -I, $(INCLUDEDIRS))

OUTPUT_LIBRARY = libmockingjson.a
SOURCES = $(wildcard src/*.c)
SOURCES += libs/jsmn/jsmn.c
OBJECTS = $(SOURCES:.c=.o)

# Main target
$(OUTPUT_LIBRARY): $(OBJECTS)
	ar r $(OUTPUT_LIBRARY) $(OBJECTS)


# 	$(CC) $(OBJECTS) -o $(OUTPUT_LIBRARY)


# To obtain object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(OUTPUT_LIBRARY) $(OBJECTS)


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



.PHONY: debug release