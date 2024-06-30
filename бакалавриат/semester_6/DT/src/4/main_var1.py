from dataclasses import dataclass
from matplotlib import pyplot as pp
from math import sqrt


@dataclass(frozen=True)
class Point:
    x: int
    y: int

    def __gt__(self, obj) -> bool:
        return (self.x >= obj.x and self.y > obj.y) or (self.x > obj.x and self.y >= obj.y)

    def distance_to(self, other) -> float:
        return sqrt((self.x - other.x) ** 2 + (self.y - other.y) ** 2)


demo_points = [
    Point(1, 5),
    Point(2, 7),
    Point(3, 6),
    Point(3, 4),
    Point(4, 3),
    Point(5, 2),
    Point(6, 2),
    Point(7, 1),
]

var1_points = [
    Point(3, 2),
    Point(4, 5),
    Point(5, 3),
    Point(8, 3),
    Point(6, 2),
    Point(3, 8),
    Point(6, 4),
    Point(2, 5),
    Point(6, 4),
    Point(2, 5),
]


def search_dot_with_utopical_point_then_write_to_file(P: set[Point], source: list[Point]):
    utopical_point = Point(max(p.x for p in source), max(p.y for p in source))

    # Построение графика
    sorted_by_x = sorted(P, key=lambda point: point.x)
    pp.plot(list(p.x for p in sorted_by_x), list(
        p.y for p in sorted_by_x), linestyle='-', color='#00ff00')
    pp.plot(list(p.x for p in source), list(p.y for p in source),
            marker='o', linestyle='none', color='#ff0000')
    pp.plot([utopical_point.x], [utopical_point.y],
            marker='*', linestyle='none', color='#ff00ff')
    pp.grid(True)
    pp.xlabel('Criteria 1')
    pp.ylabel('Criteria 2')
    pp.show()

    point_index = 0
    dist = source[point_index].distance_to(utopical_point)

    with open('output.md', 'w') as file:
        print('№ | x | y | Расстояние до утопии', file=file)
        print('--|---|---|----', file=file)

        for point in P:
            if utopical_point.distance_to(point) < dist:
                point_index = source.index(point)
                dist = utopical_point.distance_to(point)

            print(source.index(point) + 1, point.x, point.y,
                  utopical_point.distance_to(point), sep=' | ', file=file)

        print(
            f"\nМинимальное расстояние ({dist}) у точки {point_index+1}.", file=file)


def save_result(source: list[Point], P: set[Point]):
    search_dot_with_utopical_point_then_write_to_file(P, source)


def main():
    P: set[Point] = set()
    P_rem: set[Point] = set()
    is_point_dominated = False
    points = var1_points

    for point in points:
        print()
        for pareto_point in P:
            # print("Compare:", point, pareto_point, "Result:", point >
            #       pareto_point, pareto_point > point, is_point_dominated)
            if point > pareto_point:
                # Рассматриваемое решение лучше выбранного из множества
                # решения по всем критериям
                # print("* Remove:", pareto_point)
                P_rem.add(pareto_point)
            elif pareto_point > point:
                # Решение доминируется выбранным из множества по всем критериям
                # (аксиома Парето)
                # print("* Reject:", point)
                is_point_dominated = True
            else:
                # Рассмотренные решения несравнимы
                continue

        # Удаление из Парето-границы точек, помеченных для удаления
        P -= P_rem
        P_rem = set()

        if not is_point_dominated:
            # Добавление в множество в соответствие с принципом
            # Эджворта-Парето
            P.add(point)
        else:
            is_point_dominated = False

    save_result(points, P)


main()
