const table = document.getElementsByTagName("table")[0];

const today = new Date().toISOString().substring(0, 10);

let has_past = false;
let has_present = false;
let has_future = false;

for (let i = 1; i < table.rows.length; i++) {
    const date = table.rows[i].cells[0].innerText;
    
    if (date < today) {
	if (!has_past) {
	    let row = table.insertRow(1);
	    let cell = row.insertCell(0);
	    let a = document.createElement("a");
	    let text = document.createTextNode("Past journey(s):");

	    cell.colSpan = 5;
	    cell.style.fontWeight = "bolder";
	    cell.style.backgroundColor = "#af33ff";

	    a.href = "past";
	    a.appendChild(text);

	    cell.appendChild(a);

	    has_past = true;
	}
    }

    else if (date === today) {
	if (!has_present) {
	    let row = table.insertRow(i);
	    let cell = row.insertCell(0);
	    let a = document.createElement("a");
	    let text = document.createTextNode("Todays journey(s):");

	    cell.colSpan = 5;
	    cell.style.fontWeight = "bolder";
	    cell.style.backgroundColor = "#af33ff";

	    a.href = "today";
	    a.appendChild(text);

	    cell.appendChild(a);

	    has_present = true;
	}
    }

    else if (date > today) {
	if (!has_future) {
	    let row = table.insertRow(i);
	    let cell = row.insertCell(0);
	    let a = document.createElement("a");
	    let text = document.createTextNode("Future journey(s):");

	    cell.colSpan = 5;
	    cell.style.fontWeight = "bolder";
	    cell.style.backgroundColor = "#af33ff";

	    a.href = "future";
	    a.appendChild(text);

	    cell.appendChild(a);

	    has_future = true;
	}
    }
}

// de duping dates

for (let i = 1; i < table.rows.length; i++) {
    const date = table.rows[i].cells[0];

    for (let j = i + 1; j < table.rows.length; j++) {
	const next_date = table.rows[j].cells[0];

	if (date.innerText === next_date.innerText) {
	    date.rowSpan += 1;
	    next_date.remove();
	}
    }
}
