from dataclasses import dataclass
import numpy as np
import data as lwdata


@dataclass
class AnalysisResult:
    w: np.ndarray
    w_: np.ndarray
    w__: np.ndarray
    lambda_max: float
    consist_idx: float

    def __str__(self) -> str:
        return f"""\
{self.__class__.__name__}(
    w   = {self.w},
    w'  = {self.w_},
    w'' = {self.w__},
    lambda_max = {self.lambda_max},
    consist_index = {self.consist_idx}
)"""


class AlternativeCharacteristics:
    def __init__(self, A: np.ndarray) -> None:
        self.A = A

    def do_analysis(self):
        w = self._calc_eigenvector()
        w_ = self.A @ w
        w__ = w_ / w
        n = w__.shape[-1]
        lambda_max = np.sum(w__) / n
        consist_idx = (lambda_max / n) / (n - 1)

        return AnalysisResult(w, w_, w__, lambda_max, consist_idx)

    def _calc_eigenvector(self):
        other = self.A.copy()
        for col in range(other.shape[-1]):
            col_sum = 0
            for row in range(other.shape[0]):
                col_sum += other[row, col]

            for row in range(len(other)):
                other[row, col] = other[row, col] / col_sum

        return np.array([(np.sum(row) / row.shape[-1]) for row in other])


def main():
    A_res = AlternativeCharacteristics(lwdata.A).do_analysis()
    An_res = [
        AlternativeCharacteristics(lwdata.A1).do_analysis(),
        AlternativeCharacteristics(lwdata.A2).do_analysis(),
        AlternativeCharacteristics(lwdata.A3).do_analysis(),
        AlternativeCharacteristics(lwdata.A4).do_analysis(),
    ]
    print("A:")
    print(A_res)
    for (idx, A) in enumerate(An_res):
        print(f"A[{idx+1}]:")
        print(A)

    O = [
        [ An.w[An_idx] for An in An_res ]
        for An_idx in range(len(An_res[0].w))
    ]
    O_matrix = np.matrix(O)
    print("O:")
    print(O_matrix)

    D = O_matrix @ A_res.w
    print("D:")
    print(D)



main()
