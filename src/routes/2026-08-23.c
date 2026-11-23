ROUTE(
  .info = "York Summer 2026 Day 2, then go Dunfermline",
  train("G85401", "YRK", "POP"),
  train("C32247", "POP", "YRK"),
  train("G15914", "YRK", "NCL"),
  train("G15981", "NCL", "EDB"),
  bt(BT_JOURNEY, 926560178, "Edinburgh", "Dunfermline"),
)
