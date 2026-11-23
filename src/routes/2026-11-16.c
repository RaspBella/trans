ROUTE(
  .info = "Go to Stirling from London, then Dunfermline, then Bathgate",
  train("Y14756", "EUS", "STG"),
  bt(BT_JOURNEY, 963957727, "Stirling", "Dunfermline"),
  bt(BT_JOURNEY, 964079359, "Dunfermline", "Ferrytoll"),
  bt(BT_JOURNEY, 964085333, "Ferrytoll", "Ratho Station"),
  bus("Lothian Country", "X18", "Ratho Station", "Bathgate"),
)
