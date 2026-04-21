  route(
    .info = "Travel to "___LDS___" for Leeds Spring 2026",
    .on = date(.year = 2026, .month = 4, .day = 10),
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
    .info = "Travel home from "___LDS___,
    .on = date(.year = 2026, .month = 4, .day = 12),
    service(
      .info = XC,
      .id = "C75313",
      .from = LDS,
      .to = EDB
    )
  ),
  route(
    .info = "Travel to "___CRE___" (Via "___YRK___" and "___MAN___")(As the WCML has engineering works) for Liverpool Spring 2026",
    .on = date(.year = 2026, .month = 4, .day = 17),
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
    ),
    service(
      .info = NT,
      .id = "L09175",
      .from = MAN,
      .to = CRE
    )
  ),
  route(
    .info = "Trains for Day 1 of Liverpool Spring 2026, <U>Direct services back were cancelled, Heavily delayed service to and from Wigan</u>",
    .on = date(.year = 2026, .month = 4, .day = 18),
    service(
      .info = LM,
      .id = "W05233",
      .from = CRE,
      .to = LIV
    ),
    service(
      .info = TP,
      .id = "C73844",
      .from = LIV,
      .to = WGN
    ),
    service(
      .info = VT,
      .id = "W02479",
      .from = WGN,
      .to = CRE
    )
  ),
  route(
    .info = "Trains for Day 2 of Liverpool Spring 2026",
    .on = date(.year = 2026, .month = 4, .day = 19),
    service(
      .info = LM,
      .id = "W05236",
      .from = CRE,
      .to = LIV
    ),
    service(
      .info = VT,
      .id = "W02768",
      .from = LIV,
      .to = CRE
    )
  ),
  route(
    .info = "Travel home from "___CRE___" Via "___GLC___,
    .on = date(.year = 2026, .month = 4, .day = 20),
    service(
      .info = VT,
      .id = "L02283",
      .from = CRE,
      .to = GLC
    ),
    service(
      .info = SR,
      .id = "Y41028",
      .from = GLQ,
      .to = BHG
    )
  ),
  route(
    .info = ___BHG___" to "___EDB___,
    .on = date(.year = 2026, .month = 4, .day = 21),
    service(
      .info = SR,
      .id = "W73121",
      .from = BHG,
      .to = EDB
    )
  ),
  route(
    .info = "Travel to "___CRE___" Via "___GLC___" for Manchester CL First 2026",
    .on = date(.year = 2026, .month = 4, .day = 24),
    service(
      .info = VT,
      .id = "W02480",
      .from = GLC,
      .to = CRE
    )
  ),
  route(
    .info = "Travel home from "___CRE___" Via "___GLC___,
    .on = date(.year = 2026, .month = 4, .day = 27),
    service(
      .info = VT,
      .id = "L02283",
      .from = CRE,
      .to = GLC
    )
  ),
  route(
    .info = "Travel to "___CRE___" Via "___GLC___" for Manchester Megaminx Day 2026",
    .on = date(.year = 2026, .month = 5, .day = 8),
    service(
      .info = VT,
      .id = "W02480",
      .from = GLC,
      .to = CRE
    )
  ),
  route(
    .info = "Travel home from "___CRE___" Via "___GLC___,
    .on = date(.year = 2026, .month = 5, .day = 11),
    service(
      .info = VT,
      .id = "L02283",
      .from = CRE,
      .to = GLC
    )
  ),
  route(
    .info = "Travel to "___WSM___" for "___WSM___" Spring 2026",
    .on = date(.year = 2026, .month = 5, .day = 15),
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
    .info = "Travel home from "___WSM___" Via "___BRI___,
    .on = date(.year = 2026, .month = 5, .day = 18),
    service(
      .info = XC,
      .id = "G01064",
      .from = BRI,
      .to = EDB
    )
  ),
  route(
    .info = "Travel to "___CRE___" for Crewe May 2026",
    .on = date(.year = 2026, .month = 5, .day = 29),
    service(
      .info = VT,
      .id = "W34268",
      .from = EDB,
      .to = CRE
    )
  ),
  route(
    .info = "Travel from "___CRE___" to Burger Island, "___BTS___,
    .on = date(.year = 2026, .month = 6, .day = 1),
    service(
      .info = VT,
      .id = "W34206",
      .from = CRE,
      .to = GLC
    ),
    service(
      .info = SR,
      .id = "L87904",
      .from = GLQ,
      .to = HYM
    ),
    service(
      .info = SR,
      .id = "W69664",
      .from = HYM,
      .to = BTS
    )
  ),
