ROUTE(
  .info = "Leave Crewe Via Glasgow, then go to BG after trying to teach Maya how to solve a Rubik's cube",
  train("W34206", "CRE", "GLC"),
  train("W69015", "GLQ", "BHG"),
  bt(BT_JOURNEY, 888230979, "Bathgate", "Edinburgh"),
  bus("Lothian City", "14", "Leith Street", "Greendykes"),
  bus("Lothian City", "14", "Greendykes", "South Bridge"),
  bt(BT_JOURNEY, 888473724, "Edinburgh", "Bathgate"),
)
