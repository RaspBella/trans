def main():
    import json
    import os

    datafile = open('data.json', 'r')
    data = json.load(datafile)
    datafile.close()

    table = f'''        <div>
            <table>
                <tr>
                    <th>Date</th>
                    <th>From</th>
                    <th>To</th>
                    <th>Change(s)</th>
                    <th>Transportation</th>
                </tr>'''

    for date in data: # each page
        if isinstance(data[date], dict):
            # handy
            from_ = data[date]['from']
            to = data[date]['to']
            change = data[date]['change']
            trans = data[date]['trans']

            html = f'''        <div>
            <h1>{date} - {from_} to {to}</h1>
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
            </table>
        </div>'''

                else:
                    html += f'''            <tr>
                    <td>{from_}</td>
                    <td>{to}</td>
                    <td>{trans}</td>
                </tr>
            </table>
        </div>'''

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
                    <td>{stations[x+1]}</td>
                    <td>{trans[x]}</a></td>'''

                html += f'''
            </table>
        </div>'''
        
        if isinstance(data[date], list):
            html = f'''        <div>
            <h1>{date}</h1>'''

            for x in data[date]:
                html += f'''
            <h1>{x["from"]} to {x["to"]}</h1>'''

            html += f'''
            <table>
                <tr>
                    <th>From</th>
                    <th>To</th>
                    <th>Transportation</th>
                </tr>'''

            for x in data[date]:
                # handy
                from_ = x['from']
                to = x['to']
                change = x['change']
                trans = x["trans"]

                if isinstance(trans, str):
                    if 'http' in trans:
                        html += f'''            <tr>
                    <td>{from_}</td>
                    <td>{to}</td>
                    <td><a href={trans}>{trans}</a></td>
                </tr>'''

                    else:
                        html += f'''            <tr>
                    <td>{from_}</td>
                    <td>{to}</td>
                    <td>{trans}</td>
                </tr>'''

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
                    <td>{stations[x+1]}</td>
                    <td>{trans[x]}</a></td>'''

            html += f'''
            </table>
        </div>'''
        
        os.makedirs(date, exist_ok=True)

        template = open('template.html', 'r')
        index = open(date + "/index.html", "w")

        text = template.read()
        text = text.replace('<!--REPLACE-->', html)

        index.write(text)

        template.close()
        index.close()



        #main page
        trans_td = ''

        if isinstance(data[date], dict):
            # handy
            from_ = data[date]["from"]
            to = data[date]["to"]
            change = data[date]["change"]
            trans = data[date]["trans"]

            if isinstance(trans, str):
                if "http" in trans:
                    trans_td = f'<a href={trans}>{trans}</a>'
                else:
                    trans_td = trans
            else:
                stations = [from_] + change + [to]

                trans_td = '<br>'.join([
                        f'{stations[x]}->{stations[x+1]}: <a href={trans[x]}>{trans[x]}</a>'
                        if 'http' in trans[x]
                        else
                        f'{stations[x]}->{stations[x+1]}: {trans[x]}'
                        for x in range(len(stations) - 1)
                ])

                change = '<br>'.join(change)

            table += f'''
                <tr>
                    <td><a href={date}>{date}</a></td>
                    <td>{from_}</td>
                    <td>{to}</td>
                    <td>{change}</td>
                    <td>{trans_td}</td>
                </tr>'''

        if isinstance(data[date], list):
            for x in data[date]:
                # handy
                from_ = x["from"]
                to = x["to"]
                change = x["change"]
                trans = x["trans"]

                if isinstance(trans, str):
                    if "http" in trans:
                        trans_td = f'<a href={trans}>{trans}</a>'
                    else:
                        trans_td = trans
                else:
                    stations = [from_] + change + [to]

                    trans_td = '<br>'.join([
                        f'{stations[x]}->{stations[x+1]}: <a href={trans[x]}>{trans[x]}</a>'
                        if 'http' in trans[x]
                        else
                        f'{stations[x]}->{stations[x+1]}: {trans[x]}'
                        for x in range(len(stations) - 1)
                    ])

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
            </table>
        </div>
        <script type="text/javascript" src="time.js"></script>'''

    template = open('template.html', 'r')
    index = open('index.html', 'w')

    text = template.read()
    text = text.replace('<!--REPLACE-->', table)

    index.write(text)

    template.close()
    index.close()

if __name__ == '__main__':
    main()
