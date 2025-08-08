from crs import crs

def check(s):
  if len(s) == 3:
    if s.islower() or s.isupper():
      return True

  return False

def update(s):
  if check(s):
    return s.upper()

  return s

def print_name(s):
  if check(s):
    return "{}({})".format(crs(s), s)

  return s

def question():
  date = input("yyyy-mm-dd: ")

  data = {
    "from": update(input("from: ")),
    "to": update(input("to: "))
  }

  data["text"] = input("{}->{}: ".format(
    print_name(data["from"]),
    print_name(data["to"])
  ))

  data["link"] = input("{}->{}::link?: ".format(
    print_name(data["from"]),
    print_name(data["to"])
  ))

  raw = input("changes? (comma seperated): ")

  if raw:
    changes = raw.split(",")

    data["sub"] = []

    for x in range(len(changes)):
      changes[x] = update(changes[x])

    data["sub"].append({
      "from": data["from"],
      "to": changes[0],
      "text": input("{}->{}: ".format(
        print_name(data["from"]),
        print_name(changes[0])
      )),
      "link": input("{}->{}::link? ".format(
        print_name(data["from"]),
        print_name(changes[0])
      ))
    })

    for x, y in zip(changes, changes[1:]):
      data["sub"].append({
        "from": x,
        "to": y,
        "text": input("{}->{}: ".format(
          print_name(x),
          print_name(y)
        )),
        "link": input("{}->{}::link?: ".format(
          print_name(x),
          print_name(y)
        ))
      })

    data["sub"].append({
      "from": changes[len(changes) - 1],
      "to": data["to"],
      "text": input("{}->{}: ".format(
        print_name(changes[len(changes) - 1]),
        print_name(data["to"])
      )),
      "link": input("{}->{}::link?: ".format(
        print_name(changes[len(changes) - 1]),
        print_name(data["to"])
      ))
    })

  return date, data
