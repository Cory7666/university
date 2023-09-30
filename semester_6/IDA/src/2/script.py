from csv import DictReader
from scipy.stats.mstats import pearsonr, spearmanr

from fileops import column_iterator, get_unique_pairs_from_file
from ida import cortest

filename = '/home/alex/Documents/Yandex.Disk/files/Work/University/Activity/IDA/datasets/accepted/2019_converted.csv'
results: list[tuple[float, tuple[str, str]]] = list()

n = len(list(column_iterator(filename, 'score')))

for pair in get_unique_pairs_from_file(filename):
    values_1 = list(column_iterator(filename, pair[0]))
    values_2 = list(column_iterator(filename, pair[1]))
    results.append(
        (
            pearsonr(
                values_1,
                values_2
            )[0],
            spearmanr(
                values_1,
                values_2
            )[0],
            pair
        )
    )

print('Корреляция Пирсона:')
for result in sorted(results, key=lambda x: abs(x[0]), reverse=True):
    print(f"r={result[0]}, t={cortest(result[0], n)}, pair={result[-1]}")

print('Корреляция Спирмана:')
for result in sorted(results, key=lambda x: abs(x[0]), reverse=True):
    print(f"r={result[1]}, t={cortest(result[1], n)}, pair={result[-1]}")
