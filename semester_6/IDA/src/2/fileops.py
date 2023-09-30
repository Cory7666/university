from csv import DictReader


def get_unique_pairs_from_file(filename: str) -> set[tuple[str, str]]:
    with open(filename, 'r') as file:
        reader = DictReader(file)
        fieldnames = set(reader.fieldnames)

    pairs = set()

    for field_one in fieldnames:
        for field_two in fieldnames:
            if field_one != field_two:
                pairs.add(frozenset((field_one, field_two)))

    return set(
        map(
            lambda s: tuple(s),
            pairs
        )
    )


def column_iterator(filename: str, column_name: str):
    with open(filename, 'r') as file:
        reader = DictReader(file)
        if column_name in reader.fieldnames:
            for row in reader:
                yield float(row[column_name])
