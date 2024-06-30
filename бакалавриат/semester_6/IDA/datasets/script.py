from csv import DictReader

from scipy.stats import spearmanr
from scipy.stats import pearsonr

values: dict[str, list[float]] = dict()

with open("2019_converted.csv", 'r') as input_file:
    reader = DictReader(input_file)

    fieldnames: list[str] = list(sorted(reader.fieldnames))

    for record in reader:
        for fieldname in fieldnames:
            if fieldname in values.keys():
                values[fieldname].append(float(record[fieldname]))
            else:
                values[fieldname] = [float(record[fieldname])]

max_field_width = len(max(fieldnames, key=lambda x: len(x)))

print("Total:", values.keys(), '->', max_field_width)

print(''.center(max_field_width), end=' ')
print(' '.join(map(lambda x: x.center(max_field_width), fieldnames)))

for fieldname in fieldnames:
    print(fieldname.center(max_field_width), end=' ')
    for fieldname_dominated in fieldnames:
        print(
            "{0:.6f} ".format(pearsonr(values[fieldname], values[fieldname_dominated])[0]).center(max_field_width),
            end=''
        )
    print()

s_field = ('gdp_per_capita', 'healthy_life_expectancy')
with open('./points.out', 'w') as file:
    for index in range(len(values[s_field[0]])):
        print(f"{values[s_field[0]][index]} {values[s_field[1]][index]}", file=file)



