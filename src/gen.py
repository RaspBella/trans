import os
from question import print_name

data_filename = "../docs/data.json"
template_filename = "template.html"
outdir = "../docs"

def print_dom(datum):
  return "{}->{}".format(print_name(datum["from"]), print_name(datum["to"]))

def print_doms(data):
  return ", ".join([print_dom(x) for x in data])

def print_sub_row(datum, date):
  return f"""
                  <tr>
                    <td>{print_name(datum["from"])}</td>
                    <td>{print_name(datum["to"])}</td>
                    <td>{print_info(datum, date)}</td>
                  </tr>"""

def print_sub_rows(data, date):
  return "".join([print_sub_row(x, date) for x in data])

def print_sub(datum, date):
  if "sub" in datum.keys():
    return f"""
              <table>
                <thead>
                  <tr>
                    <td>From</td>
                    <td>To</td>
                    <td>Info</td>
                  </tr>
                </thead>
                <tbody>""" + print_sub_rows(datum["sub"], date) + f"""
                </tbody>
              </table>
            """

  else:
    return "N/A"

def print_info(datum, date):
  return f'<a href="/trans/{date}/{datum["from"]}->{datum["to"]}">{datum["text"]}' if "link" in datum.keys() else datum["text"]

def print_row(datum, date):
  return f"""
          <tr>
            <td>{print_name(datum["from"])}</td>
            <td>{print_name(datum["to"])}</td>
            <td>{print_sub(datum, date)}</td>
            <td>{print_info(datum, date)}</td>
          </tr>"""

def print_row_and_date(datum, date, span=0):
  return f"""
          <tr>
            <td{' rowspan="{}"'.format(span) if span != 0 else ""}><a href="{date}">{date}</a></td>
            <td>{print_name(datum["from"])}</td>
            <td>{print_name(datum["to"])}</td>
            <td>{print_sub(datum, date)}</td>
            <td>{print_info(datum, date)}</td>
          </tr>"""

def print_rows(data, date):
  return "".join([print_row(x, date) for x in data])

def print_rows_and_date(data, date):
  return print_row_and_date(data[0], date, span=len(data)) + print_rows(data[1:], date)

def print_date_page(datum, date):
  if isinstance(datum, dict):
    return f"""<div>
      <h1>{date}: {print_dom(datum)}</h1>
      <table>
        <thead>
          <tr>
            <th>From</th>
            <th>To</th>
            <th>Sub</th>
            <th>Info</th>
          </tr>
        </thead>
        <tbody>""" + print_row(datum, date) + f"""
        </tbody>
      </table>
    </div>"""

  else:
    return f"""<div>
      <h1>{date}: {print_doms(datum)}</h1>
      <table>
        <thead>
          <tr>
            <th>From</th>
            <th>To</th>
            <th>Sub</th>
            <th>Info</th>
          </tr>
        </thead>
        <tbody>""" + print_rows(datum, date) + f"""
        </tbody>
      </table>
    </div>"""

def link(filename, link):
  with open(filename, "w") as f:
    f.write('<meta http-equiv="Refresh" content="0; {}" />'.format(link))

def links(data, date):
  d = f'{outdir}/{date}'

  if isinstance(data, dict):
    if "link" in data.keys():
      os.makedirs(f'{d}/{data["from"]}->{data["to"]}', exist_ok=True)
      link(f'{d}/{data["from"]}->{data["to"]}/index.html', "link" in data.keys())

    if "sub" in data.keys():
      for x in data["sub"]:
        if "link" in x.keys():
          os.makedirs(f'{d}/{x["from"]}->{x["to"]}', exist_ok=True)
          link(f'{d}/{x["from"]}->{x["to"]}/index.html', "link" in x.keys())

  else:
    for x in data:
      if "link" in x.keys():
        os.makedirs(f'{d}/{x["from"]}->{x["to"]}', exist_ok=True)
        link(f'{d}/{x["from"]}->{x["to"]}/index.html', "link" in x.keys())

    if "sub" in x.keys():
      for y in x["sub"]:
        if "link" in y.keys():
          os.makedirs(f'{d}/{y["from"]}->{y["to"]}', exist_ok=True)
          link(f'{d}/{y["from"]}->{y["to"]}/index.html', "link" in y.keys())

def date_pages(data, template):
  for date in data:
    os.makedirs("{}/{}".format(outdir, date), exist_ok=True)

    with open("{}/{}/index.html".format(outdir, date), "w") as f:
      f.write(template.replace("<!--REPLACE-->", print_date_page(data[date], date)))

    links(data[date], date)

def print_root_page(data):
  html = f"""<div>
      <ul class="nav">
        <li id="today"><a id="today-link" href="today">today?</a></li>
        <li><a href="crs">crs</a></li>
      </ul>
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

  for date in data:
    if isinstance(data[date], dict):
      html += print_row_and_date(data[date], date)

    else:
      html += print_rows_and_date(data[date], date)

  html += f"""
        </tbody>
      </table>
    </div>
    <script src="trans.js"></script>"""

  return html

def main():
  import json

  with open(data_filename, "r") as f:
    data = json.load(f)

  with open(template_filename, "r") as f:
    template = f.read()

  date_pages(data, template)

  with open("{}/index.html".format(outdir), "w") as root:
    root.write(template.replace("<!--REPLACE-->", print_root_page(data)))

if __name__ == "__main__":
  main()
