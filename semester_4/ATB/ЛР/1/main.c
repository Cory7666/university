#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long double num_t;

static num_t
f (num_t n)
{ return powl (sqrtl (n / 8), sqrtl (n / 8)); }

static num_t
g (num_t n)
{ return powl (n, logl (logl (n))); }

int main(void)
{
    num_t 
        F_n = 0.0, G_n = 0.0,
        ATG_FG = 0.0, ATG_GF = 0.0,
        π = 0.0,
        n_begin = 0.0, n_end = 0.0, n_step = 0.0, n = 0.0,
        φ = 0.0, k = 0.0, Δ = 0.0, Θ = 0.0, O = 0.0;
    FILE
        *output = stdout,
        *file_results = fopen ("coords.results.out", "w"),
        *file_n_fn = fopen ("coords.n_fn.out", "w"),
        *file_n_gn = fopen ("coords.n_gn.out", "w");
    
    printf ("Введите Начало диапазона:\t"); scanf ("%Lf", &n_begin);
    printf ("Введите Конец диапазона:\t"); scanf ("%Lf", &n_end);
    printf ("Введите Шаг значений:   \t"); scanf ("%Lf", &n_step);
    printf ("Введите Коэффициент кратности:\t"); scanf ("%Lf", &k);

    φ = M_PI / k;
    
    for (n = n_begin; n <= n_end; n += n_step)
    {
        F_n = f(n); G_n = g(n);
        π = (ATG_FG = atanl (F_n / G_n)) - (ATG_GF = atanl (G_n / F_n));
        
        Δ = φ - π;
        Θ = fabsl (π) - φ;
        O = π + φ;
        
        /*
        fprintf (output, "%LF %LF %LF %LF %LF %LF %LF %LF %LF\n",
            n, F_n, G_n, ATG_FG, ATG_GF, π, Δ, Θ, O
        );
        */

        fprintf (output, "%Lf %Lf %Lf\n", n, φ, fabsl(π));

        fprintf (file_results, "%LF %LF %LF %LF %LF %LF %LF %LF %LF\n",
            n, F_n, G_n, ATG_FG, ATG_GF, π, Δ, Θ, O
        );
        fprintf (file_n_fn, "%Lf %Lf\n", n, F_n);
        fprintf (file_n_gn, "%Lf %Lf\n", n, G_n);
    }
}
