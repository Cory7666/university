from decimal import Decimal
from math import sqrt


class Point:
    def __init__(self, x: Decimal, p: Decimal) -> None:
        self.x: Decimal = Decimal(x)
        self.p: Decimal = Decimal(p)


class Range:
    def __init__(self, *points: Point) -> None:
        self.__points = points

    def mathExpectation(self) -> Decimal:
        """
        Вычислить математическое ожидание.
        """
        return self.rawMoment(1)

    def disperse(self) -> Decimal:
        """
        Вычислить дисперсию.
        """
        return self.standardizedMoment(2)

    def rawMoment(self, s: int) -> Decimal:
        """
        Вычислить начальный момент s.
        """
        return Decimal(sum([(point.p * point.x ** s) for point in self.__points]))

    def standardizedMoment(self, s: int) -> Decimal:
        """
        Вычислить центральный момент s.
        """
        m: Decimal = self.mathExpectation()
        return Decimal(sum([(point.p * (point.x - m) ** s) for point in self.__points]))

    def interquartileRange(self) -> Decimal:
        """
        Вычислить среднеквадратичное отклонение.
        """
        return self.disperse().sqrt()

    def variationCoeff(self) -> Decimal:
        """
        Коэффициент вариации.
        """
        return self.interquartileRange() / self.mathExpectation()
