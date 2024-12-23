def main():
    import json

    datafile = open('data.json', 'r')
    data = json.load(datafile)
    datafile.close()

    table = f'''        <table>
                <tr>
                    <th>Date</th>
                    <th>From</th>
                    <th>To</th>
                    <th>Change(s)</th>
                    <th>Transportation</th>
                </tr>'''

    for date in data:
        trans = data[date]['trans']
        trans_td = ''

        change = data[date]['change']

        if isinstance(trans, str):
            trans_td = f'<a href={trans}>{trans}</a>'
        else:
            stations = [data[date]['from']] + data[date]['change'] + [data[date]['to']]

            trans_td = '<br>'.join(
                    [
                        f'{stations[x]}->{stations[x+1]}: {trans[x]}'
                        if ' ' in trans[x]
                        else
                        f'{stations[x]}->{stations[x+1]}: <a href={trans[x]}>{trans[x]}</a>' for x in range(len(stations) - 1)
                    ]
            )

            change = '<br>'.join(change)

        table += f'''
                <tr>
                    <td>{date}</td>
                    <td>{data[date]['from']}</td>
                    <td>{data[date]['to']}</td>
                    <td>{change}</td>
                    <td>{trans_td}</td>
                </tr>'''

    table += f'''
            </table>'''

    template = open('template.html.txt', 'r')
    index = open('index.html', 'w')

    text = template.read()
    text = text.replace('<!--REPLACE-->', table)

    index.write(text)

    template.close()
    index.close()

if __name__ == '__main__':
    main()
