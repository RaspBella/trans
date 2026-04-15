  route(
    .info = "Travel to " LDS " for Leeds Spring 2026",
    .on = date(.year = 2026, .month = 4, .day = 10),
    .count = 2,
    service(
      .info = TP,
      .id = "L37277",
      .from = E_EDB,
      .to = E_NCL
    ),
    service(
      .info = XC,
      .id = "C75098",
      .from = E_NCL,
      .to = E_LDS
    )
  ),
  route(
    .info = "Travel home from " LDS,
    .on = date(.year = 2026, .month = 4, .day = 12),
    .count = 1,
    service(
      .info = XC,
      .id = "C75313",
      .from = E_LDS,
      .to = E_EDB
    )
  ),
  route(
    .info = "Travel to " CRE " (Via " YRK " and " MAN ")(As the WCML has engineering works) for Liverpool Spring 2026",
    .on = date(.year = 2026, .month = 4, .day = 17),
    .count = 2,
    service(
      .info = XC,
      .id = "C75084",
      .from = E_EDB,
      .to = E_YRK
    ),
    service(
      .info = TP,
      .id = "L36958",
      .from = E_YRK,
      .to = E_MAN
    )
  ),
  route(
    .info = "Travel home from " CRE " Via " GLC,
    .on = date(.year = 2026, .month = 4, .day = 20),
    .count = 1,
    COMMON_CRE_TO_GLC
  ),
  route(
    .info = "Travel to " CRE " Via "GLC " for Manchester CL First 2026",
    .on = date(.year = 2026, .month = 4, .day = 24),
    .count = 1,
    COMMON_GLC_TO_CRE
  ),
  route(
    .info = "Travel home from " CRE " Via " GLC,
    .on = date(.year = 2026, .month = 4, .day = 27),
    .count = 1,
    COMMON_CRE_TO_GLC
  ),
  route(
    .info = "Travel to " CRE " Via " GLC " for Manchester Megaminx Day 2026",
    .on = date(.year = 2026, .month = 5, .day = 8),
    .count = 1,
    COMMON_GLC_TO_CRE
  ),
  route(
    .info = "Travel home from " CRE " Via " GLC,
    .on = date(.year = 2026, .month = 5, .day = 11),
    .count = 1,
    COMMON_CRE_TO_GLC
  ),
  route(
    .info = "Travel to " WSM " for " WSM " Spring 2026",
    .on = date(.year = 2026, .month = 5, .day = 15),
    .count = 2,
    service(
      .info = XC,
      .id = "C75088",
      .from = E_EDB,
      .to = E_BRI
    ),
    service(
      .info = GW,
      .id = "P22990",
      .from = E_BRI,
      .to = E_WSM
    )
  ),
  route(
    .info = "Travel home from " WSM " Via " BRI,
    .on = date(.year = 2026, .month = 5, .day = 18),
    .count = 1,
    service(
      .info = XC,
      .id = "G01064",
      .from = E_BRI,
      .to = E_EDB
    )
  ),
