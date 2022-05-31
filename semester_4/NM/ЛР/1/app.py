import math

def task4 (a: float, b: float, delta_a: float, delta_b: float, n:int):
    print ("| О |  Абсолютная  |  Относительная  |  _ * 10^(-5)")

    abs_delta = (delta_a + delta_b) * (10 ** 5)
    print ("| + | %13.10f | %15.12f |" % (abs_delta, abs_delta / abs (a + b)))
    
    abs_delta = (delta_a + delta_b) * (10 ** 5)
    print ("| - | %13.10f | %15.12f |" % (abs_delta, abs_delta / abs (a - b)))
    
    abs_delta = (abs (a) * delta_b + abs (b) * delta_a) * (10 ** 5)
    print ("| * | %13.10f | %15.12f |" % (abs_delta, abs_delta / (a * b)))
    
    abs_delta = ((abs (a) * delta_b + abs (b) * delta_a) / (math.pow(b, 2))) * (10 ** 5)
    print ("| / | %13.10f | %15.12f |" % (abs_delta, abs_delta / (a / b)))
    
    abs_delta = (n * math.pow(a, n - 1) * delta_a) * (10 ** 5)
    print ("| ^ | %13.10f | %15.12f |" % (abs_delta, abs_delta / math.pow (a, n)))

task4 (0.1234, 1.7658, 0.00001, 0.00001, 4)
