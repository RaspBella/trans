import("../countdown.js").then(({ countdown }) => {
  const today = new Date().toISOString().substring(0, 10);

  fetch("../data.json")
    .then((response) => response.json())
    .then((data) => {
      if (Object.hasOwn(data, today)) {
        let header = document.createElement("h1");

        header.textContext = `journey today: ${today}`;

        document.body.appendChild(header);

        countdown(5, `/trans/${today}`);
      }

      else {
        let header = document.createElement("h1");

        header.textContent = `none today: ${today}`;

        document.body.appendChild(header);

        countdown(5, "/trans");
      }
    })
    .catch((error) => console.log("Error loading JSON file", error));
});
