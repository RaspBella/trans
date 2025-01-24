const table = document.getElementsByTagName("table")[0];

const today = new Date().toISOString().substring(0, 10);

fetch("../data.json")
.then((response) => response.json())
.then((data) => {
})
.catch((error) => console.error("Error loading JSON file", error));
