from typing import Literal


matrixes = [
    {
        'name': 'Матрица с рисунка 4',
        'value': [
            [0, 0, 1, 0, 0],
            [0, 0, 1, 0, 0],
            [0, 0, 0, 1, 1],
            [0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0]
        ],
        'expected': {0, 1}
    },
    {
        'name': 'Матрица с рисунка 5',
        'value': [
            [0, 0, 1, 0, 0],
            [0, 0, 1, 0, 0],
            [0, 1, 0, 1, 1],
            [0, 0, 1, 0, 0],
            [0, 0, 0, 0, 0]
        ],
        'expected': {0}
    },
    {
        'name': 'Матрица с рисунка 6',
        'value': [
            [0, 0, 1, 0, 0],
            [0, 0, 1, 0, 0],
            [0, 0, 0, 1, 1],
            [0, 0, 1, 0, 0],
            [0, 0, 1, 0, 0]
        ],
        'expected': {0, 1}
    },
    {
        'name': 'Матрица с рисунка 7a',
        'value': [
            [0, 0, 0, 1, 0],
            [0, 0, 1, 0, 0],
            [0, 0, 0, 1, 1],
            [0, 0, 1, 0, 0],
            [0, 0, 1, 0, 0]
        ],
        'expected': {0, 1}
    },
    {
        'name': 'Матрица с рисунка 7б',
        'value': [
            [0, 1, 0, 1, 0],
            [1, 0, 1, 0, 0],
            [0, 0, 0, 1, 1],
            [0, 0, 1, 0, 0],
            [0, 0, 0, 0, 0]
        ],
        'expected': {0, 1}
    },
    {
        'name': 'Матрица с рисунка 8',
        'value': [
            [0, 1, 1, 0, 0, 0, 0],
            [0, 0, 1, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 1, 1],
            [0, 1, 0, 0, 0, 1, 0],
            [0, 1, 0, 1, 0, 1, 0],
            [0, 0, 0, 0, 0, 0, 1],
            [0, 0, 0, 0, 0, 0, 0]
        ],
        'expected': [{0, 4}, {3}, {1}, {2}, {5}, {6}]
    },
    {
        'name': 'Матрица с рисунка 9',
        'value': [
            [0, 1, 1, 0, 0],
            [0, 0, 1, 1, 0],
            [0, 0, 0, 1, 1],
            [0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0]
        ],
        'expected': [{0}, {1}, {2}, {3, 4}]
    },
    {
        'name': 'Матрица с рисунка 10',
        'value': [
            [0, 1, 0, 0, 0, 0],
            [1, 0, 1, 1, 0, 0],
            [0, 0, 0, 0, 0, 0],
            [0, 1, 0, 0, 1, 0],
            [0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 1, 0]
        ],
        'expected': {0, 1, 3, 5}
    },
    {
        'name': "Какой-то граф",
        'value': [
            [0, 1, 1, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0],
            [1, 0, 0, 0, 0, 0, 0],
            [0, 1, 0, 0, 1, 0, 0],
            [0, 0, 0, 1, 0, 0, 0],
            [0, 0, 1, 0, 0, 0, 1],
            [0, 1, 0, 0, 0, 0, 0]
        ],
        'expected': {3, 4, 5}
    }
]


def find_dominants(
        matrix: list[list[int]],
        exclude_points_set: set[int] = set()
) -> set[int]:
    n = len(matrix)
    return_set = {i for i in range(n)}
    for i in range(n):
        for j in range(n):
            if matrix[i][j] == 1 \
                    and (matrix[j][i] == 0 or (matrix[j][i] == 1 and i not in return_set)):
                return_set -= {j}

                for k in range(n):
                    if matrix[j][k] == 1 and k in return_set:
                        return_set -= {k}

    return return_set - exclude_points_set


def find_dominated(
        matrix: list[list[int]]
) -> set[int]:
    n = len(matrix)
    return {
        inum
        for inum in range(n)
        if sum(matrix[inum]) == 0
    }


def fill_row(
        matrix: list[list[int]],
        row_number: int,
        value: Literal[0, 1]
) -> None:
    for i in range(len(matrix)):
        matrix[row_number][i] = value


def fill_column(
        matrix: list[list[int]],
        col_number: int,
        value: Literal[0, 1]
) -> None:
    for i in range(len(matrix)):
        matrix[i][col_number] = value


def do_task1(matrix: list[list[int]]) -> set[int]:
    s = find_dominants(matrix)
    return s


def do_task2(matrix: list[list[int]]) -> list[set[int]]:
    counter = 1
    results = []
    s_2 = set()
    s = find_dominants(matrix)

    while len(s) > 0:
        print(counter, ':', s)
        counter += 1
        s_2 |= s
        for num in s:
            fill_row(matrix, num, 0)
        results.append(s)
        s = find_dominants(matrix, s_2)

    return results


def do_task3(matrix: list[list[int]]) -> list[set[int]]:
    counter = 1
    results = []
    s_2 = set()
    s = find_dominated(matrix)

    while len(s) > 0:
        print(counter, ':', s)
        counter += 1
        s_2 |= s
        for num in s:
            fill_column(matrix, num, 0)
        results.append(s)
        s = find_dominated(matrix) - s_2

    return results


def main() -> None:
    # for i in [0, 1, 2, 3, 4, 7]:
    # for i in [5, 6]:
    for i in [8]:
        result = do_task1(matrixes[i]['value'])
        expected = matrixes[i]['expected']
        # expected = list(reversed(matrixes[i]['expected']))
        print(f"Тест <{matrixes[i]['name']}>", '->', expected,
              '==', result, '=', result == expected)


main()
