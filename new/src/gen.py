from question import print_name

data_filename = "../docs/data.json"
template_filename = "template.html"
outdir = "../docs/"

def print_sub(datum):
  return datum["sub"] if datum["sub"] else ""

def print_info(datum):
  return '<a href="{}">{}</a>'.format(datum["link"], datum["text"]) if datum["link"] else datum["text"]

def date_page(date, datum):
  if isinstance(datum, dict):
    html = f"""<div>
      <h1>{date}: {print_name(datum["from"])}->{print_name(datum["to"])}</h1>
      <table>
        <thead>
          <tr>
            <th>From</th>
            <th>To</th>
            <th>Sub</th>
            <th>Info</th>
          </tr>
        </thead>
        <tbody>
          <tr>
            <td>{print_name(datum["from"])}</td>
            <td>{print_name(datum["to"])}</td>
            <td>{print_sub(datum)}</td>
            <td>{print_info(datum)}</td>
          </tr>
        </tbody>
      </table>
    </div>"""

    return html

  return "test"

def date_pages(data, template):
  for date in data:
    import os

    os.makedirs(outdir + date, exist_ok=True)

    with open(outdir + date + "/index.html", "w") as f:
      f.write(template.replace("<!--REPLACE-->", date_page(date, data[date])))

def root_page(data):
  html = f"""<div>
      <table>
        <thead>
          <tr>
            <th>Date</th>
            <th>From</th>
            <th>To</th>
            <th>Sub</th>
            <th>Info</th>
          </tr>
        </thead>
        <tbody>"""

  return html

def main():
  import json

  with open(data_filename, "r") as f:
    data = json.load(f)

  with open(template_filename, "r") as f:
    template = f.read()

  date_pages(data, template)

  with open(outdir + "index.html", "w") as root:
    root.write(template.replace("<!--REPLACE-->", root_page(data)))

if __name__ == "__main__":
  main()
