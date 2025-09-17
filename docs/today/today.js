Promise.all([
  import("./parser.js"),
  import("../countdown.js")
]).then(([parserModule, countdownModule]) => {
  const { Parser, Lexer } = parserModule;
  const { countdown } = countdownModule;

  let date = new Date();

  try {
    date = new Parser(
      new Lexer(
        location.hash.substr(1)
      ),
      date
    ).parse();
  }

  catch(error) {
    console.log(error);
  }

  date = date.toISOString().substring(0, 10);

  fetch("../data.json")
    .then((response) => response.json())
    .then((data) => {
      if (Object.hasOwn(data, date)) {
        let header = document.createElement("h1");

        header.textContext = `journey on: ${date}`;

        document.body.appendChild(header);

        countdown(5, `/trans/${date}`);
      }

      else {
        let header = document.createElement("h1");

        header.textContent = `no journey on: ${date}`;

        document.body.appendChild(header);

        countdown(5, "/trans");
      }
    })
    .catch((error) => console.log("Error loading JSON file", error));
});
