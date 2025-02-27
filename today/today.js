const today = new Date().toISOString().substring(0, 10);

function countdown(s, redir) {
    let header = document.createElement("h1");
    document.body.appendChild(header);

    const interval = setInterval(() => {
	header.textContent = "redirecting to " + redir + " in " + s + " seconds";

	if (s > 0) {
	    s--;
	}

	else {
	    location.assign(redir);
	}
    }, 1000);
}

fetch("../data.json")
.then((response) => response.json())
.then((data) => {
    if (Object.hasOwn(data, today)) {
	let header = document.createElement("h1");
	header.textContent = "Journey today(" + today + ")";
	
	document.body.appendChild(header);

	countdown(5, "/trans/" + today);
    }

    else {
	let header = document.createElement("h1");
	header.textContent = "No journey today";

	document.body.appendChild(header);

	countdown(5, "/trans");
    }
})
.catch((error) => console.error("Error loading JSON file", error));
