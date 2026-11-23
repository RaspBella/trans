ROUTE(
  .info = "Manchester September 2026, then go to Carlisle",
  train("W83681", "BHG", "HYM"),
  train("W84897", "HYM", "MAN"),
  bt(BT_JOURNEY, 938066429, "Piccadilly", "Plymouth Grove"),
  bt(BT_JOURNEY, 938263074, "Plymouth Grove", "Piccadilly"),
  train("G89069", "MAN", "PRE"),
  train("W33543", "PRE", "CAR"),
)
