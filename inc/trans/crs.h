#ifndef TRANS_CRS_H
#define TRANS_CRS_H

struct crs {
  char *code;
  char *name;
};

#define crs(CODE, NAME) { .code = CODE, .name = NAME }

#endif /* TRANS_CRS_H */
