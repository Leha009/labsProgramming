#include <stdio.h>
#include <locale.h>
#include <malloc.h>

int Menu();                                             //Меню
void InputData(int*, int*, int*);                       //Ввод: &mlimit,&n,&m
int** InputArray(int, int);                             //Создание исходного: rows, cols
void ShowInput(int**, int, int, int);                   //Показ исходного: a, mlimit, rows, cols
int** ResultArray(int**, int, int, int, int**);         //Результ. массив: a, mlimit, rows, cols, bcols
void ShowResult(int**, int, int, int*);                 //Показ результата: b, rows, cols, bcols

int main()
{
	setlocale(LC_ALL, "russian");
	int	**a = NULL,                     //Указатель на вектор указателей на строки исходного массива
		**b = NULL,                     //Указатель на вектор указателей на строки результирующего массива
		mlimit,                         //Предел произведения чисел в строке массива
		cols,                           //Количество столбцов исходного массива
		rows,                           //Количество строк исходного и результирующего массивов
		*bcols = NULL,                  //Указатель на строку флагов для столбцов результирующего массива
		available,                      //Количество доступных пунктов
		select;                         //Выбранный пункт меню
    available = 1;
    do
    {
        select = Menu();
        switch(select)
        {
            case 1:
                InputData(&mlimit, &rows, &cols);
                available = 2;
                break;
            case 2:
                if(available > 1)
                {
                    a = InputArray(rows, cols);
                    available = 3;
                }
                else
                {
                    puts("Сначала введите данные в 1-ом пункте меню!");
                    system("pause");
                }
                break;
            case 3:
                if(available > 2) ShowInput(a, mlimit, rows, cols);
                else
                {
                    puts("Сначала введите данные во 2-ом пункте меню!");
                    system("pause");
                }
                break;
            case 4:
                if(available > 2)
                {
                    b = ResultArray(a, mlimit, rows, cols, &bcols);
                    available = 4;
                }
                else
                {
                    puts("Сначала введите данные во 2-ом пункте меню!");
                    system("pause");
                }
                break;
            case 5:
                if(available > 3) ShowResult(b, rows, cols, bcols);
                else
                {
                    puts("Сначала введите данные в 4-ом пункте меню!");
                    system("pause");
                }
                break;
            case 0:
                break;
            default:
                puts("Выбран неверный пункт меню!");
                system("pause");
        }
    } while(select != 0);
    if(bcols != NULL) free(bcols);
    if(a != NULL)
    {
        for(int i = 0; i < rows; i++) free(*(a+i));
        free(a);
    }
    if(b != NULL)
    {
        for(int i = 0; i < rows; i++) free(*(b+i));
        free(b);
    }
    return 0;
}

int Menu()
{
    int selected;   //Выбранный пункт меню
    system("cls");
    puts("*****************МЕНЮ*****************");
    puts("1 - Ввод предела произведения и размера массива");
    puts("2 - Ввод массива");
    puts("3 - Контрольный вывод данных");
    puts("4 - Обработка данных");
    puts("5 - Вывод результата");
    puts("0 - Выход");
    puts("Выберите пункт меню");
    scanf("%d", &selected);
    fflush(stdin);
    return selected;
}

void InputData(int *mlimit, int *rows, int *cols)                   //Ввод: mlimit,rows,cols
{
    system("cls");
    printf("Введите предел произведения в строке: ");
    scanf("%d", mlimit);
    fflush(stdin);
    printf("Введите размер массива(строки, столбцы): ");
    scanf("%d %d", rows, cols);
    fflush(stdin);
    system("pause");
}

int** InputArray(int rows, int cols)                       //Создание исходного: rows, cols
{
    system("cls");
    int** Array = NULL;
    int   i,
          j;
    Array = (int**)malloc(rows*sizeof(int*));
    if(Array != NULL)
    {
        for(i = 0; i < rows; i++)
        {
            *(Array+i) = (int*)malloc(cols*sizeof(int));
            if(*(Array+i) != NULL)
            {
                printf("Введите %d строку(в строке %d элементов): ", i, cols);
                for(j = 0; j < cols; j++) scanf("%d", &Array[i][j]);
                fflush(stdin);
            }
        }
    }
    else puts("Ошибка: недостаточно памяти!");
    system("pause");
    return Array;
}

void ShowInput(int **a, int mlimit, int rows, int cols)               //Показ исходного: a, mlimit, rows, cols
{
    int i,
        j;
    system("cls");
    printf("Было введено:\nПредел произведения в строке: %d\nРазмер массива: %dx%d\nМассив:\n", mlimit, rows, cols);
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++) printf("%d ", a[i][j]);
        puts("");
    }
    system("pause");
}

int** ResultArray(int **a, int mlimit, int rows, int cols, int **bcols)          //Результ. массив: a, mlimit, rows, cols, &bcols
{
    system("cls");
    int **result = NULL;
    int sum,        //Сумма столбца
        mult,       //Произв. в строке
        min,        //MinElement
        i,
        j,
        *rescols = NULL;
    rescols = calloc(cols, sizeof(int));
    result = (int**)malloc(rows*sizeof(int*));
    if(result != NULL)
    {
        for(i = 0; i < rows; i++)
        {
            *(result+i) = (int*)malloc(cols*sizeof(int));
            if(*(result+i) != NULL)
            {
                mult = 1; min = a[i][0];
                for(j = 0; j < cols; j++)
                {
                    if(mult > mlimit) result[i][j] = min;
                    else
                    {
                        result[i][j] = a[i][j];
                        if(a[i][j] < min) min = a[i][j];
                    }
                    mult*=a[i][j];
                }
            }
        }
        for(j = 0; j < cols; j++)
        {
            sum = 0;
            for(i = 0; i < rows; i++)
            {
                sum+=result[i][j];
            }
            if(sum >= 0)
            {
                rescols[j] = 1;
            }
        }
        puts("Обработка прошла успешно!");
    }
    else puts("Ошибка обработки: недостаточно памяти!");
    *bcols = rescols;
    system("pause");
    return result;
}

void ShowResult(int **result, int rows, int cols, int *bcols)                   //Показ результата: b, brows, cols, bcols
{
    system("cls");
    int f;  //Флаг отображения столбца
    f = 0;
    puts("Результирующий массив");
    if(result != NULL && bcols != NULL)
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                if(bcols[j] == 1)
                {
                    printf("%d ", result[i][j]);
                    f++;
                }
            }
            if(f) puts("");
        }
    }
    if(!f) puts("Ни один столбец массива не удовлетворяет условию");
    system("pause");
}
