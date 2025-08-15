export function countdown(s, redir) {
  let header = document.createElement("h1");

  document.body.appendChild(header);

  const interval = setInterval(() => {
    header.textContent = `redirecting to ${redir} in ${s} seconds`;

    s-- ? s > 0 : location.assign(redir);
  }, 1000);
}
