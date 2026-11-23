#include <gen/json.h>
#include <trans/crs.h>

void crs_index_json(FILE *fp) {
  fprintf(fp, "{\"dbs\":[\"gb_nr\",\"iata\"]}");
}

void crs_gb_nr_index_json(FILE *fp) {
  extern const struct crs crs_gb_nr[];
  extern const size_t crs_gb_nr_count;

  fprintf(fp, "{");

  if (crs_gb_nr_count) {
    fprintf(fp, "\"%s\":\"%s\"", crs_gb_nr[0].code, crs_gb_nr[0].name);

    for (size_t i = 1; i < crs_gb_nr_count; ++i) {
      fprintf(fp, ",\"%s\":\"%s\"", crs_gb_nr[i].code, crs_gb_nr[i].name);
    }
  }

  fprintf(fp, "}");
}

void crs_iata_index_json(FILE *fp) {
  extern const struct crs crs_iata[];
  extern const size_t crs_iata_count;

  fprintf(fp, "{");

  if (crs_iata_count) {
    fprintf(fp, "\"%s\":\"%s\"", crs_iata[0].code, crs_iata[0].name);

    for (size_t i = 1; i < crs_iata_count; ++i) {
      fprintf(fp, ",\"%s\":\"%s\"", crs_iata[i].code, crs_iata[i].name);
    }
  }

  fprintf(fp, "}");
}

static void bus_json(FILE *fp, const struct trans_bus b) {
  fprintf(fp, "\"bus\":{");

  switch (b.type) {
    case TRANS_BUS_NO_BT:
      fprintf(
        fp,
        "\"op\":\"%s\","
        "\"number\":\"%s\"",
        b.as.no_bt.op,
        b.as.no_bt.number
      );

      break;

    case TRANS_BUS_BT_TRIP:
      fprintf(fp, "\"trip\":\"%u\"", b.as.bt);

      break;

    case TRANS_BUS_BT_JOURNEY:
      fprintf(fp, "\"journey\":\"%u\"", b.as.bt);

      break;
  }

  fprintf(fp, "}");
}

static void train_json(FILE *fp, const struct trans_train t) {
  fprintf(fp, "\"train\":\"%s\"", t.id);
}

static void ferry_json(FILE *fp, const struct trans_ferry f) {
  fprintf(
    fp,
    "\"ferry\":{"
    "\"op\":\"%s\","
    "\"dep\":\"%s\"}",
    f.op,
    f.dep
  );
}

static void plane_json(FILE *fp, const struct trans_plane p) {
  fprintf(fp, "\"plane\":\"%s\"", p.number);
}

static void trans_json(FILE *fp, const struct trans t) {
  fprintf(
    fp,
    "{"
    "\"from\":\"%s\","
    "\"to\":\"%s\",",
    t.from,
    t.to
  );

  switch (t.type) {
    case TRANS_BUS:
      bus_json(fp, t.as.bus);

      break;

    case TRANS_TRAIN:
      train_json(fp, t.as.train);

      break;

    case TRANS_FERRY:
      ferry_json(fp, t.as.ferry);

      break;

    case TRANS_PLANE:
      plane_json(fp, t.as.plane);

      break;
  }

  fprintf(fp, "}");
}

static void route_json(FILE *fp, const struct route *r) {
  fprintf(fp, "\"%s\":", r->iso);

  if (r->count) {
    fprintf(
      fp,
      "{\"info\":\"%s\","
      "\"items\":[",
      r->info
    );

    trans_json(fp, r->items[0]);

    for (size_t i = 1; i < r->count; ++i) {
      fprintf(fp, ",");

      trans_json(fp, r->items[i]);
    }

    fprintf(fp, "]}");
  }

  else {
    fprintf(fp, "\"%s\"", r->info);
  }
}

void routes_index_json(FILE *fp, size_t count, const struct route *routes[]) {
  fprintf(fp, "{");

  if (count) {
    route_json(fp, routes[0]);

    for (size_t i = 1; i < count; ++i) {
      fprintf(fp, ",");

      route_json(fp, routes[i]);
    }
  }

  fprintf(fp, "}");
}

void index_json(FILE *fp) {
  fprintf(fp, "{\"dbs\":[\"crs\",\"routes\"]}");
}
