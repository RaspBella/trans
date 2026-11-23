ROUTE(
  .info = "Leave Wakefield Via Leeds, York, and Newcastle",
  train("G89902", "WKF", "LDS"),
  train("G16356", "LDS", "YRK"),
  train("G80203", "YRK", "NCL"),
  train("W85816", "NCL", "EDB"),
  bus("Lohian Country", "X18", "Edinburgh", "Bathgate"),
)
