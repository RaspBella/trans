ROUTE(
  .info = "Go to Birmingham Via Carlisle and Stafford for UKC",
  train("W83689", "BHG", "HYM"),
  train("W34265", "HYM", "CAR"),
  train("C01365", "CAR", "STA"),
  train("C16967", "STA", "BHM"),
  train("W75572", "BHM", "UNI"),
)
