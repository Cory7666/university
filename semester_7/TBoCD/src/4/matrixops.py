from typing import List

BoolSquareMatrix = List[List[bool]]
GramarMatrix = List[List[str]]

def make_plus_matrix(input: BoolSquareMatrix):
    n = len(input)
    output = [ [(element if colidx != rowidx else False)
                for (colidx, element) in enumerate(row)]
              for (rowidx, row) in enumerate(input) ]
    for row in range(n):
        for col in range(n):
            for k in range(n):
                if not output[row][col]:
                    output[row][col] = output[row][k] and output[k][col]
    return output

def to_string(input: BoolSquareMatrix, name = 'matrix'):
    return '\n'.join(
        [str(name) + ' = ['] + [
            '\n'.join([
                ' '.join([('0' if elem else '_') for elem in row])
            ]) for row in input
        ] + [']']
    )

def make_gramar(eq: BoolSquareMatrix, lt_dot: BoolSquareMatrix, dot_gt: BoolSquareMatrix) -> GramarMatrix:
    n = len(eq)
    return [[
        ('=' if eq[row][col] else (
            '<' if lt_dot[row][col] else (
                '>' if dot_gt[row][col] else '_'
            ))) for col in range(n)
    ] for row in range(n)]

def fill_gramar_if_absent(gramar, filler: str, start, stop):
    for row in range(start[1], stop[1]):
        for col in range(start[0], stop[0]):
            if gramar[row][col] == '_':
                gramar[row][col] = filler

def gramar_to_string(input: GramarMatrix, name = 'gramar'):
    return '\n'.join(
        [f'{name} = ['] + [
            ' '.join([
                elem for elem in row
            ]) for row in input
        ] + [']']
    )

def transpose(input: BoolSquareMatrix):
    import copy
    ret = copy.deepcopy(input)
    for row in range(len(ret)):
        for col in range(row + 1, len(ret)):
            tmp = ret[row][col]
            ret[row][col] = ret[col][row]
            ret[col][row] = tmp
    return ret

def multiply(m1: BoolSquareMatrix, m2: BoolSquareMatrix) -> BoolSquareMatrix:
    n = len(m1)
    ret = [ ([False] * n) for _ in range(n) ]
    for row in range(n):
        for col in range(n):
            for k in range(n):
                if m1[row][k] and m2[k][col]:
                    ret[row][col] = True
                    break
    return ret

def plus(m1: BoolSquareMatrix, m2: BoolSquareMatrix) -> BoolSquareMatrix:
    return [
        [(m1[row][col] or m2[row][col]) for col in range(len(m1))]
        for row in range(len(m1))
    ]

def ones(size: int) -> BoolSquareMatrix:
    return [
        [(row == col) for col in range(size)] for row in range(size)
    ]

def make_lt_dot_rel_matrix(equiv: BoolSquareMatrix, first: BoolSquareMatrix):
    return multiply(equiv, make_plus_matrix(first))

def make_dot_gt_rel_matrix(equiv: BoolSquareMatrix, first: BoolSquareMatrix,
                           last: BoolSquareMatrix):
    return multiply(multiply(transpose(make_plus_matrix(last)), equiv),
                    plus(ones(len(equiv)), make_plus_matrix(first)))
