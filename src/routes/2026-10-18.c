ROUTE(
  .info = "Falkirk Autumn 2026 Day 2",
  bt(BT_JOURNEY, 950873565, "Dunfermline", "Ferrytoll"),
  bt(BT_JOURNEY, 950875528, "Ferrytoll", "Edinburgh Airport"),
  bt(BT_TRIP, 618981591, "Edinburgh Airport", "Grangemouth"),
  bus("Midland Bluebird", "4", "Charing Cross", "Melville Street"),
  bus("Midland Bluebird", "38", "St Andrew's Church", "Larbert Forth Valley Royal Hospital"),
  bt(BT_JOURNEY, 951107647, "Larbert Forth Valley Royal Hospital", "Dunfermline"),
)
