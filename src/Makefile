CFLAGS=-Wall -Wextra -ggdb

srcs=$(filter-out stations.c, $(wildcard *.c))
objs=$(srcs:.c=.o)
deps=$(srcs:.c=.d)

BIN=trans
LINKS=$(BIN)-gen $(BIN)-add

DATA_FILE=../docs/data.json
OUT_DIR=../docs

.PHONY: all clean gen add wasm

all: wasm gen

gen: $(BIN)-gen
	./$< $(DATA_FILE) $(OUT_DIR)

add: $(BIN)-add
	./$< $(DATA_FILE)

wasm: ../docs/crs.mjs

$(BIN)-%: $(BIN)
	ln -sf $< $@

$(BIN): $(objs)
	cc ${CFLAGS} -o $@ $^

%.o: %.c
	cc ${CFLAGS} -MMD -c -o $@ $<

gen.o: gen.c
	cc ${CFLAGS} -MMD -c -o $@ $< -Wno-gnu-folding-constant

-include $(deps)

../docs/crs.mjs: crs.c
	emcc $< -o $@ \
		-s WASM=1 \
		-s MODULARIZE=1 \
		-s EXPORT_ES6=1 \
		-s EXPORTED_FUNCTIONS='["_malloc", "_free", "_crs", "_src"]' \
		-s EXPORTED_RUNTIME_METHODS='["lengthBytesUTF8", "stringToUTF8", "UTF8ToString"]' \
		-O3

clean:
	rm -rf ../docs/crs.mjs ../docs/crs.wasm ../docs/index.html ../docs/????-??-?? ../docs/[A-Z][A-Z][A-Z] $(objs) $(deps) $(BIN) $(LINKS)
