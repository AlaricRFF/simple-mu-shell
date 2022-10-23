CC = gcc
CFLAGS = -std=c99 -g -D_POSIX_C_SOURCE
BIN = mush

SRCS = $(shell find . -name "*.c")

all: $(BIN)

clean:
	rm -f $(BIN)

$(BIN): $(SRCS)
	$(CC) -o $@ $(CFLAGS) $^
