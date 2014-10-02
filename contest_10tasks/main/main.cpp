//{=================================================================================
//!         @file    main.cpp
//!         @date    2014-10-2 2:06
//!         @author  Yashukhin Artem
//!
//!         10 tasks from acm.mipt.ru
//!
//}=================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>

enum system_calling{ERROR, OK};

//{=================================================================================
//! is_prime_number - check the number of the simplicity
//! @param numbers  - number for checking
//! @return 1 if number is prime, else return 0
//! @par          Examble:
//! @code
//!     is_prime_number(7);
//!     //return 1;
//!
//!     is_prime_number(12);
//!     //return 0;
//!
//! @endcode
//!
//}=================================================================================

bool is_prime_number(int numbers);

//{=================================================================================
//! print_array - print array on screen
//! @param array  - array with numbers
//! @param size   - size of array
//! @warning  array must be int type
//}=================================================================================

int search_Prime(bool* isPrime ,int quantity_numbers, int nth_number);

//{=================================================================================
//! taskC_var2() - Return nth easy number
//}=================================================================================

void print_array(int* array, int size);

//{=================================================================================
//! scan_array - scan array from keyboard
//! @param array  - array with numbers
//! @param size   - size of array
//! @warning  array must be int type
//}=================================================================================

system_calling scan_array(int *array, int size);

//{=================================================================================
//! taskA_var1  -  write program, which get prime numbers from a list of numbers
//}=================================================================================

system_calling taskA_var1();

//{=================================================================================
//! taskB_var1  -  write program, which check number on square divider
//}=================================================================================

system_calling taskB_var1();

//{=================================================================================
//! canWeight - check, can we weigh the item using weights at 1, 4, 4^2, ... cu
//! @return 1 if we can
//! @return 0 if we cann't
//}=================================================================================

bool canWeigh(int mg);

//{=================================================================================
//! taskC_var1 - print result canWeight
//! @see  canWeight
//}=================================================================================

system_calling taskC_var1();

//{=================================================================================
//! transpose - math transpose matrix
//! @param transpose_matrix - the inital matrix
//! @param size_arr - size of matrix
//! @param[out] transpose_matrix - the transpose matrix
//}=================================================================================

void transpose( int* transpose_matrix, int size_arr);

//{=================================================================================
//! scan matrix and print her transpose
//}=================================================================================

system_calling taskA_var2();

//{=================================================================================
//! taskB_var2 - program for the normalization of the root (sqrt(a) -> b * sqrt(c)
//}=================================================================================

system_calling taskB_var2();

//{=================================================================================
//! taskC_var2() - Find nth prime number
//}=================================================================================

system_calling taskC_var2();

//{=================================================================================
//! Greatest_common_divisor - search Greatest_common_divisor for 2 numbers
//}=================================================================================

int Greatest_common_divisor(int a, int b);

//{=================================================================================
//! taskA_var3 - search Greatest_common_divisor for 3 numbers
//}=================================================================================

system_calling taskA_var3();

//{=================================================================================
//! taskB_var4 - delete ' ' , changed numbers to '#', decreases register
//}=================================================================================

void taskB_var4();

//{=================================================================================
//! decomposition_by_dividing_on_two - representation of a number as a sum of powers of two
//}=================================================================================

int decomposition_by_dividing_on_two(int number, int degree);

//{================================================================================
//! taskA_var7 - scan number for decomposition_by_dividing_on_two and print result
//! @see decomposition_by_dividing_on_two
//}================================================================================

system_calling taskA_var7();

//{================================================================================
//! taskB_var7 - find the most remote points
//}================================================================================
system_calling taskB_var7();

int main()
{
    //taskA_var1();
    //taskB_var1();
    //taskC_var1();
    //taskA_var2();
    //taskB_var2();
    //taskC_var2();
    //taskA_var3();
    //taskB_var4();
    //taskA_var7();
    //taskB_var7();
}


