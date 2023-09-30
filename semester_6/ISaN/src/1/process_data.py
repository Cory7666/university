#!/usr/bin/python

import csv
from decimal import Decimal
from io import TextIOWrapper


class DataPortion:
    def __init__(
            self,
            segments: int,
            freq: int,
            voltage_start: Decimal,
            voltage_end: Decimal,
            time_start: Decimal,
            time_end: Decimal
    ) -> None:
        self.segments = int(segments)
        self.freq = int(freq)
        self.voltage_start = Decimal(voltage_start)
        self.voltage_end = Decimal(voltage_end)
        self.time_start = Decimal(time_start)
        self.time_end = Decimal(time_end)

    def calcTimeDiff(self) -> Decimal:
        return self.time_end - self.time_start

    def calcPhaseAngleRads(self) -> Decimal:
        return self.calcTimeDiff() * (Decimal(self.freq) * Decimal('1e-3')) * 2


userfieldnames = (
    'Кол-во сегментов',
    'Частота генератора, Гц',
    'Напряжение входное, В',
    'Напряжение выходное, В',
    'Сдвиг по времени, мс',
    'Сдвиг по фазе'
)

plot_files: dict[int, dict[str, TextIOWrapper]] = dict()

with open('./data.csv', 'r') as file, \
        open('./data.out.csv', 'w', encoding='utf-8', newline='') as output_file_user:
    reader = csv.DictReader(file)
    writer = csv.DictWriter(
        output_file_user, fieldnames=userfieldnames, delimiter=';')
    writer.writeheader()

    for row in reader:
        data = DataPortion(**row)
        if data.segments not in plot_files.keys():
            plot_files[data.segments] = {
                'af': open(f"out-data.{data.segments}segments.csv", 'w')
            }
        print(f"{data.freq} {data.voltage_end}",
              file=plot_files[data.segments]['af'])

        writer.writerow(
            {
                'Кол-во сегментов': data.segments,
                'Частота генератора, Гц': data.freq,
                'Напряжение входное, В': data.voltage_start,
                'Напряжение выходное, В': data.voltage_end,
                'Сдвиг по времени, мс': data.calcTimeDiff(),
                'Сдвиг по фазе': data.calcPhaseAngleRads()
            }
        )

for (_, files) in plot_files.items():
    files['af'].close()
