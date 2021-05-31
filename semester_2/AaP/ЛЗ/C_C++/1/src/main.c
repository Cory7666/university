#include <stdio.h>
#include <math.h>
#include <ncurses.h>

#define PI 3.14

int main ()
{
  float a, b, x, z;

  printf("\nНачало работы программы...");
  printf("\nВведите значения переменных - a, b, x: ");
  scanf("%f %f %f", &a, &b, &x);

  if (x <= a)
  {
    printf("Выбрана первая ветка выполнения программы...");
    z = sqrt( 1.414 - pow(x, 3.5) * sin( pow(x, 2.2) ) ) + log(x);
  }
  else if (x < b)
  {
    printf("Выбрана вторая ветка выполнения программы...");
    z = 2 * exp(3.14 * x) * sin( 2.1 * x - PI / 5 );
  }
  else
  {
    printf("Выбрана третья ветка выполнения программы...");
    z = fabs( pow(x, 5.1) * cosh(x) - 1.4 ) * atan( pow(x, 2.6) );
  }

  printf("\nОтвет: %f.\n\n", z);

  return 0;
}