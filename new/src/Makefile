gen: crs.py libcrs.so
	python gen.py

add: question.py crs.py libcrs.so
	python add.py

../docs/crs.mjs: crs.c
	emcc $< -o $@ \
		-s WASM=1 \
		-s MODULARIZE=1 \
		-s EXPORT_ES6=1 \
		-s EXPORTED_FUNCTIONS='["_malloc", "_free", "_crs"]' \
		-s EXPORTED_RUNTIME_METHODS='["lengthBytesUTF8", "stringToUTF8", "UTF8ToString"]' \
		-O3

libcrs.so: crs.c
	cc -shared $< -o $@

clean:
	rm -rf libcrs.so __pycache__
