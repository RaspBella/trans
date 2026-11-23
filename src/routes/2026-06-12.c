ROUTE(
  .info = "Go to Crewe Via Glasgow for Manchester CL Third 2026",
  bt(BT_JOURNEY, 894823626, "Bathgate", "Haymarket"),
  bt(BT_JOURNEY, 894861137, "Haymarket", "Princes Street"),
  bt(BT_JOURNEY, 894874619, "Princes Street", "August_21"),
  bus("Lothian Country", "37", "August_21", "Princes Street"),
  bus("Scottish City Link", "900", "Princes Street", "Glasgow"),
  train("W34195", "GLC", "CRE"),
)
