#ifndef TRANS_FERRY_H
#define TRANS_FERRY_H

struct trans_ferry {
  char *op;
  char dep[6];
};

#define ferry(OP, DEP, FROM, TO) { \
  .type = TRANS_FERRY, \
  .from = FROM, \
  .to = TO, \
  .as.ferry = { \
    .op = OP, \
    .dep = DEP \
  } \
}

#endif /* TRANS_FERRY_H */
