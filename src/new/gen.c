#include <stdio.h>

#include "trans.h"
#include "ops.h"

int main(void) {
  struct day dates[] = {
#include "data.c"
  };

  for (unsigned i = 0; i < ARRAY_LEN(dates); ++i) {
    print_day(dates[i]);
  }
}
