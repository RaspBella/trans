def combine_data(data, date, new):
  if date in data:
    if isinstance(data[date], list):
      data[date].append(new)
    else:
      data[date] = [data[date], new]
  else:
    data[date] = new

    data = dict(sorted(data.items()))

  return data

def main():
  import json
  from question import question

  filename = "../docs/data.json"

  with open(filename, "r") as f:
    data = json.load(f)

  date, new = question()

  print({date: new})

  if "y" in input("Confirm: ").lower():
    data = combine_data(data, date, new)

    with open(filename, "w") as f:
      json.dump(data, f)

if __name__ == "__main__":
  main()
