#include <stdio.h>
#include <limits.h>
#include <locale.h>

#define MAX_SIZE1 3
#define MAX_SIZE2 3

int main()
{
    setlocale(LC_ALL, "russian");
    int a[MAX_SIZE1][MAX_SIZE2],
    mlimit, //������ ������������ ����� � ������ �������
    mult, //������������ ����� � ������ �������
    min, //����������� ����� � ������ �������
    column[MAX_SIZE2], //���� ��� �������, ���������������� �������
    sum, //����� ����� ������� �������
    repeat, //���� ���������� ������ ���������
    rm;
    repeat = 1;
    while(repeat)
    {
        sum = 0; rm = 0;
        for(int i = 0; i < MAX_SIZE2; i++) column[i] = 0;
        puts("������� ����� - ������ ������������ ����� � ������ �������");
        scanf("%d", &mlimit);
        printf("��������� ������� �������� ������� �������� �������: %d ������: %d\n", MAX_SIZE1, MAX_SIZE2);
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
        puts("�������� ������:");
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
            puts("�������������� ������:");
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
        else puts("�� ���� ������� ������� �� ������������� �������");
        puts("������� ����� ����� �����, �� ������ ����, ����� ��������� ���������");
        scanf("%d", &repeat);
        puts("**************************************************************************");
    }
    return 0;
}
