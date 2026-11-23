ROUTE(
  .info = "Go to Dunfermline",
  bus("Lothian Country", "X18", "Bathgate", "Old Liston Road"),
  bt(BT_JOURNEY, 945171551, "Old Liston Road", "Dunfermline"),
  bt(BT_JOURNEY, 945254738, "Dunfermline", "Ferrytoll"),
  bt(BT_JOURNEY, 945313563, "Ferrytoll", "Ratho Station"),
  bus("Lothian Country", "X18", "Ratho Station", "Bathgate"),
)
