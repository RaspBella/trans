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
      let tokens = input.split(/[\s]+/).filter((str) => str != "");

      if (tokens.length > 0) {
        alert(`tokens: ${JSON.stringify(tokens)}`);

        let res = data;

        return res;
      }

      return data
    }

    query.addEventListener("keydown", (e) => {
      if (e.code === "Enter") {
        let res = parse_query(query.value, data);

        alert(`res: ${JSON.stringify(res)}`);
      }
    });

    submit_query.addEventListener("click", () => {
      let res = parse_query(query.value, data);

      alert(`res: ${JSON.stringify(res)}`);
    });
  })
  .catch((error) => console.log("Error loading JSON file", error));
