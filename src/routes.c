#include <trans/trans.h>
#include <stddef.h>

extern const struct route ROUTES;

const struct route *routes[] = { ROUTE_ADDRS };
const size_t route_count = sizeof(routes)/sizeof(routes[0]);
