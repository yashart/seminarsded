#include <stdio.h>
#include <math.h>
#include "quadratic.h"


int main()
{
    double polinomal_coefficiens[POLINOM_DEGREE+1];
    radicals r;
    radicals_construction(&r);

    for (int i = 0; i < POLINOM_DEGREE + 1; i++ )
    {
        polinomal_coefficiens[i] = NAN;
    }

    scan(polinomal_coefficiens);
    logic(polinomal_coefficiens, &r);
    return 0;
}

