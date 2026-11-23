ROUTE(
  .info = "Southport Autumn 2026 Day 2 and then go to Dunfermline",
  train("P24125", "SOP", "WGW"),
  train("W33290", "WGN", "PNR"),
  train("W85211", "PNR", "HYM"),
  bt(BT_JOURNEY, 935559389, "Queensferry Street", "Dunfermline"),
)
