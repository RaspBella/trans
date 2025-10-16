fetch("data.json")
  .then((response) => response.json())
  .then((data) => {
    const date = new Date().toISOString().substring(0, 10);

    if (Object.hasOwn(data, date)) {
      today_link.text = "today!";
    }

    else {
      today.remove();
    }

    function parse_query(input, data) {
      let res = data;

      return res;
    }

    query.addEventListener("keydown", (e) => {
      if (e.code === "Enter") {
        let res = parse_query(query.value, data);

        console.log(res);
      }
    });

    submit_query.addEventListener("click", () => {
      let res = parse_query(query.value, data);

      console.log(res);
    });
  })
  .catch((error) => console.log("Error loading JSON file", error));
