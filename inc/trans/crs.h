#ifndef TRANS_CRS_H
#define TRANS_CRS_H

struct crs {
  const char *code;
  const char *name;
};

#define crs(CODE, NAME) { .code = CODE, .name = NAME }

#endif /* TRANS_CRS_H */
