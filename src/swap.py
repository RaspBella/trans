def main():
    import json

    file = open("data.json", "r")

    trains = json.load(file)

    file.close()

    while True:
        date = input("Swap journeys on `date`: ").strip()

        if date == "":
            break

        if date in trains:
            if isinstance(trains[date], list):
                for x in range(len(trains[date])):
                    print(str(x) + ":", str(trains[date][x]))

                start = int(input("input starting index: "))
                end = int(input("ending index: "))

                if start < 0:
                    break

                if end > len(trains[date]) - 1:
                    break

                temp = trains[date][start]
                trains[date][start] = trains[date][end]
                trains[date][end] = temp

                print("Now swapped")

                for x in range(len(trains[date])):
                    print(str(x) + ":", str(trains[date][x]))

            else:
                break
        else:
            break

    file = open("data.json", "w")

    json.dump(trains, file)

    file.close()

if __name__ == "__main__":
    main()
