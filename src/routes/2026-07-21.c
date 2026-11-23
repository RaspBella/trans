ROUTE(
  .info = "Leave London, Hangout at the Meadows, then August_21",
  bt(BT_JOURNEY, 911734904, "St Mary's Church", "Euston"),
  train("W34144", "EUS", "EDB"),
  bt(BT_JOURNEY, 911993000, "August_21", "South Bridge"),
  bus("FlixBus", "UK090", "Edinburgh", "Newbridge"),
  bus("Lothian Country", "X18", "Newbridge", "Bathgate"),
)
