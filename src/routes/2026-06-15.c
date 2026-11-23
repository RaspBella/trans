ROUTE(
  .info = "Go to Ayr from Crewe",
  train("W34206", "CRE", "GLC"),
  train("L87376", "GLC", "AYR"),
  bt(BT_JOURNEY, 896093027, "Wellington Square", "Greenan Way"),
  bt(BT_JOURNEY, 896123826, "Alisa View", "Ayr Bus Station"),
  bt(BT_JOURNEY, 896149896, "Ayr", "Glasgow"),
  train("W68957", "GLQ", "BHG"),
)
