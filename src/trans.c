  route(
    .info = "Travel to Leeds for Leeds Spring 2026",
    .on = date(.year = 2026, .month = 4, .day = 10),
    .count = 2,
    service(
      .info = "TPE",
      .id = "L37277",
      .from = EDB,
      .to = NCL
    ),
    service(
      .info = "XC",
      .id = "C75098",
      .from = NCL,
      .to = LDS
    )
  ),
  route(
    .info = "Travel home from Leeds Spring 2026",
    .on = date(.year = 2026, .month = 4, .day = 12),
    .count = 1,
    service(
      .info = "XC",
      .id = "C75313",
      .from = LDS,
      .to = EDB
    )
  ),
  route(
    .info = "Travel to Crewe (Via York and Manchester)(As the WCML has engineering works) for Liverpool Spring 2026",
    .on = date(.year = 2026, .month = 4, .day = 17),
    .count = 2,
    service(
      .info = "XC",
      .id = "C75084",
      .from = EDB,
      .to = YRK
    ),
    service(
      .info = "TPE",
      .id = "L36958",
      .from = YRK,
      .to = MAN
    )
  ),
  route(
    .info = "Travel home from Crewe Via Glasgow",
    .on = date(.year = 2026, .month = 4, .day = 20),
    .count = 1,
    WEEKDAY_WYSI_FROM_CRE
  ),
