const form = document.getElementById("search");
const div = document.getElementsByTagName("div")[0];

var had_prev_search = false;

function clear_result() {
    const header = document.getElementsByTagName("h1")[0];
    const table = document.getElementsByTagName("table")[0];

    header.remove();

    if (table) {
	table.remove();
    }

    had_prev_search = false;
}

form.addEventListener("submit", (event) => {
    event.preventDefault();

    if (had_prev_search) {
	clear_result();
    }

    const form_data = Object.fromEntries(new FormData(form).entries());

    fetch("../data.json")
    .then((response) => response.json())
    .then((data) => {
	if (form_data["date"] != "") {
	    for (const date in data) {
		if (date != form_data["date"]) {
		    delete(data[date]);
		}
	    }
	}

	if (form_data["from"] != "") {
	    for (const date in data) {
		const type = Object.prototype.toString.call(data[date])

		if (type === "[object Array]") {
		    for (const journey in data[date]) {
			if (data[date][journey]["from"] != form_data["from"]) {
			    delete(data[date][journey]);
			}
		    }

		    data[date] = data[date].filter(n => n);
		    
		    if (data[date].length == 0) {
			delete(data[date]);
		    }

		    else if (data[date].length == 1) {
			data[date] = data[date][0];
		    }
		}

		else if (type === "[object Object]") {
		    if (data[date]["from"] != form_data["from"]) {
			delete(data[date]);
		    }
		}
	    }
	}

	if (form_data["to"] != "") {
	    for (const date in data) {
		const type = Object.prototype.toString.call(data[date])

		if (type === "[object Array]") {
		    for (const journey in data[date]) {
			if (data[date][journey]["to"] != form_data["to"]) {
			    delete(data[date][journey]);
			}
		    }
		    
		    data[date] = data[date].filter(n => n);

		    if (data[date].length == 1) {
			data[date] = data[date][0];
		    }
		}

		else if (type === "[object Object]") {
		    if (data[date]["to"] != form_data["to"]) {
			delete(data[date]);
		    }
		}
	    }
	}

	var date_count = 0;
	var count = 0;

	for (const date in data) {
	    const type = Object.prototype.toString.call(data[date]);
	    
	    date_count += 1;
count += 1;

	    if (type === "[object Array]") {
		count += data[date].length - 1;
	    }
	}

	const header = document.createElement("h1");
	var template;

	if (count == 0) {
	    template = "No results";
	}

	else if (count == 1) {
	    template = "1 result";
	}

	else {
	    template = count + " results";
	}

	if (date_count == 1) {
	    template += " on 1 day";
	}

	else if (date_count > 1) {
	    template += " on " + date_count + " days";
	}
	
	const text = document.createTextNode(template);

	header.appendChild(text);
	div.appendChild(header);

	if (count != 0) {
	    const table = document.createElement("table");

	    for (const date in data) {
		const type = Object.prototype.toString.call(data[date]);

		if (type === "[object Array]") {
		    let date_cell = false;

		    for (const journey in data[date]) {
			let row = table.insertRow();

			if (!date_cell) {
			    let cell = row.insertCell();

			    cell.rowSpan = data[date].length;

			    let a = document.createElement("a");
			    let text = document.createTextNode(date);

			    a.href = "/trans/" + date;
			    a.appendChild(text);

			    cell.appendChild(text);
			    
			    date_cell = true;
			}

			let from = row.insertCell();
			let to = row.insertCell();
			let change = row.insertCell();
			let trans = row.insertCell();

			from.appendChild(document.createTextNode(data[date][journey]["from"]));
			to.appendChild(document.createTextNode(data[date][journey]["to"]));

			{ // change
			    const type = Object.prototype.toString.call(data[date][journey]["change"]);

			    if (type === "[object Array]") {
				let br = document.createElement("br");

				change.appendChild(document.createTextNode(data[date][journey]["change"][0]));

				for (let i = 1; i < data[date][journey]["change"].length; i++) {
				    change.appendChild(br);
				    change.appendChild(document.createTextNode(data[date][journey]["change"][i]));
				}
			    }

			    else if (type === "[object String]") {
				change.appendChild(document.createTextNode(data[date][journey]["change"]));
			    }
			}

			{ // trans
			    const type = Object.prototype.toString.call(data[date][journey]["trans"]);

			    if (type === "[object Array]") {
				const stations = new Array(data[date][journey]["trans"].length + 1);

				stations[0] = data[date][journey]["from"];
			    
				const type = Object.prototype.toString.call(data[date][journey]["change"]);

				if (type === "[object Array]") {
				    for (let i = 1; i < stations.length - 1; i++) {
					stations[i] = data[date][journey]["change"][i - 1];
				    }
				}

				else if (data[date][journey]["change"] != "direct") {
				    stations[1] = data[date][journey]["change"];
				}

				stations[stations.length - 1] = data[date][journey]["to"];

				if (data[date][journey]["trans"][0].includes("http")) {
				    let text = document.createTextNode(stations[0] + "->" + stations[1] + ": ");
				    let a = document.createElement("a");
				    let a_text = document.createTextNode(data[date][journey]["trans"][0]);

				    a.href = data[date][journey]["trans"][0];
				    a.appendChild(a_text);

				    trans.appendChild(text);

				    trans.appendChild(a);
				}

				else {
				    trans.appendChild(document.createTextNode(stations[0] + "->" + stations[1] + ": " + data[date][journey]["trans"][0]));
				}

				for (let i = 1; i < stations.length - 1; i++) {
				    let br = document.createElement("br");

				    trans.appendChild(br);

				    if (data[date][journey]["trans"][i].includes("http")) {
					let text = document.createTextNode(stations[i] + "->" + stations[i + 1] + ": ");
					let a = document.createElement("a");
					let a_text = document.createTextNode(data[date][journey]["trans"][i]);

					a.href = data[date][journey]["trans"][i];
					a.appendChild(a_text);

					trans.appendChild(text);

					trans.appendChild(a);
				    }

				    else {
					trans.appendChild(document.createTextNode(stations[i] + "->" + stations[i + 1] + ": " + data[date][journey]["trans"][i]));
				    }
				}
			    }

			    else if (type === "[object String]") {
				if (data[date][journey]["trans"].includes("http")) {
				    let a = document.createElement("a");
				    let text = document.createTextNode(data[date][journey]["trans"]);

				    a.href = data[date][journey]["trans"];
				    a.appendChild(text);

				    trans.appendChild(a);
				}

				else {
				    let text = document.createTextNode(data[date][journey]["trans"]);

				    trans.appendChild(text);
				}
			    }
			}
		    }
		}

		else if (type === "[object Object]") {
		    let row = table.insertRow();
		    let cell = row.insertCell();
		    let a = document.createElement("a");
		    let text = document.createTextNode(date);

		    a.href = "/trans/" + date;
		    a.appendChild(text);

		    cell.appendChild(a);

		    let from = row.insertCell();
		    let to = row.insertCell();
		    let change = row.insertCell();
		    let trans = row.insertCell();

		    from.appendChild(document.createTextNode(data[date]["from"]));
		    to.appendChild(document.createTextNode(data[date]["to"]));

		    { // change
			const type = Object.prototype.toString.call(data[date]["change"]);

			if (type === "[object Array]") {
			    change.appendChild(document.createTextNode(data[date]["change"][0]));

			    for (let i = 1; i < data[date]["change"].length; i++) {
				change.appendChild(document.createElement("br"));
				change.appendChild(document.createTextNode(data[date]["change"][i]));
			    }
			}

			else if (type === "[object String]") {
			    change.appendChild(document.createTextNode(data[date]["change"]));
			}
		    }

		    { // trans
			const type = Object.prototype.toString.call(data[date]["trans"]);

			if (type === "[object Array]") {
			    const stations = new Array(data[date]["trans"].length + 1);

			    stations[0] = data[date]["from"];

			    const type = Object.prototype.toString.call(data[date]["change"]);

			    if (type === "[object Array]") {
				for (let i = 1; i < stations.length - 1; i++) {
				    stations[i] = data[date]["change"][i - 1];
				}
			    }

			    else if (data[date]["change"] != "direct") {
				stations[1] = data[date]["change"];
			    }

			    stations[stations.length - 1] = data[date]["to"];

			    if (data[date]["trans"][0].includes("http")) {
				let text = document.createTextNode(stations[0] + "->" + stations[1] + ": ");
				let a = document.createElement("a");
				let a_text = document.createTextNode(data[date]["trans"][0]);

				a.href = data[date]["trans"][0];
				a.appendChild(a_text);

				trans.appendChild(text);

				trans.appendChild(a);
			    }

			    else {
				trans.appendChild(document.createTextNode(stations[0] + "->" + stations[1] + ": " + data[date]["trans"][0]));
			    }

			    for (let i = 1; i < stations.length - 1; i++) {
				let br = document.createElement("br");

				trans.appendChild(br);

				if (data[date]["trans"][i].includes("http")) {
				    let text = document.createTextNode(stations[i] + "->" + stations[i + 1] + ": ");
				    let a = document.createElement("a");
				    let a_text = document.createTextNode(data[date]["trans"][i]);

				    a.href = data[date]["trans"][i];
				    a.appendChild(a_text);

				    trans.appendChild(text);

				    trans.appendChild(a);
				}

				else {
				    trans.appendChild(document.createTextNode(stations[i] + "->" + stations[i + 1] + ": " + data[date]["trans"][i]));
				}
			    }
			}

			else if (type === "[object String]") {
			    if (data[date]["trans"].includes("http")) {
				let a = document.createElement("a");
				let text = document.createTextNode(data[date]["trans"]);

				a.href = data[date]["trans"];
				a.appendChild(text);

				trans.appendChild(a);
			    }

			    else {
				let text = document.createTextNode(data[date]["trans"]);

				trans.appendChild(text);
			    }
			}
		    }
		}
	    }

	    div.appendChild(table);
	}

	had_prev_search = true;
    })
    .catch((error) => console.error("Error loading JSON file", error));
});
