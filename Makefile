CFLAGS=-Iinc -Wall -Wextra -Werror -Og -ggdb

RSRC=$(wildcard src/routes/*.c)
ROBJ=$(notdir $(RSRC:.c=.o))

CRS_SRC=$(wildcard src/crs/*.c)
CRS_OBJ=$(notdir $(CRS_SRC:.c=.o))

SRC=$(wildcard src/*.c src/gen/*.c) $(RSRC) $(CRS_SRC)
OBJ=$(notdir $(SRC:.c=.o)) $(ROBJ) $(CRS_OBJ)

SHARED=$(CRS_OBJ:.o=.so)
BIN=gen

.PHONY: all clean

all: $(BIN) $(SHARED)
	@mkdir -p docs/db/routes
	./$<

$(BIN): $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "CC	$@"

%.o: src/gen/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC	$@"

%.o: src/routes/%.c
	@$(CC) $(CFLAGS) \
		-include inc/trans/trans.h \
		-D'ROUTE(INFO, ...)=const struct route route_$(subst -,_,$*) = {.iso = "$*", INFO, .count = sizeof((struct trans[]){__VA_ARGS__})/sizeof((const struct trans[]){__VA_ARGS__}[0]), .items = {__VA_ARGS__}};' \
		-c $< -o $@
	@mkdir -p docs/$(basename $@)
	@echo "CC	$@"

routes.o: src/routes.c $(ROBJ)
	@$(CC) $(CFLAGS) \
		-D'ROUTES=$(shell echo $(foreach r,$(subst -,_,$(basename $(ROBJ))),route_$(r)) | sed "s/ /,/g")' \
		-D'ROUTE_ADDRS=$(shell echo $(foreach r,$(subst -,_,$(basename $(ROBJ))),\&route_$(r)) | sed "s/ /,/g")' \
		-c $< -o $@
	@echo "CC	$@"

%.o: src/crs/%.c
	@printf '#include <stddef.h>\n#include <trans/crs.h>\n#define CRS(CODE, NAME) crs(#CODE, NAME),\nconst struct crs crs_$*[] = {\n#include "$<"\n};\nconst size_t crs_$*_count = sizeof(crs_$*)/sizeof(crs_$*[0]);' | $(CC) $(CFLAGS) -c -x c - -o $@
	@mkdir -p docs/db/crs/$(basename $@)
	@echo "CC	$@"

%.so: src/crs/%.c
	@printf '#define CRS(CODE, NAME) const char *crs_$*_##CODE = NAME;\n#include "$<"\n' | $(CC) $(CFLAGS) -shared -fPIC -x c - -o $@
	@echo "CC	$@"

clean:
	@rm -rf $(BIN) $(OBJ) $(SHARED) docs/index.html docs/db docs/????-??-??
	@echo clean
