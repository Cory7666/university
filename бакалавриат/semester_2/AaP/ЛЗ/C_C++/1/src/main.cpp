#include <iostream>
#include <cmath>

using namespace std;

int main ()
{
  const float p = 3.14;
  float a, b, x;
  cout << "Введите a, b, x: "; cin >> a >> b >> x;
  cout << ( (x <= a) ? ( sqrt(1.414 - pow(x, 3.5) * sin(pow(x, 2.2)) ) + log(x) ): ( (x < b) ? ( 2 * exp(3.14 * x) * sin(2.1 * x - p / 5) ): ( abs( pow(x, 5.1) * cosh(x) -1.4 ) * atan(pow(x, 2.6)) ) ) ) << endl;
  return 0;
}
