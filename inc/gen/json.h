#ifndef GEN_JSON_H
#define GEN_JSON_H

#include <stdio.h>
#include <stddef.h>
#include <trans/trans.h>

void crs_index_json(FILE *fp);
void crs_gb_nr_index_json(FILE *fp);
void crs_iata_index_json(FILE *fp);
void routes_index_json(FILE *fp, size_t count, const struct route *routes[]);
void index_json(FILE *fp);

#endif /* GEN_JSON_H */
