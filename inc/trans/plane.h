#ifndef TRANS_PLANE_H
#define TRANS_PLANE_H

struct trans_plane {
  char *number;
};

#define plane(NUMBER, FROM, TO) { \
  .type = TRANS_PLANE, \
  .from = FROM, \
  .to = TO, \
  .as.plane.number = NUMBER \
}

#endif /* TRANS_PLANE_H */
