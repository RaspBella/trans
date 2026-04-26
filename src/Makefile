CFLAGS=-Wall -Wextra -MMD
O_DIR=../docs

SRCS=$(wildcard *.c) $(wildcard gen/*.c) $(wildcard gen/html/*.c)
OBJS=$(SRCS:.c=.o)
DEPS=$(wildcard *.d) $(wildcard gen/*.d) $(wildcard gen/html/*.d)
GENC=crs.c crs.h
BINS=gen/html/pages gen/crs

.PHONY: default clean

default: gen/html/pages
	./gen/html/pages

gen/html/pages: crs.o gen/html/root.o gen/html/yyyy_mm_dd.o

crs.c: gen/crs
	./gen/crs

-include $(DEPS)

clean:
	rm -f $(BINS)
	rm -f $(OBJS) $(DEPS)
	rm -f $(GENC)
	rm -f $(O_DIR)/index.html $(O_DIR)/data.json
	rm -rf $(O_DIR)/????-??-?? $(O_DIR)/[A-Z][A-Z][A-Z]/index.html
