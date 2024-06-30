#!/bin/python

from decimal import Decimal


class ApplicationStream:
    def __init__(self, l, t):
        self.l = Decimal(l)
        self.t = Decimal(t)

    def getMathExpectation(self) -> Decimal:
        return Decimal(1) / self.l

    def getDisperse(self) -> Decimal:
        return Decimal(1) / (self.l ** 2)

    def getInterquartileRange(self) -> Decimal:
        return self.getDisperse().sqrt()

    def getVariationCoeff(self) -> Decimal:
        return self.getInterquartileRange() / self.getMathExpectation()


class ApplicationCount:
    def __init__(self, l, t, k):
        self.l = Decimal(l)
        self.t = Decimal(t)
        self.k = Decimal(k)

    def getMathExpectation(self) -> Decimal:
        return self.l * self.t

    def getDisperse(self) -> Decimal:
        return self.l * self.t

    def getInterquartileRange(self) -> Decimal:
        return self.getDisperse().sqrt()

    def getVariationCoeff(self) -> Decimal:
        return self.getInterquartileRange() / self.getMathExpectation()


kLambda = 5
kTau = 5

t1 = ApplicationStream(kLambda, kTau)
t2 = ApplicationCount(kLambda, kTau, -1)

print("Задача 1:")
print("Мат. ожидание: ", t1.getMathExpectation())
print("Дисперсия:     ", t1.getDisperse())
print("СКО:           ", t1.getInterquartileRange())
print("Коэф. вариации:", t1.getVariationCoeff())

print("Задача 2:")
print("Мат. ожидание: ", t2.getMathExpectation())
print("Дисперсия:     ", t2.getDisperse())
print("СКО:           ", t2.getInterquartileRange())
print("Коэф. вариации:", t2.getVariationCoeff())
