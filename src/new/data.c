Day(
  "2025-01-10",
  Routes(
    Route(
      TRAIN,
      Services(
        NatRail(
          AWC,
          "EDB",
          "CRE",
          .rtt = "https://www.realtimetrains.co.uk/service/gb-nr:C50078/2025-01-10/detailed"
        )
      ),
      .info = "Crewe Favourites and FMC"
    )
  )
),
Day(
  "2025-01-13",
  Routes(
    Route(
      TRAIN,
      Services(
        NatRail(
          AWC,
          "CRE",
          "EDB",
          .rtt = "https://www.realtimetrains.co.uk/service/gb-nr:C44657/2025-01-13/detailed"
        )
      ),
      .info = "Return"
    )
  )
),
Day(
  "2025-01-17",
  Routes(
    Route(
      TRAIN,
      Services(
        NatRail(
          LNER,
          "EDB",
          "KGX",
          .rtt = "https://www.realtimetrains.co.uk/service/gb-nr:C71427/2025-01-17/detailed"
        ),
        London_Tube("KGX", "VIC"),
        NatRail(
          SWR,
          "VIC",
          "CCH",
          .rtt = "https://www.realtimetrains.co.uk/service/gb-nr:W35984/2025-01-17/detailed"
        )
      ),
      .info = "Chichester January"
    )
  )
),
Day(
  "2025-01-20",
  Routes(
    Route(
      TRAIN,
      Services(
        NatRail(
          SWR,
          "CCH",
          "VIC",
          .rtt = "https://www.realtimetrains.co.uk/service/gb-nr:W35937/2025-01-20/detailed"
        ),
        London_Tube("VIC", "KGX"),
        NatRail(
          LNER,
          "KGX",
          "EDB",
          .rtt = "https://www.realtimetrains.co.uk/service/gb-nr:C71560/2025-01-20/detailed"
        )
      ),
      .info = "Return"
    )
  )
),
Day(
  "2025-01-22",
  Routes(
    Route(
      TRAIN,
      Services(
        NatRail(
          TPE,
          "EDB",
          "NCL",
          .rtt = "https://www.realtimetrains.co.uk/service/gb-nr:P13809/2025-01-22/detailed"
        )
      ),
      .info = "Cat cafe :3c!"
    ),
    Route(
      TRAIN,
      Services(
        NatRail(
          TPE,
          "NCL",
          "EDB",
          .rtt = "https://www.realtimetrains.co.uk/service/gb-nr:P13835/2025-01-22/detailed"
        )
      ),
      .info = "Return"
    )
  )
)
