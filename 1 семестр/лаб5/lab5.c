#include <stdio.h>
#include <locale.h>
#include <malloc.h>

int Menu();                                             //����
void InputData(int*, int*, int*);                       //����: &mlimit,&n,&m
int** InputArray(int, int);                             //�������� ���������: rows, cols
void ShowInput(int**, int, int, int);                   //����� ���������: a, mlimit, rows, cols
int** ResultArray(int**, int, int, int, int**);         //�������. ������: a, mlimit, rows, cols, bcols
void ShowResult(int**, int, int, int*);                 //����� ����������: b, rows, cols, bcols

int main()
{
	setlocale(LC_ALL, "russian");
	int	**a = NULL,                     //��������� �� ������ ���������� �� ������ ��������� �������
		**b = NULL,                     //��������� �� ������ ���������� �� ������ ��������������� �������
		mlimit,                         //������ ������������ ����� � ������ �������
		cols,                           //���������� �������� ��������� �������
		rows,                           //���������� ����� ��������� � ��������������� ��������
		*bcols = NULL,                  //��������� �� ������ ������ ��� �������� ��������������� �������
		available,                      //���������� ��������� �������
		select;                         //��������� ����� ����
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
                    puts("������� ������� ������ � 1-�� ������ ����!");
                    system("pause");
                }
                break;
            case 3:
                if(available > 2) ShowInput(a, mlimit, rows, cols);
                else
                {
                    puts("������� ������� ������ �� 2-�� ������ ����!");
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
                    puts("������� ������� ������ �� 2-�� ������ ����!");
                    system("pause");
                }
                break;
            case 5:
                if(available > 3) ShowResult(b, rows, cols, bcols);
                else
                {
                    puts("������� ������� ������ � 4-�� ������ ����!");
                    system("pause");
                }
                break;
            case 0:
                break;
            default:
                puts("������ �������� ����� ����!");
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
    int selected;   //��������� ����� ����
    system("cls");
    puts("*****************����*****************");
    puts("1 - ���� ������� ������������ � ������� �������");
    puts("2 - ���� �������");
    puts("3 - ����������� ����� ������");
    puts("4 - ��������� ������");
    puts("5 - ����� ����������");
    puts("0 - �����");
    puts("�������� ����� ����");
    scanf("%d", &selected);
    fflush(stdin);
    return selected;
}

void InputData(int *mlimit, int *rows, int *cols)                   //����: mlimit,rows,cols
{
    system("cls");
    printf("������� ������ ������������ � ������: ");
    scanf("%d", mlimit);
    fflush(stdin);
    printf("������� ������ �������(������, �������): ");
    scanf("%d %d", rows, cols);
    fflush(stdin);
    system("pause");
}

int** InputArray(int rows, int cols)                       //�������� ���������: rows, cols
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
                printf("������� %d ������(� ������ %d ���������): ", i, cols);
                for(j = 0; j < cols; j++) scanf("%d", &Array[i][j]);
                fflush(stdin);
            }
        }
    }
    else puts("������: ������������ ������!");
    system("pause");
    return Array;
}

void ShowInput(int **a, int mlimit, int rows, int cols)               //����� ���������: a, mlimit, rows, cols
{
    int i,
        j;
    system("cls");
    printf("���� �������:\n������ ������������ � ������: %d\n������ �������: %dx%d\n������:\n", mlimit, rows, cols);
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++) printf("%d ", a[i][j]);
        puts("");
    }
    system("pause");
}

int** ResultArray(int **a, int mlimit, int rows, int cols, int **bcols)          //�������. ������: a, mlimit, rows, cols, &bcols
{
    system("cls");
    int **result = NULL;
    int sum,        //����� �������
        mult,       //������. � ������
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
        puts("��������� ������ �������!");
    }
    else puts("������ ���������: ������������ ������!");
    *bcols = rescols;
    system("pause");
    return result;
}

void ShowResult(int **result, int rows, int cols, int *bcols)                   //����� ����������: b, brows, cols, bcols
{
    system("cls");
    int f;  //���� ����������� �������
    f = 0;
    puts("�������������� ������");
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
    if(!f) puts("�� ���� ������� ������� �� ������������� �������");
    system("pause");
}
