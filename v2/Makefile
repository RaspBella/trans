EXTRA_CFLAGS=-Og -ggdb3
CFLAGS=$(EXTRA_CFLAGS) -std=c23 -pedantic
CFLAGS_WARNINGS=$(CFLAGS) -Wextra -Wall

SRCS=$(wildcard *.c parser/*.c parser/*/*.c)
OBJS=$(SRCS:.c=.o)

BIN=trans

.PHONY: all clean parser

all: $(BIN)

$(BIN): parser $(OBJS)
	$(CC) $(CFLAGS_WARNINGS) -o $@ $(OBJS)

parser:
	$(MAKE) -C $@ $(MAKEFLAGS)

%.o: %.c
	$(CC) $(CFLAGS_WARNINGS) -c $< -o $@

clean:
	rm -f $(BIN) $(OBJS)
	$(MAKE) -C parser clean $(MAKEFLAGS)
