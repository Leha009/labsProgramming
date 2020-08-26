#include <stdio.h>
#include <limits.h>
#include <locale.h>

#define MAX_SIZE 10

int main()
{
    setlocale(LC_ALL, "russian");
    int a[MAX_SIZE][MAX_SIZE],  //�������� ������
        b[MAX_SIZE][MAX_SIZE],  //�������������� ������
        mlimit,                 //������ ������������ ����� � ������ �������
        mult,                   //������������ ����� � ������ �������
        min,                    //����������� ����� � ������ �������
        sum,                    //����� ����� ������� �������
        repeat,                 //���� ���������� ������ ���������
        m,                      //���������� �������� ��������� �������
        n,                      //���������� ����� �������
        k;                      //���������� �������� ��������������� �������
    do
    {
        sum = 0; k = 0;
        for(int i = 0; i < MAX_SIZE; i++)
            for(int j = 0; j < MAX_SIZE; j++) b[i][j] = 0, a[i][j] = 0;
        puts("������� ����� - ������ ������������ ����� � ������ �������");
        scanf("%d", &mlimit);
        printf("������� ������� �������. ������� ���������� ��������, ����� - �����. ������������ ������: %dx%d\n", MAX_SIZE, MAX_SIZE);
        do
        {
            scanf("%d %d", &m, &n);
            if(m < 1 || n < 1) printf("������ ������� ������ ���� ������� 1�1, �������� %dx%d\n", MAX_SIZE, MAX_SIZE);
        } while((m < 1 || n < 1) || m > MAX_SIZE || n > MAX_SIZE);
        printf("��������� ������� �������� ������� �������� �������: %d ������: %d\n", m, n);
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                scanf("%d", &a[i][j]);
                if(j == 0)
                {
                    min = a[i][j];
                    mult = a[i][j];
                }
                if(mult > mlimit) a[i][j] = min;
                if(a[i][j] < min) min = a[i][j];
                if(j && mult <= mlimit) mult *= a[i][j];
            }
        }
        puts("�������� ������:");
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++) printf("%d ", a[i][j]);
            puts("");
        }
        for(int j = 0; j < m; j++)
        {
            sum = 0;
            for(int i = 0; i < n; i++) sum += a[i][j];
            if(sum >= 0)
            {
                for(int i = 0; i < n; i++) b[i][k] = a[i][j];
                k++;
            }
        }
        if(k > 0)
        {
            puts("�������������� ������:");
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < k; j++) printf("%d ", b[i][j]);
                puts(" ");
            }
        }
        else puts("�� ���� ������� ������� �� ������������� �������");
        puts("������� ����� ����� �����, �� ������ ����, ����� ��������� ���������");
        scanf("%d", &repeat);
        puts("**************************************************************************");
    } while(repeat);
    return 0;
}
