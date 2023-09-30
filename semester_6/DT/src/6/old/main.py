from typing import List

import data


def _get_eigenvector_var1(m: List[List[float]]) -> List[float]:
    """Получение собственного вектора по методу 1."""
    by_row_sum = [sum(row) for row in m]
    total_sum = sum(by_row_sum)

    return list(e / total_sum for e in by_row_sum)


def _get_eigenvector_var3(m: List[List[float]]) -> List[float]:
    """Получение собственного вектора по методу 3."""
    t = [
        1 / sum(row[col_num] for row in m)
        for col_num in range(len(m[0]))
    ]
    s = sum(t)
    return [e/s for e in t]


get_eigenvector = _get_eigenvector_var3


def get_vector_w1(m: List[List[float]], w: List[float]) -> List[float]:
    """Подсчёт вектора w' на основе m и w."""
    ret = []

    for row in m:
        s = sum(x * y for (x, y) in zip(row, w))
        ret.append(s)

    return ret


def get_vector_w11(w: List[float], w1: List[float]) -> List[float]:
    """Подсчёт вектора w'' на основе векторов w и w'."""
    return [x / y for (x, y) in zip(w1, w)]


def get_matrix_eigenvalue(m: List[List[float]]) -> float:
    w = get_eigenvector(m)
    w1 = get_vector_w1(m, w)
    w11 = get_vector_w11(w, w1)
    l_max = sum(w11) / len(w11)

    return l_max


def get_consistency_index(eigenvalue: float, n: int) -> float:
    return (eigenvalue-n) / (n-1)


def get_scores(p: List[List[float]], *other: List[List[float]]) -> List[float]:
    w1 = get_eigenvector(p)
    w2 = [get_eigenvector(m) for m in other]

    return [
        sum(
            w1[j] * w2[j][i]
            for j in range(len(w1)-1)
        )
        for i in range(len(other))
    ]


for title, m in (('A', data.A),
                 ('A1', data.A1),
                 ('A2', data.A2),
                 ('A3', data.A3),):
    print(title)
    w = get_eigenvector(m)
    print('w =', w)
    w_ = get_vector_w1(m, w)
    print("w' =", w_)
    w__ = get_vector_w11(w, w_)
    print("w'' =", w__)
    l_max = get_matrix_eigenvalue(m)
    print("\lambda _{max} =", l_max)
    ci = get_consistency_index(l_max, len(w__))
    print('ИС =', ci)
    print('\n\n')
scores = get_scores(data.A, data.A1, data.A2, data.A3)
print('D =', scores)
