gen: crs.py libcrs.so
	python gen.py

add: question.py crs.py libcrs.so
	python add.py

libcrs.so: crs.c
	cc -shared $< -o $@

clean:
	rm -rf libcrs.so __pycache__
