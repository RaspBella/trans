EXTRA_CFLAGS=-Og -ggdb3
CFLAGS=$(EXTRA_CFLAGS) -std=c23 -pedantic
CFLAGS_WARNINGS=$(CFLAGS) -Wextra -Wall

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

CODEGEN_DIRS=$(patsubst %/,%,$(wildcard */))

.PHONY: all codegen clean $(CODEGEN_DIRS)

all: codegen $(OBJS)

codegen: $(CODEGEN_DIRS)

$(CODEGEN_DIRS):
	$(MAKE) -C $@ -f ../codegen.mk $(MAKEFLAGS)
	$(MAKE) -C $@ -f ../Makefile $(MAKEFLAGS)

%.o: %.c
	$(CC) $(CFLAGS_WARNINGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	for dir in $(CODEGEN_DIRS); do \
		$(MAKE) -C $$dir -f ../codegen.mk clean $(MAKEFLAGS); \
	done
