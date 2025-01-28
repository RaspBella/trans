const table = document.getElementsByTagName("table")[0];

const today = new Date().toISOString().substring(0, 10);

fetch("../data.json")
.then((response) => response.json())
.then((data) => {
    for (const date in data) {
	if (date < today) {
	    const type = Object.prototype.toString.call(data[date])

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

			cell.appendChild(a);
			
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
			    change.appendChild(document.createTextNode(data[date][journey]["change"][0]));

			    for (let i = 1; i < data[date][journey]["change"].length; i++) {
				change.appendChild(document.createElement("br"));
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

			else {
			    if (data[date]["change"] != "direct") {
				stations[1] = data[date]["change"];
			    }
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

	else break;
    }
})
.catch((error) => console.error("Error loading JSON file", error));
