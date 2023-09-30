import requests
from dataclasses import dataclass
from datetime import datetime
import bs4
from csv import DictWriter


@dataclass
class Record:
    date: datetime
    value: float


class SteamChartsApi:
    def __init__(self) -> None:
        pass

    def get_data_for_app(self, app) -> tuple[str, list[Record]]:
        response = requests.get(f'http://steamcharts.com/app/{str(app)}')
        return self._parse_data(response.text)

    def _parse_data(self, d: str) -> tuple[str, list[Record]]:
        result = []
        soup = bs4.BeautifulSoup(d)
        title = soup.select_one('#app-title').text.strip()
        table = soup.select_one('.common-table tbody')

        for row in table.select('tr'):
            try:
                date_str = row.select_one('.month-cell').text
                value_str = row.select_one('.num-f').text.replace(',', '')
                record = Record(
                    SteamChartsApi._parse_date_str(date_str),
                    float(value_str)
                )
                result.append(record)
            except Exception:
                pass

        return (title, result)

    @staticmethod
    def _parse_date_str(date: str) -> datetime:
        months = {
            'January': 1,
            'February': 2,
            'March': 3,
            'April': 4,
            'May': 5,
            'June': 6,
            'July': 7,
            'August': 8,
            'September': 9,
            'October': 10,
            'November': 11,
            'December': 12,
        }

        date_arr = date.split()
        return datetime(int(date_arr[-1]), months[date_arr[0]], 1)


data = SteamChartsApi().get_data_for_app(440)

with open(f"{data[0]}.csv", 'w', newline='') as file:
    writer = DictWriter(file, fieldnames=('date', 'value'))
    writer.writeheader()

    for record in sorted(data[1], key=lambda x: x.date):
        writer.writerow({
            'date': record.date.strftime('%d.%m.%Y'),
            'value': record.value,
        })
