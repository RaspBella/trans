ROUTE(
  .info = "Go to Helensburgh from Crewe",
  train("W34206", "CRE", "GLC"),
  train("W68956", "GLQ", "HLC"),
  bt(BT_JOURNEY, 905328730, "Helensburgh", "Balloch"),
  bt(BT_JOURNEY, 905197548, "Balloch", "Glasgow"),
  bus("FlixBus", "UK090", "Glasgow", "Livingston Deer Park"),
  bt(BT_JOURNEY, 905365705, "Knightsridge", "Bathgate"),
)
