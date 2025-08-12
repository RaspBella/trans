from crs import crs

data_filename = "../docs/data.json"
template_filename = "template.html"
outdir = "../docs/"

def date_page(date, datum):
  html = f"""    <div>
      <h1>{date}: {crs(datum["from"])}->{crs(datum["to"])}
      <table>
        <tr>
          <th>From</th>
          <th>To</th>
          <th>Sub</th>
          <th>Info</th>
        </tr>
        <tr>
          <td>{crs(datum["from"])}</td>
          <td>{crs(datum["to"])}</td>"""

def date_pages(data):
  for date in data:

def root_page():
  html = f"""    <div>
      <table>
        <tr>
          <th>Date</th>
          <th>From</th>
          <th>To</th>
          <th>Sub</th>
          <th>Info</th>
        </tr>"""

def main():
  import json
  import os

  with open(data_filename, "r") as f:
    data = json.load(f)

  date_pages(data)

  root_page(data)

if __name__ == "__main__":
  main()
