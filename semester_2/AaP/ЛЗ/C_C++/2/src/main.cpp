#include <iostream>
#include <iomanip>
#include <cmath>

#define PI 3.14

using namespace std;

int main ()
{
    long double a, b, x, z, xb, xe, dx;
	
	cout << " (!) Внимание (!) " << endl
		 << "Если значение функции невычисляемо, в ячейке будет отображено число 666.666 ." << endl;
    cout << "Введите значение a:     "; cin >> a;
    cout << "Введите значение b:     "; cin >> b;
    cout << "Введите значение x_нач: "; cin >> xb;
    cout << "Введите значение x_кон: "; cin >> xe;
    cout << "Введите значение dx:    "; cin >> dx;

    x = xb;

    if (x <= xe)
    {
        cout << endl << "+-----------------+----------------------------------+"
             << endl << "|   Значение X    |           z ( X ) = ...          |"
             << endl << "+-----------------+----------------------------------+";

        while (x <= xe)
        {
            if (x <= a)
            {
                z = ((pow(x, 3.5) * sin( pow(x, 2.2) ) <= 1.414) && x > 0) ? (sqrt( 1.414 - pow(x, 3.5) * sin( pow(x, 2.2) ) ) + log(x)) : 666.666;
            }
            else if (x < b)
            {
                z = 2 * exp(3.14 * x) * sin( 2.1 * x - PI / 5 );
            }
            else
            {
                z = (x >= 0) ? ( fabs( pow(x, 5.1) * cosh(x) - 1.4 ) * atan( pow(x, 2.6) ) ) : 666.666;
            }

            cout << endl << "| " << setw(15) << x << " | " << setw(32) << z << " |";

            x += dx;
        }

        printf("\n+-----------------+----------------------------------+");
    } else {
        printf("Начальное значение больше конечного.");
    }
    printf("\nПрограмма завершила свою работу....\n");
    
    return 0;
}