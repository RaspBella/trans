CFLAGS=-Wall -Wextra -Werror -ggdb

c=$(wildcard *.c)
o=$(c:.c=.o)
d=$(c:.c=.d)
BIN=trans

all: ../docs/crs.mjs $(BIN) gen

$(BIN): $(o)
	cc ${CFLAGS} -o $@ $^

%.o: %.c
	cc ${CFLAGS} -MMD -c -o $@ $<

bestline.o: bestline.c
	cc -MMD -c -o $@ $<

-include $(d)

gen: crs.py libcrs.so
	python gen.py

add: question.py crs.py libcrs.so
	python add.py

../docs/crs.mjs: crs.c
	emcc $< -o $@ \
		-s WASM=1 \
		-s MODULARIZE=1 \
		-s EXPORT_ES6=1 \
		-s EXPORTED_FUNCTIONS='["_malloc", "_free", "_crs", "_src"]' \
		-s EXPORTED_RUNTIME_METHODS='["lengthBytesUTF8", "stringToUTF8", "UTF8ToString"]' \
		-O3

libcrs.so: crs.c
	cc ${CFLAGS} -shared $< -o $@

clean:
	rm -rf libcrs.so __pycache__ ../docs/crs.mjs ../docs/crs.wasm ../docs/index.html ../docs/????-??-?? $(o) $(d) $(BIN)
