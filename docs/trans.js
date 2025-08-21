fetch("data.json")
  .then((response) => response.json())
  .then((data) => {
    const date = new Date().toISOString().substring(0, 10);

    const today = document.getElementById("today");

    if (Object.hasOwn(data, date)) {
      document.getElementById("today-link").text = "today!";
    }

    else {
      today.remove();
    }
  })
  .catch((error) => console.log("Error loading JSON file", error));
