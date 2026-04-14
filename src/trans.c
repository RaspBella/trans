  route(
    .info = "Travel to Leeds for Leeds Spring 2026",
    .on = date(.year = 2026, .month = 4, .day = 10),
    .count = 2,
    service(
      .info = TP,
      .id = "L37277",
      .from = EDB,
      .to = NCL
    ),
    service(
      .info = XC,
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
      .info = XC,
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
      .info = XC,
      .id = "C75084",
      .from = EDB,
      .to = YRK
    ),
    service(
      .info = TP,
      .id = "L36958",
      .from = YRK,
      .to = MAN
    )
  ),
  route(
    .info = "Travel home from Crewe Via Glasgow",
    .on = date(.year = 2026, .month = 4, .day = 20),
    .count = 1,
    COMMON_CRE_TO_GLC
  ),
  route(
    .info = "Travel to Crewe Via Glasgow for Manchester CL First 2026",
    .on = date(.year = 2026, .month = 4, .day = 24),
    .count = 1,
    COMMON_GLC_TO_CRE
  ),
  route(
    .info = "Travel home from Crewe Via Glasgow",
    .on = date(.year = 2026, .month = 4, .day = 27),
    .count = 1,
    COMMON_CRE_TO_GLC
  ),
  route(
    .info = "Travel to Crewe Via Glasgow for Manchester Megaminx Day 2026",
    .on = date(.year = 2026, .month = 5, .day = 8),
    .count = 1,
    COMMON_GLC_TO_CRE
  ),
  route(
    .info = "Travel home from Crewe Via Glasgow",
    .on = date(.year = 2026, .month = 5, .day = 11),
    .count = 1,
    COMMON_CRE_TO_GLC
  ),
