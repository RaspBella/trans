ROUTE(
  .info = "Go to BG from Fionnphort",
  bus("West Coast Motors", "96", "Fionnphort", "Craignure"),
  ferry("Caledonian MacBrayne", "11:05", "Craignure", "Oban"),
  bt(BT_JOURNEY, 933199722, "Oban", "Haymarket"),
  bt(BT_JOURNEY, 933289087, "Haymarket", "South Bridge"),
  bus("Lothian Country", "X18", "Edinburgh", "Bathgate"),
)
