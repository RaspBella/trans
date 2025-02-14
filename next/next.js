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
    next = [];

    for (const date in data) {
	if (date >= today) {
	    next.push(date);
	}
    }

    if (next.length > 0) {
        if (next[0] === today) {
	    let header = document.createElement("h1");
	    header.textContent = "Today is " + today;
	    
	    body.appendChild(header);
    
	    if (location.hash === "#today_is_ok") {
	        countdown(5, "/trans/" + today);
	    }
    
	    else if (location.hash === "#not_today") {
		if (next.length > 1) {
		    countdown(5, "/trans/" + next[1]);
		}

		else {
		    body.appendChild(
			document.createElement(
			    "h2"
			).appendChild(
			    document.createTextNode(
				"No journeys upcoming :("
			    )
			)
		    );
		    
		    countdown(5, "/trans/");
		}
	    }
    
	    else {
		if (next.length > 1) {
		    let header = document.createElement("h2");
    
		    let start = document.createTextNode("Do you want a journey after today: [");
		    let y = document.createElement("a");
		    let div = document.createTextNode("|");
		    let n = document.createElement("a");
		    let end = document.createTextNode("]");
    
		    y.appendChild(document.createTextNode("y"));
		    n.appendChild(document.createTextNode("N"));
    
		    y.href = "/trans/" + next[1];
		    n.href = "/trans/" + today;
    
		    header.appendChild(start);
		    header.appendChild(y);
		    header.appendChild(div);
		    header.appendChild(n);
		    header.appendChild(end);

		    body.appendChild(header);
		}

		countdown(5, "/trans/" + today);
	    }
	}

	else {
	    countdown(5, "/trans/" + next[0]);
	}
    }

    else {
	body.appendChild(
	    document.createElement(
		"h2"
	    ).appendChild(
		document.createTextNode(
		    "No journeys upcoming :("
		)
	    )
	);

	countdown(5, "/trans/");
    }
})
.catch((error) => console.error("Error loading JSON file", error));
