ROUTE(
  .info = "Go to Dunfermline Via Glasgow from Crewe with Kirsty :3",
  train("W34206", "CRE", "WGN"),
  train("W34254", "WGN", "GLC"),
  train("L87962", "GLQ", "HYM"),
  train("W69678", "HYM", "DFE"),
  bt(BT_JOURNEY, 948439325, "Dunfermline", "Ferrytoll"),
  bt(BT_JOURNEY, 948443234, "Ferrytoll", "Ratho Station"),
  bt(BT_TRIP, 654421295, "Ratho Station", "Bathgate"),
)
