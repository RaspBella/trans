CFLAGS=-Og -ggdb3 -std=c23
CFLAGS_WARNINGS=-Werror -Wall $(CFLAGS)
LDLIBS=-leditline
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

clean:
	$(RM) $(BIN) $(OBJS)
