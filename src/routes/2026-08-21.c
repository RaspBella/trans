ROUTE(
  .info = "Go to York for York Summer 2026",
  bt(BT_JOURNEY, 925463576, "Bathgate", "Haymarket"),
  bus("Lothian City", "31", "Haymarket", "Princes Street"),
  bus("Lothian City", "3", "South Bridge", "August_21"),
  bt(BT_JOURNEY, 925546006, "August_21", "South Bridge"),
  train("W85790", "EDB", "NCL"),
  train("C24969", "NCL", "YRK"),
)
