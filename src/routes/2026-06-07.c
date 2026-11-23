ROUTE(
  .info = "Edinburgh Zoo trip :3",
  bus("Lothian Country", "X18", "Bathgate", "Edinburgh Zoo"),
  bus("Scottish City Link", "900", "Edinburgh Zoo", "Edinburgh Bus Station"),
  bt(BT_JOURNEY, 892627849, "Edinburgh", "Dunfermline"),
  bt(BT_JOURNEY, 892712419, "Dunfermline", "Ferrytoll"),
  bt(BT_JOURNEY, 892716198, "Ferrytoll", "Ratho Station"),
  bus("Lothian Country", "X18", "Ratho Station", "Bathgate"),
)
