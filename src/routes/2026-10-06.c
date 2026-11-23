ROUTE(
  .info = "BG on trip to Duncan Place",
  bt(BT_JOURNEY, 945627925, "Bathgate", "George Street"),
  bus("Lothian City", "1", "Princes Street Scott Momument", "Academy Park"),
  bt(BT_JOURNEY, 945720746, "Duke Street", "Kirkgate Centre"),
  bt(BT_JOURNEY, 945756188, "Kirkgate Centre", "Starbank Road"),
  bus("Lothian City", "17", "Starbank Road", "Craigs Avenue"),
  bus("Lothian Country", "X18", "Craigs Avenue", "Bathgate"),
)
