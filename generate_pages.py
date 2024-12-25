def main():
    import json
    import os

    datafile = open('data.json', 'r')
    data = json.load(datafile)
    datafile.close()

    table = f'''            <table>
                <tr>
                    <th>Date</th>
                    <th>From</th>
                    <th>To</th>
                    <th>Change(s)</th>
                    <th>Transportation</th>
                </tr>'''

    for date in data:
        # handy
        from_ = data[date]['from']
        to = data[date]['to']
        change = data[date]['change']
        trans = data[date]['trans']



        # each page
        os.makedirs(date, exist_ok=True)

        template = open('template.html', 'r')
        index = open(date + "/index.html", "w")

        html = f'''            <h1>{date} - {from_} to {to}</h1>
            <table>
                <tr>
                    <th>From</th>
                    <th>To</th>
                    <th>Transportation</th>
                </tr>'''

        if isinstance(trans, str):
            if 'http' in trans:
                html += f'''            <tr>
                    <td>{from_}</td>
                    <td>{to}</td>
                    <td><a href={trans}>{trans}</a></td>
                </tr>
            </table>'''

            else:
                html += f'''            <tr>
                    <td>{from_}</td>
                    <td>{to}</td>
                    <td>{trans}</td>
                </tr>
            </table>'''

        else:
            stations = [from_] + change + [to]
            for x in range(len(stations) - 1):
                if 'http' in trans[x]:
                    html += f'''            <tr>
                    <td>{stations[x]}</td>
                    <td>{stations[x+1]}</td>
                    <td><a href={trans[x]}>{trans[x]}</a></td>'''

                else:
                    html += f'''            <tr>
                    <td>{stations[x]}</td>
                    <td>{stations[x+2]}</td>
                    <td>{trans[x]}</a></td>'''

            html += f'''
            </table>'''

        text = template.read()
        text = text.replace('<!--REPLACE-->', html)

        index.write(text)

        template.close()
        index.close()



        #main page
        trans_td = ''

        if isinstance(trans, str):
            trans_td = f'<a href={trans}>{trans}</a>'
        else:
            stations = [from_] + change + [to]

            trans_td = '<br>'.join(
                    [
                        f'{stations[x]}->{stations[x+1]}: <a href={trans[x]}>{trans[x]}</a>'
                        if 'http' in trans[x]
                        else
                        f'{stations[x]}->{stations[x+1]}: {trans[x]}'
                        for x in range(len(stations) - 1)
                    ]
            )

            change = '<br>'.join(change)

        table += f'''
                <tr>
                    <td><a href={date}>{date}</a></td>
                    <td>{from_}</td>
                    <td>{to}</td>
                    <td>{change}</td>
                    <td>{trans_td}</td>
                </tr>'''

    table += f'''
            </table>'''

    template = open('template.html', 'r')
    index = open('index.html', 'w')

    text = template.read()
    text = text.replace('<!--REPLACE-->', table)

    index.write(text)

    template.close()
    index.close()

if __name__ == '__main__':
    main()
