#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>

int easy_num(int numbers);
void taskA_var1();

void taskB_var1();

int weigh(int mg);
void taskC_var1();

void taskA_var2();

void taskB_var2();

void taskC_var2();

int nod(int a, int b);
void taskA_var3();

void taskB_var3();

int raz(int N, int i);
void taskA_var7();

void taskB_var7();

int main()
{
    //taskA_var1();
    //taskB_var1();
    //taskC_var1();
    //taskA_var2();
    //taskB_var2();
    //taskC_var2();
    //taskA_var3();
    //taskB_var3();
    //taskA_var7();
    taskB_var7();
}


void taskA_var1()
{
    int n, numbers, size_arr = 0;
    int *easyn = NULL;
    easyn = (int*) calloc(size_arr, sizeof(*easyn));
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &numbers);
        if (easy_num (numbers))
        {
            size_arr++;
            easyn = (int *) realloc((void*) easyn, size_arr);
            easyn[size_arr - 1] = numbers;
        }
    }
    for (int i = 0; i< size_arr; i++)
    {
        assert(i>=0 && i< size_arr);
        printf("%d ", easyn[i]);
    }

    free(easyn);
}
int easy_num(int numbers)
{
    for (int i = 1; i <=(int) sqrt(numbers) + 1; i++)
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

void taskB_var1()
{
    int number = 0;
    scanf("%d", &number);

    for (int i = 2; (i * i) <= ((int) sqrt(number) + 1); i++)
    {
        if (number % (i*i) == 0)
        {
            printf("YES");
            break;
        }
        else
        {
            printf("NO");
            break;
        }
    }
}

int weigh(int mg)
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
        weigh( (int) (mg / 4 + (mg % 4 + 1) / 4) );
    }
}
void taskC_var1()
{

    int mg = 0;
    scanf("%d", &mg);
    if(weigh(mg))
    {
        printf("YES");
    }else
    {
        printf("NO");
    }

}

void taskA_var2()
{
    int* transpon = NULL;
    int n = 0;
    int tmp = 0;

    scanf("%d", &n);

    int size_arr = n*n;
    transpon = (int*) calloc(size_arr, sizeof(*transpon));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &transpon[n * i + j]);
        }
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            assert (n * i + j >= 0 && n * i + j < size_arr);
            tmp = transpon[n * i + j];

            assert (n * j + i >= 0 && n * j + i < size_arr);
            transpon[n * i + j] = transpon [n * j + i];

            transpon[n * j + i] = tmp;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            assert (n * i + j >= 0 && n * i + j < size_arr);

            printf("%d ", transpon[n * i + j]);
        }
        printf("\n");
    }

    free(transpon);
}

void taskB_var2()
{
    int number, sqrt_int, sqrt_float = 0;
    scanf("%d", &number);
    for (int i = 1; (i * i) <= number; i++)
    {
        if (number % (i*i) == 0)
        {
            sqrt_int = i;
            sqrt_float = number /i/i;
        }
    }
    printf("%d %d",sqrt_float, sqrt_int);

}

void taskC_var2()
{
    int N = 100500000;
    bool* isPrime = (bool*) calloc(N, sizeof(*isPrime));
    isPrime[1] = true;

    int numbers = 0;
    scanf("%d", &numbers);
for (int i = 2; i*i < N; i++){
    assert(i < N);
   if (!isPrime[i]){
        numbers--;
        if(numbers == 0)
        {
            printf("%d", i);
        }
      for (int j = i * i; j < N; j += i){
        assert(j < N);
         isPrime[j] = true;
      }
    }
}
}

void taskA_var3()
{
    int a, b, c = 0;
    scanf("%d %d %d", &a, &b, &c);
    printf("%d", a*b*c/nod(a*b/nod(a, b),c)/nod(a,b));
}
int nod(int a, int b)
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

void taskB_var3()
{
    char c = 0;
    int i = 0;
    bool flag = false;
    for(i = 1; c != '\n'; i++)
    {
        scanf("%c", &c);
        if(c == ' ')
        {
            flag = true;
        }else if(c != ' ' && flag == true)
        {
            printf(" ");
            flag = false;
        }
        c = tolower(c);
        if(c <= '9' && c >= '0')
        {
            c = '#';
        }
        if(c != ' ')
        {
            printf("%c", c);
        }
    }
}

int raz(int N, int i)
{
    if(N == 1)
    {
        printf("%lg", pow(2, i) );
        return 0;
    }
    if(N % 2 == 1)
    {
        printf("%lg ", pow(2, i) );
    }
    i++;
    raz(N/2, i);


}
void taskA_var7()
{
    int N = 0;
    scanf("%d", &N);
    raz(N, 0);

}

void taskB_var7()
{
    int N = 0;
    scanf("%d", &N);
    double* x     = (double*) calloc (N, sizeof(*x));
    double* y     = (double*) calloc (N, sizeof(*y));
    double maxim = -1;
    int imax, jmax = -1;
    for (int i = 0; i < N; i++)
    {
        scanf("%lg %lg", &x[i], &y[i]);
    }
    for (int i = N - 1; i >= 0; i--)
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
}
