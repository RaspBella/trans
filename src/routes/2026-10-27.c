ROUTE(
  .info = "Leave Dunfermline, then BG",
  bt(BT_JOURNEY, 954874459, "Dunfermline", "Livingston"),
  bt(BT_JOURNEY, 954909855, "Livingston", "Bathgate"),
  bt(BT_JOURNEY, 954975321, "Bathgate", "Edinburgh"),
  bus("Lothian Country", "X18", "Edinburgh", "Bathgate"),
)
