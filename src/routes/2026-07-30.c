ROUTE(
  .info = "Back from night out, then Beach trip",
  bus("FlixBus", "UK090", "Haymarket", "Livingston Deer Park"),
  bt(BT_JOURNEY, 915734758, "Knightsridge", "Bathgate"),
  train("W68989", "BHG", "EDP"),
  bus("Lothian City", "32", "Edinburgh Park", "Cramond"),
  bus("Lothian City", "32", "Cramond", "Edinburgh Park"),
  train("W69024", "EDP", "BHG"),
)
