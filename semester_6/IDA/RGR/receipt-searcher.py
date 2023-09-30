from dataclasses import dataclass
from typing import Iterable
import requests as req
from csv import DictWriter

@dataclass
class Ingredient:
    id: int
    amount: float
    name: str
    original_name: str
    tags: list[str]


@dataclass
class Receipt:
    id: int
    title: str
    ingredients: set[Ingredient]

def map_to_ingredients_object(data: dict):
    return Ingredient(
        id=int(data['id']),
        amount=float(data['amount']),
        name=str(data['name']),
        original_name=str(data['originalName']),
        tags=str(data['aisle']).split(';'),
    )

def map_to_receipt_object(data: dict):
    return Receipt(
        id=int(data['id']),
        title=str(data['title']),
        ingredients=[
            map_to_ingredients_object(v) for v in data['missedIngredients']
        ]
    )

class SpoonacularApi:
    def __init__(self, api: str) -> None:
        self.__api = str(api)

    def get_receipts(self, cuisines: Iterable[str], number: int = 2) -> Iterable[Receipt]:
        response = req.get(
            'https://api.spoonacular.com/recipes/complexSearch',
            params={
                'cuisine': ','.join(cuisines),
                'fillIngredients': True,
                'number': number,
            },
            headers={
                'x-api-key': self.__api
            },
        )

        if response.status_code < 300:
            return (
                map_to_receipt_object(d)
                for d in response.json()['results']
            )

def main():
    receipts = list(SpoonacularApi('f0fb04a6fac44cd591cfda2008bcb474').get_receipts(['italian'], number=40))
    header = ['ingredient', 'receipt']

    print(f"received {len(receipts)}")

    receipts_filtered = list(filter(lambda x: len(x.ingredients) > 5, receipts))
    print(f"подходит: {len(receipts_filtered)}")

    with open('/home/alex/Documents/Yandex.Disk/files/Work/University/Activity/IDA/RGR/output.my.csv', 'w', newline='') as file:
        writer = DictWriter(file, header)
        writer.writeheader()

        for receipt in receipts_filtered:
            for ingredient in receipt.ingredients:
                writer.writerow({
                    'ingredient': ingredient.name,
                    'receipt': receipt.title,
                })

main()
