from decimal import Decimal
from mstypes import Point, Range

result = Range(Point("400", "0.2"), Point("20", "0.4"), Point("100", "0.4"))
print("Математическое ожидание:", result.mathExpectation())
print("Дисперсия:", result.disperse())
print("Начальный момент 2:", result.rawMoment(2))
print("Среднеквадратичное отклонение:", result.interquartileRange())
print("Коэффициент вариации:", result.variationCoeff())
