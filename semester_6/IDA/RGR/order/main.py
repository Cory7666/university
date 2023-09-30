from csv import DictWriter

class ValueNormalizer:
    def __init__(self, value: str) -> None:
        self._value = value

    def normalize(self) -> str:
        if 'cheese' in self._value:
            return 'cheese'
        elif 'milk' in self._value:
            return 'milk'
        elif 'eggs' in self._value:
            return 'eggs'
        elif 'beer' in self._value:
            return 'beer'
        elif 'bread' in self._value:
            return 'bread'
        elif 'wine' in self._value:
            return 'wine'
        elif 'oil' in self._value:
            return 'oil'
        elif self._value.endswith('fruit') or self._value.endswith('fruits'):
            return 'fruit'
        elif self._value.endswith('vegetable') or self._value.endswith('vegetables') or 'potato' in self._value:
            return 'vegetable'
        elif 'juice' in self._value:
            return 'juice'
        elif 'meat' in self._value:
            return 'meat'
        elif 'rolls' in self._value:
            return 'rolls'
        elif 'bakery' in self._value:
            return 'bakery'
        elif 'cosmetics' in self._value or 'hygiene articles' == self._value:
            return 'cosmetics'
        elif 'chocolate' in self._value:
            return 'chocolate'
        elif 'sweet' in self._value:
            return 'sugar'
        else:
            return self._value

out_filename = 'out.csv'
with open('groceries.csv', 'r') as infile, \
    open(out_filename, 'w', newline='') as outfile:
    writer = DictWriter(outfile, ('index', 'value'))
    writer.writeheader()
    order_counter = 1

    while True:
        values = infile.readline().strip().split(',')
        if len(values) == 0 or len(values[0]) == 0:
            break
        if len(values) > 4:
            values_set = set()
            for value in values:
                values_set.add(ValueNormalizer(value).normalize())
            
            if len(values_set) > 6:
                for value in values_set:
                    writer.writerow({
                        'index': f'order{order_counter}',
                        'value': value,
                    })
                order_counter += 1

