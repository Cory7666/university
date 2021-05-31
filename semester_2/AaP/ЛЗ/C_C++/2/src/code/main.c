#include <stdio.h>
#include <math.h>
#define PI 3.14
int main ()
{
	float a, b, x, z, xb, xe, dx;
	printf(" (!) Warning (!) \n");
	printf("If the function value is not calculated, the cell will display a number 666.666 .\n");
    printf("Enter a:     "); scanf("%f", &a);
    printf("Enter b:     "); scanf("%f", &b);
    printf("Enter x_beg: "); scanf("%f", &xb);
    printf("Enter x_end: "); scanf("%f", &xe);
    printf("Enter dx:    "); scanf("%f", &dx);
	x = xb - dx;
	if (xb <= xe) { for (printf("\n+-----------------+----------------------------------+\n|   Value of X    |           z ( X ) = ...          |\n+-----------------+----------------------------------+"); x <= xe && (z = (x <= a) ? ( ((pow(x, 3.5) * sin( pow(x, 2.2) ) <= 1.414) && x > 0) ? (sqrt( 1.414 - pow(x, 3.5) * sin( pow(x, 2.2) ) ) + log(x)) : 666.666 ) : ( (x < b) ? (2 * exp(3.14 * x) * sin( 2.1 * x - PI / 5 )) : (fabs( pow(x, 5.1) * cosh(x) - 1.4 ) * atan( pow(x, 2.6) )) )); x += dx, printf("\n| %15f | %32f |", x, z) );
	printf("\n+-----------------+----------------------------------+\n\n"); } else { printf("Too big.\n"); }
}
