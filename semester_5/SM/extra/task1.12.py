#!/bin/python

from decimal import Decimal


class TwoChanellSMO:
    def __init__(self, m, k):
        self.l = Decimal(1) / Decimal(m)
        self.k = Decimal(k)

    def getStreamIntensity(self) -> Decimal:
        return self.l / self.k
    
    def getVariationCoeff(self) -> Decimal:
      return 1 / self.k.sqrt() * Decimal(1/2)


kA = 5
kK = 10

task = TwoChanellSMO(kA, kK)

print ("Интенсивность потока заявок:", task.getStreamIntensity())
print ("Коэффициент вариации:       ", task.getVariationCoeff())
