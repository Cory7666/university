#!/bin/python


from decimal import Decimal


class MM1ModelingMethod:
    def __init__(self, l, mu):
        self.l = Decimal(l)
        self.mu = Decimal(mu)
        self.b = Decimal(1) / mu

    def getZagruzka(self) -> Decimal:
        return min(self.l * self.b, Decimal(1))

    def getNagruzka(self) -> Decimal:
        return self.l / self.mu

    def getAverageWait(self) -> Decimal:
        n = self.getZagruzka()
        return (n * self.b) / (Decimal(1) - n)

    def getAverageStay(self) -> Decimal:
        n = self.getNagruzka()
        return self.b / (Decimal(1) - n)

    def getAverageQueueLength(self) -> Decimal:
        w = self.getAverageWait()
        return self.l * w

    def getAverageApplicationCount(self) -> Decimal:
        u = self.getAverageStay()
        return self.l * u


kL = 9
kMu = 10

task = MM1ModelingMethod(kL, kMu)

print("Нагрузка:            ", task.getNagruzka())
print("Загрузка:            ", task.getZagruzka())
print("Сред. время ожидания:", task.getAverageWait())
print("Сред. время пребывания в системе:", task.getAverageStay())
print("Сред. длина очереди:         ", task.getAverageQueueLength())
print("Сред. чисkо заявок в системе:", task.getAverageApplicationCount())
