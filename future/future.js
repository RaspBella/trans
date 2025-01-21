const body = document.getElementsByTagName("body")[0];

const today = new Date().toISOString().substring(0, 10);

let new_div = document.createElement("div");
let new_table = document.createElement("table");

new_div.appendChild(new_table);

let new_row = new_table.insertRow();

let new_cell_date = document.createElement("th");
let new_cell_from = document.createElement("th");
let new_cell_to = document.createElement("th");
let new_cell_change = document.createElement("th");
let new_cell_trans = document.createElement("th");

new_cell_date.appendChild(
    document.createTextNode("Date")
);
new_row.appendChild(new_cell_date);

new_cell_from.appendChild(
    document.createTextNode("From")
);
new_row.appendChild(new_cell_from);

new_cell_to.appendChild(
    document.createTextNode("To")
);
new_row.appendChild(new_cell_to);

new_cell_change.appendChild(
    document.createTextNode("Change")
);
new_row.appendChild(new_cell_change);

new_cell_trans.appendChild(
    document.createTextNode("Transportation")
);
new_row.appendChild(new_cell_trans);

body.appendChild(new_div);
