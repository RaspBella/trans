EXTRA_CFLAGS=-Og -ggdb3
CFLAGS=$(EXTRA_CFLAGS) -std=c23 -pedantic
CFLAGS_WARNINGS=$(CFLAGS) -Wextra -Wall

SRCS=$(wildcard *.c) parser/json_extra.c parser/trans_extra.c
OBJS=$(SRCS:.c=.o)

BIN=trans

all: $(BIN)

$(BIN): $(OBJS) parser/json.tab.o parser/lex.json.o parser/trans.tab.o parser/lex.trans.o
	$(CC) $(CFLAGS_WARNINGS) -o $@ $^

parser/json.tab.c parser/json.tab.h: parser/json.y
	bison -o $@ -d -p json $<

parser/lex.json.c: parser/json.l parser/json.tab.h
	flex --prefix=json -o $@ $<

parser/trans.tab.c parser/trans.tab.h: parser/trans.y
	bison -o $@ -d -p trans $<

parser/lex.trans.c: parser/trans.l parser/trans.tab.h
	flex --prefix=trans -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS_WARNINGS) -c $< -o $@

clean:
	rm -f $(BIN) $(OBJS) parser/*.o parser/json.tab.c parser/lex.json.c parser/json.tab.h parser/trans.tab.c parser/lex.trans.c parser/trans.tab.h
