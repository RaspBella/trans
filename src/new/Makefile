.PHONY: all

all: gen
	./gen

gen: gen.c trans.c ../crs.c data.c
	cc gen.c trans.c ../crs.c -o gen
