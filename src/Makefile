CFLAGS=-Wall -Wextra -MMD
O_DIR=../docs

DEPS=$(wildcard *.d)

.PHONY: default clean

default: gen
	./gen

crs_lit.h: crs
	./crs

gen: gen.c crs_lit.h
	cc $(CFLAGS) $< -o $@

-include $(DEPS)

clean:
	rm -rf crs crs_lit.h gen $(O_DIR)/index.html $(O_DIR)/????-??-?? $(O_DIR)/[A-Z][A-Z][A-Z] $(DEPS) $(O_DIR)/data.json
