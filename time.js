const table = document.getElementsByTagName("table")[0];

const today = new Date().toISOString().substring(0, 10);

let has_past = false;
let has_present = false;
let has_future = false;

for (let i = 1; i < table.rows.length; i++) {
    const date = table.rows[i].cells[0].innerText;
    
    if (date < today) {
	if (!has_past) {
	    let new_row = table.insertRow(1);

	    let new_cell = new_row.insertCell(0);
	    new_cell.colSpan = "5";
	    new_cell.style.fontWeight = "bolder";

	    let new_text = document.createTextNode("Past Journeys:");

	    new_cell.appendChild(new_text);

	    has_past = true;
	}
    }
    else if (date === today) {
	if (!has_present) {
	    let new_row = table.insertRow(i);

	    let new_cell = new_row.insertCell(0);
	    new_cell.colSpan = "5";
	    new_cell.style.fontWeight = "bolder";

	    let new_text = document.createTextNode("Todays Journey:");

	    new_cell.appendChild(new_text);

	    has_present = true;
	}
    }
    else if (date > today) {
	if (!has_future) {
	    let new_row = table.insertRow(i);

	    let new_cell = new_row.insertCell(0);
	    new_cell.colSpan = "5";
	    new_cell.style.fontWeight = "bolder";

	    let new_text = document.createTextNode("Future Journeys:");

	    new_cell.appendChild(new_text);

	    has_future = true;

	    break; // now we are done labling 
	}
    }
}
