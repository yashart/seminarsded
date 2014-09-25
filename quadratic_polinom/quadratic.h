//{========================================================================
//solves quadratic equation ax^2 + bx + c = 0 .
//@param events             events is type of equation for message function
//@param POLINOM_DEGREE     it is a degree of polinom (Now i can solve only linear and quadratic equation).
//
//@param[out] radicals      radicals is struct, which has radicals
//
//https://github.com/yashart/Intel_i-lab/tree/master/quadratic_polinom
//yashart@mail.ru
//Yashukhin Artem 413 group, 2014
//}========================================================================


#ifndef GLOBALCONSTANTS_H_INCLUDED
#define GLOBALCONSTANTS_H_INCLUDED

enum events { ALL_NUMBERS, NO_RADICALS, ONE_RADICAL, TWO_RADICALS, TWO_RADICALS_2};


const int POLINOM_DEGREE = 2;

struct radicals
{
    double x1,x2;
};
//{========================================================================
//  It is construction for radicals struct.(like as class)
//}========================================================================
void radicals_construction(struct radicals* r)
{
    r->x1 = NAN;
    r->x2 = NAN;
}
//{========================================================================
//  @param coefficints*     array of polinom coefficients
//  @return                 discriminant
//}========================================================================
double discrim_counting(double* coefficients)
{
    return coefficients[1] * coefficients[1] - 4 * coefficients[0] * coefficients[2];
}
//{========================================================================
//  @param      coefficints*     array of polinom coefficients
//  @param      events
//  @param      radicals
//  @return     radicals
//  @warning    radicals will be changed
//}========================================================================
radicals radicals_counting(events event, double* coefficients, radicals* r)
{
    if(event == ONE_RADICAL)
    {
        r->x1 = -coefficients[2] / coefficients[1];
    }

    if(event == TWO_RADICALS)
    {
        r->x1 = (-coefficients[1] - sqrt(discrim_counting(coefficients)) )/ 2/coefficients[0];
        r->x2 = (-coefficients[1] + sqrt(discrim_counting(coefficients)) )/ 2/coefficients[0];
    }

    return *r;
}

//{========================================================================
//  Print answer.
//  @param  events
//  @param  radicals
//}========================================================================
void message (events event, radicals r)
{
    if( event == ALL_NUMBERS)
        printf( "Any number is radical");

    if( event == NO_RADICALS)
        printf( "No radicals");

    if( event == ONE_RADICAL)
        printf( "One radical %lg", r.x1);

    if( event == TWO_RADICALS)
        printf( "Two radicals %lg и %lg", r.x1, r.x2);
}
//{========================================================================
//  Check coefficients and calling message with event argument
//  @param  coefficients
//  @param  radicals
//}========================================================================
void logic(double* coefficients, radicals* r)
{
    double discrim = NAN;

    if(POLINOM_DEGREE == 2)
    {
        if( coefficients[0] == 0)
        {
            if( coefficients[1] == 0)
            {
                if( coefficients[2] == 0)
                {
                    message (ALL_NUMBERS, *r);
                }
                else
                {
                    message (NO_RADICALS, *r);
                }
            }
            else
            {

                message (ONE_RADICAL, radicals_counting(ONE_RADICAL, coefficients, r));
            }
        }
        else
        {
            discrim = discrim_counting(coefficients);
            if( discrim < 0)
            {
                message (NO_RADICALS, *r);
            }
            else
            {

                if( discrim == 0)
                {
                    message (ONE_RADICAL, radicals_counting (TWO_RADICALS, coefficients, r));
                }
                else
                {
                    message (TWO_RADICALS, radicals_counting (TWO_RADICALS, coefficients, r));
                }
            }
        }


    }
}
//{========================================================================
//  Read arguments
//  @param  coefficiens
//  @param[out]  coefficiens
//}========================================================================
void scan(double* coefficients)
{
    double right_scan = NAN;
    for(int i = 0; i < POLINOM_DEGREE+1; i++)
    {
        printf( "Write the %d-st polinomal coefficients of %d polinom by a space \n",i+1 ,POLINOM_DEGREE + 1);

        right_scan = scanf("%lg[0-9]", &coefficients[i]);
        fflush(stdin);
        while(getchar() != 10);
        if(right_scan == 0)
        {
            i--;

        }

        right_scan = NAN;
    }


}

#endif // GLOBALCONSTANTS_H_INCLUDED
