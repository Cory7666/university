import numpy as np
from data2 import R


def _gen_E_matrix(size: int):
    return np.ones(size) - np.diag([1] * size)


def _opred_poter_matrix_p(R_list: list[np.matrix]):
    rows, cols = R_list[0].shape
    p = np.zeros((rows, cols))
    for row in range(rows):
        for col in range(cols):
            if row != col:
                k = 0
                for (R_idx, R_k) in enumerate(R_list):
                    if R_k[row, col] > R_list[k][row, col]:
                        k = R_idx
                for (R_idx, R_n) in enumerate(R_list):
                    p[row, col] += R_list[k][row, col] - R_n[row, col]
    return p


def _opred_poter_matrix_Qn(p: np.matrix):
    E = _gen_E_matrix(p.shape[0])
    return E @ p @ E


def _find_min_element(Qn: np.matrix, selected_idxs, rows, cols):
    match_flag = False
    min_row, min_col = 0, 0

    for row in range(Qn.shape[0]):
        for col in range(Qn.shape[1]):
            if ((rows[row] != cols[col])
                    and (rows[row] not in selected_idxs)
                    and (cols[col] not in selected_idxs)):
                if match_flag:
                    if (Qn[min_row, min_col] > Qn[row, col]):
                        min_row, min_col = row, col
                else:
                    match_flag = True
                    min_row, min_col = row, col


    return (min_row, min_col)


def _print_R_list(R_list: list[np.matrix]):
    for (R_idx, R_n) in enumerate(R_list):
        print(f"R{R_idx+1} =")
        print(R_n)


def main():
    R_answer = [-1] * R[0].shape[0]
    N = len(R_answer)
    offset = 0
    col_idxs = [idx for idx in range(N)]
    row_idxs = [idx for idx in range(N)]

    while N > 0:
        print(f"Iteration {offset+1}:")
        print('N =', N)
        print('col_idxs =', col_idxs)
        print('row_idxs =', row_idxs)
        print('R_answer =', R_answer)

        _print_R_list(R)
        p = _opred_poter_matrix_p(R)
        print('p =')
        print(p)

        Qn = _opred_poter_matrix_Qn(p)
        print('Qn =')
        print(Qn)

        coords = _find_min_element(Qn, R_answer, row_idxs, col_idxs)
        print("q_{%d %d} = %d" % (coords[0], coords[1], Qn[coords]))

        for idx in range(len(R)):
            R[idx] = np.delete(np.delete(R[idx], coords[0], 0), coords[1], 1)

        R_answer[offset] = col_idxs[coords[1]]
        R_answer[len(R_answer) - offset - 1] = row_idxs[coords[0]]
        del row_idxs[coords[0]]
        del col_idxs[coords[1]]
        N -= 2
        offset += 1

    print(f"R = {[(r + 1) for r in R_answer]}")


main()
