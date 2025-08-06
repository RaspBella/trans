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

fetch("/trans/data.json")
  .then((response) => response.json())
  .then((data) => {
    var next = 1;
    var stack = [];

    if (location.hash != "") {
      var n = +location.hash.slice(1);
      if (n === n) {
        if (n !== 0 ) {
          next = n;
        }
      }
    }

    for (const date in data) {
      if (date >= today) {
        stack.push(date);
      }
    }

    if (stack.length >= next) {
      countdown(5, "/trans/" + stack[next - 1]);
    }

    else {
      document.body.appendChild(
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
