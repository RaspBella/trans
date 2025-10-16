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

    submit_query.addEventListener("click", () => {
      console.log(query.textContent);
    });
  })
  .catch((error) => console.log("Error loading JSON file", error));
