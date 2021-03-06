#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_SIZE 10

int main()
{
    setlocale(LC_ALL, "russian");
    int a[MAX_SIZE], //������
    sum, //����� ��������� ������������� �����
    sign, //���������� ����� � ����� ������, ������ ������
    row, //������������ ���������� ����� � ����� ������, ������ ������
    last, //������ ���������� �������������� �����
    f, //����, ������������ ����� ���� ��������� ������������� �����
    repeat = 1; //���� ������� ���������
    while(repeat)
    {
        sign = 0;
        sum = 0;
        last = 0;
        f = 1;
        puts("������� �����, ������� 1, ������������ ������������ ���������� ����� � ����� ������, ������ ������");
        do
        {
            scanf("%d", &row);
        } while(row < 1);
        puts("��������� ������� �������� ������������������. ����� ������� �������� ��������� Enter");
        for(int i = 0; i < MAX_SIZE && abs(sign) < row; i++)
        {
            scanf("%d", &a[i]);
            if(a[i] < 0)
            {
                if(sign > 0) sign = -1;
                else sign--;
                last = i;
            }
            else
            {
                if(sign > 0) sign++;
                else sign = 1;
            }
        }
        for(int i = last; i >= 0 && f; i--)
        {
            if(a[i] > 0) f = 0;
            else sum += a[i];
        }
        printf("����� ��������� ������ ������ ������������� ����� ����� %d\n", sum);
        puts("������� ����� �����, �������� �� ����, ����� ��������� ������ ���������");
        scanf("%d", &repeat);
        puts("**************************************************************************");
    }
    return 0;
}
