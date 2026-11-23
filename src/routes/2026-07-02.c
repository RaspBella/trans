ROUTE(
  .info = "Cooking, Roslin Glen, and post Vada hangout :3",
  train("W69953", "BHG", "EDB"),
  bt(BT_JOURNEY, 903662398, "Princes Street", "North Werber Park"),
  bus("Lothian City", "37", "North Werber Park", "Charles Wilson Avenue"),
  bt(BT_JOURNEY, 903857644, "Original Rosslyn Hotel", "Princes Street"),
  train("W69035", "EDB", "BHG"),
)