system_calling taskA_var1()
{
    int size_array = 0;
    int scaning_number = 0;
    int quantity_numbers = 0;

    int *prime_numbers = NULL;
    assert(size_array >= 0);
    prime_numbers = (int*) calloc(size_array, sizeof(*prime_numbers));
    scanf("%d", &quantity_numbers);

    for (int i = 0; i < quantity_numbers; i++)
    {
        if( scanf("%d", &scaning_number) == 0)
        {
            printf("Error input");
            return ERROR;
        }
        if (is_prime_number(scaning_number))
        {
            size_array++;
            assert(   (0 <  size_array * sizeof(*prime_numbers) ) \
                    && (size_array * sizeof(*prime_numbers) <= quantity_numbers * sizeof(*prime_numbers) ) );
            prime_numbers = (int *) realloc((void*) prime_numbers, size_array * sizeof(*prime_numbers));
            prime_numbers[size_array - 1] = scaning_number;
        }
    }
    print_array(prime_numbers, size_array);
    free(prime_numbers);
    return OK;
}


void print_array(int* array, int size) {
    for (int i = 0; i< size; i++)
    {
        assert(i>=0 && i< size);
        printf("%d ", array[i]);
    }
}

bool is_prime_number(int numbers)
{
    double sqrt_number = sqrt(numbers);
    for (int i = 1; i <= sqrt_number; i++)
    {

        if(numbers % i == 0 && i != 1)
        {
            return 0;
        }
    }
    if(numbers != 1)
        return 1;
    return 0;
}


system_calling taskB_var1() {
    int number = 0;
    if(scanf("%d", &number) != 1)
    {
        printf("Error input");
        return ERROR;
    }

    for (int i = 2; (i * i) <= number; i++)
    {
        if (number % (i*i) == 0)
        {
            printf("YES");
            return OK;
        }
    }
    printf("NO");
    return OK;
}


bool canWeigh(int mg)
{
    if(mg     == 1)
    {
        return 1;
    }else if(mg < 4)
    {
        return 0;
    }
    if(mg % 4 == 2)
    {
        return 0;
    }
    else
    {
        canWeigh((int) (mg / 4 + (mg % 4 + 1) / 4));
    }
}
system_calling taskC_var1()
{

    int mg = 0;
    if(scanf("%d", &mg) != 1)
    {
        printf("Error input");
        return ERROR;
    }
    printf (canWeigh (mg)? "YES" : "NO");
    return OK;
}

system_calling scan_array(int *array, int size)
{
    for (int i = 0; i < size; i++)
        {
            if(scanf("%d", &array[i]) != 1)
            {
                printf("Input_error");
                return ERROR;
            }
        }
    return OK;
}


void transpose( int* transpose_matrix, int size_arr) {
    int buffer_for_swap = 0;
    int matrix_per_size = (int) sqrt(size_arr);
    for (int i = 0; i < matrix_per_size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            assert (matrix_per_size * i + j >= 0 && matrix_per_size * i + j < size_arr);
            buffer_for_swap = transpose_matrix[matrix_per_size * i + j];

            assert (matrix_per_size * j + i >= 0 && matrix_per_size * j + i < size_arr);
            transpose_matrix[matrix_per_size * i + j] = transpose_matrix[matrix_per_size * j + i];

            transpose_matrix[matrix_per_size * j + i] = buffer_for_swap;
        }
    }
}

system_calling taskA_var2()
{
    int matrix_per_size = 0;

    if(scanf("%d", &matrix_per_size) != 1)
    {
        printf("Error input");
        return ERROR;
    }

    int size_arr = matrix_per_size * matrix_per_size;

    assert(size_arr > 0);
    int* transpose_matrix = (int*) calloc(size_arr, sizeof(*transpose_matrix));

    if( scan_array(transpose_matrix, size_arr) == ERROR)
    {
        return ERROR;
    }

    printf("\n");

    transpose(transpose_matrix, size_arr);

    print_array (transpose_matrix, size_arr);

    free(transpose_matrix);

    return OK;
}

