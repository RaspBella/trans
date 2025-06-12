c=parser.c lexer.c
o=$(c:.c=.o)

code=$(c) parser.h

all: $(code)

lexer.c: parser.h

parser.c parser.h: parser.y
	bison -o $@ $<

lexer.c: lexer.l
	flex -o $@ $<

clean:
	rm -f $(code) $(o)
