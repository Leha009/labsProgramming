#include <stdio.h>
#include <limits.h>
#include <locale.h>

#define MAX_SIZE1 3
#define MAX_SIZE2 3

int main()
{
    setlocale(LC_ALL, "russian");
    int a[MAX_SIZE1][MAX_SIZE2],
    mlimit, //Предел произведения чисел в строке массива
    mult, //Произведение чисел в строке массива
    min, //Минимальное число в строке массива
    column[MAX_SIZE2], //Флаг для столбца, удовлетворяющего условию
    sum, //Сумма чисел столбца массива
    repeat, //Флаг повторения работы программы
    rm;
    repeat = 1;
    while(repeat)
    {
        sum = 0; rm = 0;
        for(int i = 0; i < MAX_SIZE2; i++) column[i] = 0;
        puts("Введите число - предел произведения чисел в строке массива");
        scanf("%d", &mlimit);
        printf("Построчно введите элементы массива размером столбцы: %d строки: %d\n", MAX_SIZE1, MAX_SIZE2);
        for(int i = 0; i < MAX_SIZE1; i++)
        {
            mult = 1; min = INT_MAX;
            for(int j = 0; j < MAX_SIZE2; j++)
            {
                scanf("%d", &a[i][j]);
                if(j == 0 && mlimit < mult) min = a[i][j];
                if(mult > mlimit) a[i][j] = min;
                if(a[i][j] < min) min = a[i][j];
                mult *= a[i][j];
            }
        }
        puts("Исходный массив:");
        for(int i = 0; i < MAX_SIZE1; i++)
        {
            for(int j = 0; j < MAX_SIZE2; j++) printf("%d ", a[i][j]);
            puts("");
        }
        for(int j = 0; j < MAX_SIZE2; j++)
        {
            sum = 0;
            for(int i = 0; i < MAX_SIZE1; i++)
            {
                sum+=a[i][j];
            }
            if(sum >= 0)
            {
                column[j] = 1;
                rm++;
            }
        }
        if(rm)
        {
            puts("Результирующий массив:");
            for(int i = 0; i < MAX_SIZE1; i++)
            {
                for(int j = 0; j < MAX_SIZE2; j++)
                {
                    if(column[j])
                    {
                        printf("%d ", a[i][j]);
                    }
                    if(j == MAX_SIZE2 - 1) puts("");
                }
            }
        }
        else puts("Ни один столбец массива не удовлетворяет условию");
        puts("Введите любое целое число, не равное нулю, чтобы повторить программу");
        scanf("%d", &repeat);
        puts("**************************************************************************");
    }
    return 0;
}
