import numpy

coeffs = numpy.matrix(
    [
        [0.1,
         0.05,
         0.15,
         0.15,
         0.2,
         0.1,
         0.1,
         0.1,
         0.05]
    ]
)
values = numpy.matrix(
    [
        [7, 5, 7],
        [9, 9, 3],
        [8, 8, 4],
        [9, 9, 3],
        [4, 7, 9],
        [8, 5, 2],
        [7, 6, 7],
        [6, 8, 4],
        [2, 2, 7]
    ]
)

print(numpy.sum(coeffs))
print("Result:", coeffs @ values)
