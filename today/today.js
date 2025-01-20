const head = document.getElementsByTagName("head")[0];
const body = document.getElementsByTagName("body")[0];

const today = new Date().toISOString().substring(0, 10);

body.appendChild(
    document.createElement("h1").appendChild(
	document.createTextNode("Today is " + today)
    )
);

let new_meta = document.createElement("meta");

new_meta.httpEquiv = "Refresh";
new_meta.content = "0; url=/trans/" + today;

head.appendChild(new_meta);
