CFLAGS=-Wall -Wextra -MMD
O_DIR=../docs

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
DEPS=$(wildcard *.d)
BINS=gen_crs_lit gen

.PHONY: default clean

default: gen
	./gen

gen: gen.o crs.o
	cc $(CFLAGS) $^ -o gen

gen.c: crs_lit.h

gen_crs_lit: gen_crs_lit.o
	cc $(CFLAGS) $< -o $@

crs_lit.h: gen_crs_lit
	./gen_crs_lit

-include $(DEPS)

clean:
	rm -f $(BINS)
	rm -f $(OBJS) $(DEPS) crs_lit.h
	rm -f $(O_DIR)/index.html $(O_DIR)/data.json
	rm -rf $(O_DIR)/????-??-?? $(O_DIR)/[A-Z][A-Z][A-Z]
