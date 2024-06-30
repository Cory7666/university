from decimal import Decimal
from mstypes import Point, Range


point1, point2 = Point("150", "0.3"), Point("400", "0.7")
result = Range(point1, point2)
print("Математическое ожидание:", result.mathExpectation())
print("Дисперсия:", result.disperse())
print("Начальный момент 2:", result.rawMoment(2))
print("Среднеквадратичное отклонение:", result.interquartileRange())
print("Коэффициент вариации:", result.variationCoeff())
