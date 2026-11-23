ROUTE(
  .info = "Falkirk Autumn 2026 Day 1",
  bt(BT_JOURNEY, 950448233, "Dunfermline", "Larbert Forth Valley Royal Hospital"),
  bt(BT_TRIP, 654461857, "Larbert Forth Valley Royal Hospital", "Falkirk Asda"),
  bt(BT_TRIP, 654461075, "Melville Street", "Charing Cross"),
  bus("Midland Bluebird", "3", "Charing Cross", "Melville Street"),
  bus("Midland Bluebird", "38", "St Andrew's Church", "Larbert Forth Valley Royal Hospital"),
  bt(BT_JOURNEY, 950790273, "Larbert Forth Valley Royal Hospital", "Dunfermline"),
)
