ROUTE(
  .info = "Leave Dunfermline",
  bt(BT_JOURNEY, 918509353, "Dunfermline", "Ferrytoll"),
  bt(BT_JOURNEY, 918515758, "Ferrytoll", "Ratho Station"),
  bus("Lothian Country", "X18", "Ratho Station", "Bathgate"),
)
