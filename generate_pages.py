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
                    <th>RTT</th>
                </tr>'''

    for date in data:
        change = data[date]['change']
        rtt = data[date]['rtt']

        if isinstance(change, list):
            change = ', '.join(change)

        if isinstance(rtt, list):
            rtt = '<br>'.join([f'''<a href={link}>{link}</a>''' for link in rtt])

        table += f'''
                <tr>
                    <td>{date}</td>
                    <td>{data[date]['from']}</td>
                    <td>{data[date]['to']}</td>
                    <td>{change}</td>
                    <td>{rtt}</td>
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
