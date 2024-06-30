# shop.py
# -------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


class FruitShop:

    def __init__(self, name, fruitPrices):
        """
            name: Название магазина фруктов

            fruitPrices: Словарь-ценник с ключами в виде фруктов
            и значениями в виде цены, например
            {'яблоки:2.00, 'апельсины': 1.50, 'груши': 1.75}
        """
        self.fruitPrices = fruitPrices
        self.name = name
        print('Welcome to %s fruit shop' % (name))

    def getCostPerPound(self, fruit):
        """
            fruit: Fruit string
        Возвращает цену 'fruit', если 'fruit'
        содержится в ценнике, иначе - None
        """
        if fruit not in self.fruitPrices:
            return None
        return self.fruitPrices[fruit]

    def getPriceOfOrder(self, orderList):
        """
            orderList: Список-заказ из кортежей (fruit, numPounds) 

        Возвращает стоимость списка заказа, включает  только значения 
        стоимости фруктов, которые имеются в ценнике магазина.
        """
        totalCost = 0.0
        for fruit, numPounds in orderList:
            costPerPound = self.getCostPerPound(fruit)
            if costPerPound != None:
                totalCost += numPounds * costPerPound
        return totalCost

    def getName(self):
        return self.name

    def __str__(self):
        return "<FruitShop: %s>" % self.getName()

    def __repr__(self):
        return str(self)
