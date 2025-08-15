from question import print_name

data_filename = "../docs/data.json"
template_filename = "template.html"
outdir = "../docs/"

def print_dom(datum):
  return "{}->{}".format(print_name(datum["from"]), print_name(datum["to"]))

def print_doms(data):
  return ", ".join([print_dom(x) for x in data])

def print_sub_row(datum):
  return f"""
                  <tr>
                    <td>{print_name(datum["from"])}</td>
                    <td>{print_name(datum["to"])}</td>
                    <td>{print_info(datum)}</td>
                  </tr>"""

def print_sub_rows(data):
  return "".join([print_sub_row(x) for x in data])

def print_sub(datum):
  if datum["sub"]:
    return f"""
              <table>
                <thead>
                  <tr>
                    <td>From</td>
                    <td>To</td>
                    <td>Info</td>
                  </tr>
                </thead>
                <tbody>""" + print_sub_rows(datum["sub"]) + f"""
                </tbody>
              </table>
"""

  else:
    return "N/A"

def print_info(datum):
  return '<a href="{}">{}</a>'.format(datum["link"], datum["text"]) if datum["link"] else datum["text"]

def print_row(datum):
  return f"""
          <tr>
            <td>{print_name(datum["from"])}</td>
            <td>{print_name(datum["to"])}</td>
            <td>{print_sub(datum)}</td>
            <td>{print_info(datum)}</td>
          </tr>"""

def print_row_and_date(datum, date, span=0):
  return f"""
          <tr>
            <td{' rowspan="{}"'.format(span) if span != 0 else ""}><a href="{date}">{date}</a></td>
            <td>{print_name(datum["from"])}</td>
            <td>{print_name(datum["to"])}</td>
            <td>{print_sub(datum)}</td>
            <td>{print_info(datum)}</td>
          </tr>"""

def print_rows(data):
  return "".join([print_row(x) for x in data])

def print_rows_and_date(data, date):
  return print_row_and_date(data[0], date, span=len(data)) + print_rows(data[1:])

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
        <tbody>""" + print_row(datum) + f"""
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
        <tbody>""" + print_rows(datum) + f"""
        </tbody>
      </table>
    </div>"""

def date_pages(data, template):
  for date in data:
    import os

    os.makedirs(outdir + date, exist_ok=True)

    with open(outdir + date + "/index.html", "w") as f:
      f.write(template.replace("<!--REPLACE-->", print_date_page(data[date], date)))

def print_root_page(data):
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

  for date in data:
    if isinstance(data[date], dict):
      html += print_row_and_date(data[date], date)

    else:
      html += print_rows_and_date(data[date], date)

  html += f"""
        </tbody>
      </table>
    </div>"""

  return html

def main():
  import json

  with open(data_filename, "r") as f:
    data = json.load(f)

  with open(template_filename, "r") as f:
    template = f.read()

  date_pages(data, template)

  with open(outdir + "index.html", "w") as root:
    root.write(template.replace("<!--REPLACE-->", print_root_page(data)))

if __name__ == "__main__":
  main()
