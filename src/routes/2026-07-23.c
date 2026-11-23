ROUTE(
  .info = "Lunch and Whitburn Party :3",
  train("W68988", "BHG", "EDB"),
  bt(BT_JOURNEY, 912882203, "South Bridge", "Cameratiks"),
  bus("Lothian City", "11", "Cameratiks", "Usherhall"),
  train("W83208", "HYM", "EDP"),
  train("C15056", "EDP", "ARM"),
  bus("Lothian Country", "X18", "Armadale Asda", "Whitburn"),
  bt(BT_JOURNEY, 913125609, "Whitburn", "Bathgate"),
)
