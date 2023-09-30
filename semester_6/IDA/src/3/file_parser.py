from csv import DictReader, DictWriter

filename = '/run/media/alex/8B9D-E766/honeyproduction_1_.csv'
output_filename = './output_2.csv'
method_count = 5

data: list[tuple[float, float]] = list()
field_chosen: tuple[int, int] = tuple()

with open(filename, 'r') as file:
    reader = DictReader(file)

    fieldnames = list(reader.fieldnames)

    print(
        f"Доступные поля:\n{list([(index, value) for index, value in enumerate(fieldnames)])}")

    field_chosen = tuple(
        map(lambda x: fieldnames[int(x)], input('Выберите два поля:').split()))

    for record in reader:
        data.append((record[field_chosen[0]], record[field_chosen[1]]))

data.sort(key=lambda x: x[1])

k = len(data) // method_count
with open(output_filename, 'w') as ofile:
    writer = DictWriter(ofile, fieldnames=('Value', 'Method'))
    writer.writeheader()
    for index, d in enumerate(data):
        writer.writerow({'Value': d[0], 'Method': f"Method_{y if (y := (index // k) + 1) <= k else k}"})
