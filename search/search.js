const form = document.getElementById("search");
const div = document.getElementsByTagName("div")[0];

form.addEventListener("submit", (event) => {
    event.preventDefault();

    const form_data = Object.fromEntries(new FormData(form).entries());

    fetch("../data.json")
    .then((response) => response.json())
    .then((data) => {
	console.log(form_data);
	console.log(data);

	if (form_data["date"] != "") {
	}
	
	if (form_data["from"] != "") {
	}

	if (form_data["to"] != "") {
	}
    })
    .catch((error) => console.error("Error loading JSON file", error));
});
