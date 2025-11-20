DATA(
  DATE(
    "2025-01-10",
    ROUTES(
      ROUTE(
        PLACE(TRAIN, "EDB"),
        PLACE(TRAIN, "CRE"),
        SERVICES(
          SERVICE(
            TRAIN,
            AWC,
            PLACE(TRAIN, "EDB"),
            PLACE(TRAIN, "CRE"),
            .link = "https://www.realtimetrains.co.uk/service/gb-nr:C50078/2025-01-10/detailed"
          )
        ),
        .type = TRAIN,
        .info = "Crewe Favourites and FMC"
      )
    )
  ),
  DATE(
    "2025-01-13",
    ROUTES(
      ROUTE(
        PLACE(TRAIN, "CRE"),
        PLACE(TRAIN, "EDB"),
        SERVICES(
          SERVICE(
            TRAIN,
            AWC,
            PLACE(TRAIN, "CRE"),
            PLACE(TRAIN, "EDB"),
            .link = "https://www.realtimetrains.co.uk/service/gb-nr:C44657/2025-01-13/detailed"
          )
        ),
        .type = TRAIN
      )
    )
  ),
  DATE(
    "2025-01-17",
    ROUTES(
      ROUTE(
        PLACE(TRAIN, "EDB"),
        PLACE(TRAIN, "CCH"),
        SERVICES(
          SERVICE(
            TRAIN,
            LNER,
            PLACE(TRAIN, "EDB"),
            PLACE(TRAIN, "KGX"),
            .link = "https://www.realtimetrains.co.uk/service/gb-nr:C71427/2025-01-17/detailed"
          ),
          SERVICE(
            LONDON_TUBE,
            TFL,
            PLACE(TRAIN, "KGX"),
            PLACE(TRAIN, "VIC")
          ),
          SERVICE(
            TRAIN,
            SWR,
            PLACE(TRAIN, "VIC"),
            PLACE(TRAIN, "CCH"),
            .link = "https://www.realtimetrains.co.uk/service/gb-nr:W35984/2025-01-17/detailed"
          )
        ),
        .info = "Chichester January 2025"
      )
    )
  ),
  DATE(
    "2025-01-20",
    ROUTES(
      ROUTE(
        PLACE(TRAIN, "CCH"),
        PLACE(TRAIN, "EDB"),
        SERVICES(
          SERVICE(
            TRAIN,
            SWR,
            PLACE(TRAIN, "CCH"),
            PLACE(TRAIN, "VIC"),
            .link = "https://www.realtimetrains.co.uk/service/gb-nr:W35937/2025-01-20/detailed"
          ),
          SERVICE(
            LONDON_TUBE,
            TFL,
            PLACE(TRAIN, "VIC"),
            PLACE(TRAIN, "KGX")
          ),
          SERVICE(
            TRAIN,
            LNER,
            PLACE(TRAIN, "KGX"),
            PLACE(TRAIN, "EDB"),
            .link = "https://www.realtimetrains.co.uk/service/gb-nr:C71560/2025-01-20/detailed"
          )
        )
      )
    )
  ),
  DATE(
    "2025-01-22",
    ROUTES(
      ROUTE(
        PLACE(TRAIN, "EDB"),
        PLACE(TRAIN, "NCL"),
        SERVICES(
          SERVICE(
            TRAIN,
            TPE,
            PLACE(TRAIN, "EDB"),
            PLACE(TRAIN, "NCL"),
            .link = "https://www.realtimetrains.co.uk/service/gb-nr:P13809/2025-01-22/detailed"
          )
        ),
        .type = TRAIN,
        .info = "Cat cafe :3c!"
      ),
      ROUTE(
        PLACE(TRAIN, "NCL"),
        PLACE(TRAIN, "EDB"),
        SERVICES(
          SERVICE(
            TRAIN,
            TPE,
            PLACE(TRAIN, "NCL"),
            PLACE(TRAIN, "EDB"),
            .link = "https://www.realtimetrains.co.uk/service/gb-nr:P13835/2025-01-22/detailed"
          )
        ),
        .type = TRAIN
      )
    )
  )
);
