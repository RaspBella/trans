import("../countdown.js").then(({ countdown }) => {
  const date = new Date().toISOString().substring(0, 10);

  fetch("../data.json")
    .then((response) => response.json())
    .then((data) => {
      if (Object.hasOwn(data, date)) {
        let header = document.createElement("h1");

        header.textContext = `journey today: ${date}`;

        document.body.appendChild(header);

        countdown(5, `/trans/${date}`);
      }

      else {
        let header = document.createElement("h1");

        header.textContent = `no journey today: ${date}`;

        document.body.appendChild(header);

        countdown(5, "/trans");
      }
    })
    .catch((error) => console.log("Error loading JSON file", error));
});