system_calling taskB_var2()
{
    int number_under_radical = 0;
    int initial_number_under_radical = 0;
    int number_outside_radical = 0;
    if(scanf("%d", &initial_number_under_radical) != 1)
    {
        printf("Input error");
        return ERROR;
    }

    for (int i = 1; (i * i) <= initial_number_under_radical; i++)
    {
        if (initial_number_under_radical % (i*i) == 0)
        {
            number_outside_radical = i;
            number_under_radical = initial_number_under_radical /i/i;
        }
    }
    printf("%d %d", number_under_radical, number_outside_radical);

    return OK;
}

int search_Prime(bool* isPrime ,int quantity_numbers, int nth_number) {
    for (int i = 2; i*i < quantity_numbers; i++){
        assert(i < quantity_numbers);
        if (!isPrime[i]){
            nth_number--;
            if(nth_number == 0)
            {
                return i;
            }
            for (int j = i * i; j < quantity_numbers; j += i){
                assert(j < quantity_numbers);
                isPrime[j] = true;
            }
        }
    }
}

system_calling taskC_var2()
{
    int quantity_numbers = 100500000;

    assert (quantity_numbers > 2);
    bool* isPrime = (bool*) calloc(quantity_numbers, sizeof(*isPrime));
    isPrime[1] = true;

    int nth_number = 0;
    if(scanf("%d", &nth_number) != 1)
    {
        printf("Input error");
        return ERROR;
    }

    printf("%d", search_Prime(isPrime, quantity_numbers, nth_number) );
    return OK;
}

system_calling taskA_var3()
{
    int a, b, c = 0;
    if(scanf("%d %d %d", &a, &b, &c) != 3)
    {
        printf("Input ERROR");
        return ERROR;
    }
    printf("%d", a*b*c/ Greatest_common_divisor(a * b / Greatest_common_divisor(a, b), c)/ Greatest_common_divisor(a, b));
    return OK;
}

int Greatest_common_divisor(int a, int b)
{
    while (a != 0 && b != 0){
        if (a > b){
            a = a % b;
        }
        else{
            b = b % a;
        }
    }
return a+b;
}

void taskB_var4()
{
    char symbol = 0;
    bool flag_correct_symbol = false;
    for(int i = 1; symbol != '\n'; i++)
    {
        scanf("%c", &symbol);
        if(symbol == ' ')
        {
            flag_correct_symbol = true;
        }else if(symbol != ' ' && flag_correct_symbol == true)
        {
            printf(" ");
            flag_correct_symbol = false;
        }
        symbol = tolower(symbol);
        if(symbol <= '9' && symbol >= '0')
        {
            symbol = '#';
        }
        if(symbol != ' ')
        {
            printf("%c", symbol);
        }
    }
}

int decomposition_by_dividing_on_two(int number, int degree)
{
    if(number == 1)
    {
        printf("%lg", pow(2, degree) );
        return 0;
    }
    if(number % 2 == 1)
    {
        printf("%lg ", pow(2, degree) );
    }
    degree++;
    decomposition_by_dividing_on_two(number / 2, degree);


}

system_calling taskA_var7()
{
    int number = 0;
    if(scanf("%d", &number) != 1)
    {
        printf("Input error");
        return ERROR;
    }
    decomposition_by_dividing_on_two(number, 0);
    return OK;
}

system_calling taskB_var7() {
    int quantity_points = 0;
    if(scanf("%d", &quantity_points)  != 1)
    {
        printf("Input ERROR");
        return ERROR;
    }
    assert(quantity_points > 0);
    double* x     = (double*) calloc (quantity_points, sizeof(*x));
    double* y     = (double*) calloc (quantity_points, sizeof(*y));

    double maxim = -1;
    int imax = -1;
    int jmax = -1;
    for (int i = 0; i < quantity_points; i++)
    {
        if(scanf("%lg %lg", &x[i], &y[i]))
        {
            printf("Input ERROR");
            return ERROR;
        }
    }
    for (int i = quantity_points - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if(maxim < ((x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j])) )
            {
                maxim = (x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]);
                imax = i;
                jmax = j;
            }
        }
    }
    printf("%d %d %lg",imax+1, jmax+1, sqrt(maxim));
    return OK;
}
