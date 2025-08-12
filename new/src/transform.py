import json
from question import print_name

def fix(datum):
  if isinstance(datum["trans"], str):
    state = "http" in datum["trans"]

    datum["text"] = input("{}->{}: ".format(print_name(datum["from"]), print_name(datum["to"]))) if state else datum["trans"]
    
    datum["link"] = datum["trans"] if state else None

    datum["sub"] = None

  elif isinstance(datum["trans"], list):
    datum["text"] = input("{}->{}: ".format(print_name(datum["from"]), print_name(datum["to"])))
    datum["link"] = None

    if len(datum["change"]) == 1:
      state = ["http" in x for x in datum["trans"]]

      datum["sub"] = [
        {
          "from": datum["from"],
          "to": datum["change"][0],
          "text": input("{}->{}: ".format(print_name(datum["from"]), print_name(datum["change"][0]))) if state[0] else datum["trans"][0],
          "link": datum["trans"][0] if state[0] else None
        },
        {
          "from": datum["change"][0],
          "to": datum["to"],
          "text": input("{}->{}: ".format(print_name(datum["change"][0]), print_name(datum["to"]))) if state[1] else datum["trans"][1],
          "link": datum["trans"][1] if state[1] else None
        }
      ]

    else:
      state = "http" in datum["trans"][0]

      datum["sub"] = [
        {
          "from": datum["from"],
          "to": datum["change"][0],
          "text": input("{}->{}: ".format(print_name(datum["from"]), print_name(datum["change"][0]))) if state else datum["trans"][0],
          "link": datum["trans"][0] if state else None
        }
      ]

      for x, y, z in zip(datum["change"], datum["change"][1:], datum["trans"][1:]):
        state = "http" in z

        datum["sub"].append({
          "from": x,
          "to": y,
          "text": input("{}->{}: ".format(print_name(x), print_name(y))) if state else z,
          "link": z if state else None
        })

      state = "http" in datum["trans"][-1]

      datum["sub"].append({
        "from": datum["change"][-1],
        "to": datum["to"],
        "text": input("{}->{}: ".format(print_name(datum["change"][-1]), print_name(datum["to"]))) if state else datum["trans"][-1],
        "link": datum["trans"][-1] if state else None
      })

  del datum["change"]
  del datum["trans"]

  return datum

with open("../docs/data.json") as f:
  data = json.load(f)

for date in data:
  if isinstance(data[date], list):
    print("date: {}".format(date))
    for x in range(len(data[date])):
      data[date][x] = fix(data[date][x])

  elif isinstance(data[date], dict):
    print("date: {}".format(date))
    data[date] = fix(data[date])

print(data)

if "y" in input("Confirm: ").lower():
  with open("../docs/data.json", "w") as f:
    json.dump(data, f)
