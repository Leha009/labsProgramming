#include <stdio.h>
#include <limits.h>
#include <locale.h>
#include <malloc.h>

int main()
{
    setlocale(LC_ALL, "russian");
    int **a,                    //�������� ������
        **b,                    //�������������� ������
        mlimit,                 //������ ������������ ����� � ������ �������
        mult,                   //������������ ����� � ������ �������
        min,                    //����������� ����� � ������ �������
        sum,                    //����� ����� ������� �������
        repeat,                 //���� ���������� ������ ���������
        m,                      //���������� �������� ��������� �������
        n,                      //���������� ����� �������
        k,                      //���������� �������� ��������������� �������
        i,                      //������ ������ �������
        j,                      //������ ������� �������
        c,                      //������� ��� ����� � ���������� ������
        f;                      //���� ��� ����� ��������� ������
    do
    {
        puts("������� ����� - ������ ������������ ����� � ������ �������");
        scanf("%d", &mlimit);
        printf("������� ������� �������. ������� ���������� ��������, ����� - �����.\n");
        do
        {
            scanf("%d %d", &m, &n);
            if(m < 1 || n < 1)
                printf("������ ������� ������ ���� ������� 1�1\n");
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
                puts("�� ������� �������� ������ ��� ���������� �������. ���������� ��� ���, �������� ��������");
            }
            else
            {
                printf("��������� ������� �������� ������� �������� �������: %d ������: %d\n", m, n);
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
                puts("�������� ������:");
                for(i = 0; i < n; i++)
                {
                    for(j = 0; j < m; j++) printf("%d ", a[i][j]);
                    puts("");
                }
                //puts("���������� �������� ������:");
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
                    puts("�������������� ������:");
                    for(i = 0; i < n; i++)
                    {
                        for(j = 0; j < k; j++) printf("%d ", b[i][j]);
                        puts(" ");
                    }
                }
                else puts("�� ���� ������� ������� �� ������������� �������");
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
        } else puts("�� ������� �������� ������ ��� ���������� �������. ���������� ��� ���, �������� ��������");
        puts("������� ����� ����� �����, �� ������ ����, ����� ��������� ���������");
        scanf("%d", &repeat);
        puts("**************************************************************************");
    } while(repeat);
    return 0;
}
