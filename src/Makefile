CFLAGS=-Wall -Wextra -MMD
O_DIR=../docs

DEPS=$(wildcard *.d)

.PHONY: default clean wasm

default: gen wasm
	./gen

gen: gen.c
	cc $(CFLAGS) $< -o $@

-include $(DEPS)

clean:
	rm -rf gen $(O_DIR)/index.html $(O_DIR)/????-??-?? $(O_DIR)/[A-Z][A-Z][A-Z] $(DEPS) $(O_DIR)/data.json
