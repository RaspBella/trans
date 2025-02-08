const body = document.getElementsByTagName("body")[0];

const today = new Date().toISOString().substring(0, 10);

function countdown(s, redir) {
    let header = document.createElement("h1");
    body.appendChild(header);

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
	body.appendChild(
	    document.createElement("h1").appendChild(
		document.createTextNode("Journey today(" + today + ")")
	    )
	);

	countdown(5, "/trans/" + today);
    }

    else {
	body.appendChild(
	    document.createElement("h1").appendChild(
		document.createTextNode("No journey today")
	    )
	);

	countdown(5, "/trans");
    }
})
.catch((error) => console.error("Error loading JSON file", error));
