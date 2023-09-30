from typing import Literal


input_matrix = [
    [0, 0, 1, 0, 0],
    [0, 0, 1, 0, 0],
    [0, 1, 0, 1, 1],
    [0, 0, 1, 0, 0],
    [0, 0, 0, 0, 0]
]


def find_columns_with_only_zeros(matrix):
    n = len(matrix)
    return [
        inum
        for inum in range(n)
        if sum(
            [matrix[i][inum] for i in range(n)]
        ) == 0
    ]


def find_rows_with_only_zeros(matrix):
    n = len(matrix)
    return [
        inum
        for inum in range(n)
        if sum(
            [matrix[inum][i] for i in range(n)]
        ) == 0
    ]


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


def do_task1():
    print(find_columns_with_only_zeros(input_matrix))


def do_task2():
    counter = 1
    s = find_columns_with_only_zeros(input_matrix)
    while len(s) > 0:
        print(counter, ":", s)
        counter += 1
        for i in s:
            fill_row(input_matrix, i, 0)
        for i in s:
            fill_column(input_matrix, i, 1)
        s = find_columns_with_only_zeros(input_matrix)


def do_task3():
    counter = 1
    s = find_rows_with_only_zeros(input_matrix)
    while len(s) > 0:
        print(counter, ':', s)
        counter += 1
        for i in s:
            fill_column(input_matrix, i, 0)
        for i in s:
            fill_row(input_matrix, i, 1)
        s = find_rows_with_only_zeros(input_matrix)


def main() -> None:
    do_task2()


main()
