#include <iostream>
#include <iomanip>
#include <cmath>
#include <thread>

using std::cout;
using std::endl;
using std::setprecision;
using value_t = long double;

value_t f(value_t x)
{ return std::pow (x, 4) - 2 * x - 4; }

void method1 (value_t start, value_t end, value_t eps, value_t& answer, int& counter)
{
    value_t x = 0.0;
    while (std::abs (end - start) > eps)
    {
        ++counter;
        x = (start + end) / 2;

        if (f(x) * f(start) < 0)
            end = x;
        else
            start = x;
    }
    answer = x;
}

void method2 (value_t start, value_t end, value_t eps, value_t& answer, int& counter)
{
    value_t x = 0.0, x_prev = 999999.0;
    if (f(start) < f(end))
    {
        x = start;
        while (std::abs (x_prev - x) > eps)
        {
            ++counter;
            x_prev = x;
            x = x_prev - ( f(x_prev) / (f(end) - f(x_prev)) ) * (end - x_prev);
        }
    }
    else
    {
        x = end;
        while (std::abs (x_prev - x) > eps)
        {
            ++counter;
            x_prev = x;
            x = x_prev - ( f(x_prev) / (f(x_prev) - f(start)) ) * (x_prev - start);
        }
    }
    answer = x;
}

int main (void)
{
    const value_t
        start_right = 1.0, end_right = 2.0,
        start_left = -1.5, end_left = -1,
        eps = 1e-15;
    value_t
        answer1_left = 0.0,  answer2_left = 0.0,
        answer1_right = 0.0, answer2_right = 0.0;
    int
        counter1_right = 0,  counter2_right = 0,
        counter1_left = 0,   counter2_left = 0;

    std::thread th1_left {method1, start_left, end_left, eps,   std::ref(answer1_left),  std::ref(counter1_left)},
                th1_right{method1, start_right, end_right, eps, std::ref(answer1_right), std::ref(counter1_right)},
                th2_left {method2, start_left, end_left, eps,   std::ref(answer2_left),  std::ref(counter2_left)},
                th2_right{method2, start_right, end_right, eps, std::ref(answer2_right), std::ref(counter2_right)};

    cout.precision (20);
    
    th1_left.join();
    cout << "Method 1: xE (" << start_left  << ", " << end_left  << ").\tОтвет: " << answer1_left  << ".\tИтераций: " << counter1_left  << "\n";
    
    th2_left.join();
    cout << "Method 2: xE (" << start_left  << ", " << end_left  << ").\tОтвет: " << answer2_left  << ".\tИтераций: " << counter2_left  << "\n";
    
    th1_right.join();
    cout << "Method 1: xE (" << start_right << ", " << end_right << ").\t\tОтвет: " << answer1_right << ".\tИтераций: " << counter1_right << "\n";
    
    th2_right.join();
    cout << "Method 2: xE (" << start_right << ", " << end_right << ").\t\tОтвет: " << answer2_right << ".\tИтераций: " << counter2_right << endl;

    return 0;
}
