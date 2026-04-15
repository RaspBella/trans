  route(
    .info = "Travel to "__LDS__" for Leeds Spring 2026",
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
    .info = "Travel home from "__LDS__,
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
    .info = "Travel to "__CRE__" (Via "__YRK__" and "__MAN__")(As the WCML has engineering works) for Liverpool Spring 2026",
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
    .info = "Travel home from "__CRE__" Via "__GLC__,
    .on = date(.year = 2026, .month = 4, .day = 20),
    .count = 1,
    COMMON_CRE_TO_GLC
  ),
  route(
    .info = "Travel to "__CRE__" Via "__GLC__" for Manchester CL First 2026",
    .on = date(.year = 2026, .month = 4, .day = 24),
    .count = 1,
    COMMON_GLC_TO_CRE
  ),
  route(
    .info = "Travel home from "__CRE__" Via "__GLC__,
    .on = date(.year = 2026, .month = 4, .day = 27),
    .count = 1,
    COMMON_CRE_TO_GLC
  ),
  route(
    .info = "Travel to "__CRE__" Via "__GLC__" for Manchester Megaminx__Day__2026",
    .on = date(.year = 2026, .month = 5, .day = 8),
    .count = 1,
    COMMON_GLC_TO_CRE
  ),
  route(
    .info = "Travel home from "__CRE__" Via "__GLC__,
    .on = date(.year = 2026, .month = 5, .day = 11),
    .count = 1,
    COMMON_CRE_TO_GLC
  ),
  route(
    .info = "Travel to "__WSM__" for "__WSM__" Spring 2026",
    .on = date(.year = 2026, .month = 5, .day = 15),
    .count = 2,
    service(
      .info = XC,
      .id = "C75088",
      .from = EDB,
      .to = BRI
    ),
    service(
      .info = GW,
      .id = "P22990",
      .from = BRI,
      .to = WSM
    )
  ),
  route(
    .info = "Travel home from "__WSM__" Via "__BRI__,
    .on = date(.year = 2026, .month = 5, .day = 18),
    .count = 1,
    service(
      .info = XC,
      .id = "G01064",
      .from = BRI,
      .to = EDB
    )
  ),
