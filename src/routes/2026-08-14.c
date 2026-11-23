ROUTE(
  .info = "Go to Bedworth for UKC BLD 2026 Via The West Midlands",
  train("W83679", "BHG", "HYM"),
  train("W84896", "HYM", "MAN"),
  train("L89590", "MAN", "KDG"),
  train("W70551", "KDG", "STA"),
  train("C16951", "STA", "BHM"),
  train("Y80927", "BHM", "COV"),
  bus("Stagecoach Midlands", "56", "Sainsburys (TS3)", "Newcomen Road"),
)
