from dataclasses import dataclass
import matplotlib.pyplot as pl
from csv import DictWriter

@dataclass
class Stat:
    d_ii: float
    d_ij: float
    m: int

    @property
    def j1(self) -> float:
        return self.d_ii * 2 / (self.m * (self.m - 1))
    
    @property
    def j2(self) -> float:
        return self.d_ij / self.m
    
    @property
    def J(self) -> float:
        return self.j1 / self.j2

stats = [
    Stat(m=2, d_ii=90.93345, d_ij=154.6535),
    Stat(m=3, d_ii=55.32351, d_ij=190.2635),
    Stat(m=4, d_ii=40.32133, d_ij=190.2635),
    Stat(m=5, d_ii=29.87446, d_ij=215.7125),
    Stat(m=6, d_ii=26.20787, d_ij=219.3791),
    Stat(m=7, d_ii=24.20457, d_ij=221.3824),
    Stat(m=8, d_ii=22.42567, d_ij=223.1613),
    Stat(m=9, d_ii=20.82057, d_ij=224.7664)
]

with open('output-data.csv', 'w', newline='') as file:
    writer = DictWriter(
        file,
        ('Clusters', 'Dii', 'm', 'Dij', 'J1', 'J2', 'J')
    )
    writer.writeheader()
    for stat in stats:
        writer.writerow({
            'Clusters': stat.m,
            'Dii': stat.d_ii,
            'm': stat.m,
            'Dij': stat.d_ij,
            'J1': stat.j1,
            'J2': stat.j2,
            'J': stat.J
        })


pl.plot(*[
    [s.m for s in stats],
    [s.J for s in stats]
])
pl.xlabel('m')
pl.ylabel('J')
pl.show()
