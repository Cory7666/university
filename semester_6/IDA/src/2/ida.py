from math import sqrt
from numbers import Number


def cortest(
        r: Number,
        n: Number
) -> Number:
    return (r * sqrt(n - 2)) / sqrt(1 - (r**2))
