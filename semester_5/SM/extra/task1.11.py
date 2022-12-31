#!/bin/python

from decimal import Decimal


class TimeInterval:
    def __init__(self, a, k):
        self.a = Decimal(a)
        self.k = Decimal(k)

    def getMathExpectation(self) -> Decimal:
        return self.k / self.a

    def getDisperse(self) -> Decimal:
        return self.k / (self.a ** 2)

    def getInterquartileRange(self) -> Decimal:
        return self.getDisperse().sqrt()

    def getVariationCoeff(self) -> Decimal:
        return self.getInterquartileRange() / self.getMathExpectation()


kA = 5
kK = 9

task = TimeInterval(kA, kK)
print("Мат. ожидание: ", task.getMathExpectation())
print("Дисперсия:     ", task.getDisperse())
print("СКО:           ", task.getInterquartileRange())
print("Коэф. вариации:", task.getVariationCoeff())
