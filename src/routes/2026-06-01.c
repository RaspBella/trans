ROUTE(
  .info = "Go to Burger Island from Crewe Via Glasgow, then Dunfermline, then Bathgate",
  train("W34206", "CRE", "GLC"),
  train("L87904", "GLQ", "HYM"),
  train("W69664", "HYM", "BTS"),
  bus("Stagecoach East Scotland", "7", "Burntisland", "Dunfermline"),
  bt(BT_JOURNEY, 890059064, "Dunfermline", "Livingston"),
  bus("Lothian Country", "73", "Livingston", "Bathgate"),
)
