#include <stdio.h>
#include <limits.h>
#include <locale.h>
#include <malloc.h>

int main()
{
    setlocale(LC_ALL, "russian");
    int **a,                    //Исходный массив
        **b,                    //Результирующий массив
        mlimit,                 //Предел произведения чисел в строке массива
        mult,                   //Произведение чисел в строке массива
        min,                    //Минимальное число в строке массива
        sum,                    //Сумма чисел столбца массива
        repeat,                 //Флаг повторения работы программы
        m,                      //Количество столбцов исходного массива
        n,                      //Количество строк массива
        k,                      //Количество столбцов результирующего массива
        i,                      //Индекс строки массива
        j,                      //Индекс столбца массива
        c,                      //Счетчик для цикла с выделением памяти
        f;                      //Флаг для цикла выделения памяти
    do
    {
        puts("Введите число - предел произведения чисел в строке массива");
        scanf("%d", &mlimit);
        printf("Введите размера массива. Сначала количество столбцов, далее - строк.\n");
        do
        {
            scanf("%d %d", &m, &n);
            if(m < 1 || n < 1)
                printf("Размер массива должен быть минимум 1х1\n");
        } while(m < 1 || n < 1);
        a = (int**)malloc(n*sizeof(int*));
        b = (int**)malloc(n*sizeof(int*));
        if(a != NULL && b != NULL)
        {
            f = 1;
            for(i = 0, c = 0; i < n && f; i++, c++)
            {
                a[i] = (int*)malloc(m*sizeof(int));
                b[i] = (int*)malloc(m*sizeof(int));
                if(a[i] == NULL || b[i] == NULL)
                    f = 0;
            }
            if(c != n)
            {
                for(i = 0; i < c; i++)
                {
                    if(a[i] != NULL) free(a[i]);
                    if(b[i] != NULL) free(b[i]);
                }
                free(a);
                free(b);
                puts("Не удалось выделить память для требуемого массива. Попробуйте еще раз, уменьшив значения");
            }
            else
            {
                printf("Построчно введите элементы массива размером столбцы: %d строки: %d\n", m, n);
                for(i = 0; i < n; i++)
                    for(j = 0; j < m; j++)
                        scanf("%d", &a[i][j]);
                        /*if(j == 0)
                        {
                            min = a[i][j];
                            mult = a[i][j];
                        }
                        if(mult > mlimit) a[i][j] = min;
                        if(a[i][j] < min) min = a[i][j];
                        if(j && mult <= mlimit) mult *= a[i][j];*/
                puts("Исходный массив:");
                for(i = 0; i < n; i++)
                {
                    for(j = 0; j < m; j++) printf("%d ", a[i][j]);
                    puts("");
                }
                //puts("Измененный исходный массив:");
                for(i = 0; i < n; i++)
                {
                    for(j = 0; j < m; j++)
                    {
                        if(j == 0)
                        {
                            min = a[i][j];
                            mult = a[i][j];
                        }
                        if(mult > mlimit) a[i][j] = min;
                        if(a[i][j] < min) min = a[i][j];
                        if(j && mult <= mlimit) mult *= a[i][j];
                        //printf("%d ", a[i][j]);
                    }
                    //puts("");
                }
                k = 0; sum = 0;
                for(j = 0; j < m; j++)
                {
                    sum = 0;
                    for(i = 0; i < n; i++) sum += a[i][j];
                    if(sum >= 0)
                    {
                        for(i = 0; i < n; i++) b[i][k] = a[i][j];
                        k++;
                    }
                }
                if(k > 0)
                {
                    puts("Результирующий массив:");
                    for(i = 0; i < n; i++)
                    {
                        for(j = 0; j < k; j++) printf("%d ", b[i][j]);
                        puts(" ");
                    }
                }
                else puts("Ни один столбец массива не удовлетворяет условию");
                for(i = 0; i < n; i++)
                {
                    free(a[i]);
                    free(b[i]);
                }
                free(a);
                free(b);
                a = NULL;
                b = NULL;
            }
        } else puts("Не удалось выделить память для требуемого массива. Попробуйте еще раз, уменьшив значения");
        puts("Введите любое целое число, не равное нулю, чтобы повторить программу");
        scanf("%d", &repeat);
        puts("**************************************************************************");
    } while(repeat);
    return 0;
}
