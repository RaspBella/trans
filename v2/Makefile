EXTRA_CFLAGS=-Og -ggdb3
CFLAGS=$(EXTRA_CFLAGS) -std=c23
CFLAGS_WARNINGS=$(CFLAGS) -Werror -Wall
SRCS=$(wildcard *.c parser/*.c)
OBJS=$(SRCS:.c=.o) parser/alexer.o
BIN=add

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS_WARNINGS) $(LDLIBS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS_WARNINGS) -c $< -o $@

bestline.o: bestline.c
	$(CC) $(CFLAGS) -c $< -o $@

parser/alexer.o: parser/alexer.h
	$(CC) -x c -DALEXER_IMPLEMENTATION $(CFLAGS_WARNINGS) -c $< -o $@

release:
	make EXTRA_CFLAGS=-O3

clean:
	$(RM) $(BIN) $(OBJS)
