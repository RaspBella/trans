CFLAGS=-Og -ggdb3 -std=c23
CFLAGS_WARNINGS=-Werror -Wall $(CFLAGS)
LDLIBS=-leditline
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
BIN=add

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS_WARNINGS) $(LDLIBS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS_WARNINGS) -c $< -o $@

bestline.o: bestline.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(BIN) $(OBJS)
