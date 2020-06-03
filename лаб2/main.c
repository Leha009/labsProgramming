#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <locale.h>
#include <string.h>

#define MAXLEN 80

typedef struct Gaslist
{
    char* name;                                 //��������
    char* address;                              //�����
    float fuelPrices[4];                        //���� ���� �� �������(92,95,98,������)
    int rating;                                 //������� ���(1-10)
    struct Gaslist* next;                       //������ �� ��������� ���������
} GSDesc;

/*----------------------------�������------------------------------*/
int Menu();                                     //����
void OutputMenu(GSDesc*);                       //���� ������
GSDesc* InputMenu(GSDesc*);                     //���� ������ �����
void Help();                                    //�������
int ListActions();                              //�������� �� �������

int ListLen(GSDesc*);                           //����� ������
GSDesc* DeleteItem(GSDesc*);                    //�������� �������� �� ������
void Sort(GSDesc**, int);                       //���������� �� ����
void Swap(GSDesc*,int,int);                     //�������� ������� 2 ��������
void GetItem(GSDesc*);                          //����� ��� �� �������� ����������

GSDesc* PushBack(GSDesc*, GSDesc*);             //���������� � �����
GSDesc* PushForward(GSDesc*, GSDesc*);          //���������� � ������
GSDesc* PushAnyPlace(GSDesc*);                  //���������� � ����� �����
GSDesc* InputStations();                        //���� ������ �� ���
GSDesc* Process(GSDesc*);                       //��������� ������

int PrepareStruct(GSDesc*);                     //��������� ������ ��� ����� ���������
void CopyStruct(GSDesc*, GSDesc*);              //����������� ���������

void OutputGasStationsTable(GSDesc*);           //����� ���������� � ���� �������
void OutputGasStationsText(GSDesc*);            //����� ���������� � ���� ������

GSDesc* free_station(GSDesc*);                  //������������ ������ ����� ���
GSDesc* free_list(GSDesc*);                     //������������ ������ ������ ���
/*-----------------------------------------------------------------*/
int main()
{
    setlocale(LC_ALL, "russian");
    GSDesc*    First = NULL;                    //������ ������
    GSDesc*    GResult = NULL;                  //������ ������ ����������
    int MenuItem, len, index1, index2, field;
    do
    {
        MenuItem = Menu();
        switch(MenuItem)
        {
            case 1:
                Help();
                break;
            case 2:
                First = InputMenu(First);
                break;
            case 3:
                if(First != NULL) OutputMenu(First);
                else
                {
                    puts("��� ������ ��� ������, ������ ����!");
                    system("pause");
                }
                break;
            case 4:
                if(First != NULL)
                {
                    do
                    {
                        MenuItem = ListActions();
                        len = ListLen(First);
                        switch(MenuItem)
                        {
                            case 1:
                                printf("���������� ��������� � ������: %d\n",len);
                                system("pause");
                                break;
                            case 2:
                                First = DeleteItem(First);
                                break;
                            case 3:
                                system("cls");
                                printf("������� ��� ������ ��������� ��� ������������(�� 1 �� %d): ", len);
                                do
                                {
                                    scanf("%d %d", &index1, &index2);
                                    if(index1 < 1 || index1 > len || index2 < 1 || index2 > len)
                                        printf("��������� ������ ������ ���� �� 1 �� %d!\n", len);
                                } while(index1 < 1 || index1 > len || index2 < 1 || index2 > len);
                                Swap(First, index1, index2);
                                break;
                                break;
                            case 4:
                                system("cls");
                                puts("�������� ���� ��� ����������:\n1 - ��������, 2 - �����, 3 - ���� �� 92 ������,4 - ���� �� 95 ������\n5 - ���� �� 98 ������, 6 - ���� �� ������, 7 - �������");
                                do
                                {
                                    scanf("%d", &field);
                                    if(field < 1 || field > 7) puts("���� � ����� ������� ���!");
                                } while(field < 1 || field > 7);
                                Sort(&First, field);
                                break;
                                break;
                            case 5:
                                GetItem(First);
                                break;
                        }
                    } while(MenuItem != 6);
                }
                else
                {
                    puts("������� ������� ������ ���!");
                    system("pause");
                }
                break;
            case 5:
                if(First != NULL)
                {
                    GResult = free_list(GResult);
                    GResult = Process(First);
                }
                else
                {
                    puts("������� ������� ������ ���!");
                    system("pause");
                }
                break;
            case 6:
                if(GResult != NULL) OutputMenu(GResult);
                else
                {
                    puts("�� ���� ���������� ����������, ���� �� ���� ��� �� �������� ��� �������!");
                    system("pause");
                }
                break;
        }
    } while(MenuItem);
    First = free_list(First);
    GResult = free_list(GResult);
    return 0;
}
//------------------------------------------------------����------------------------------------------------------
int Menu()
{
    system("cls");
    int selected;
    puts("****************����****************");
    puts("1 - �������");
    puts("2 - ���� ���������� �� ���");
    puts("3 - ����� ���������� �� ���");
    puts("4 - �������� ��� ������� ���");
    puts("5 - ��������� ������");
    puts("6 - ����� ������������ ������");
    puts("0 - �����");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 6) puts("������� ������ ���� �� ����������");
    } while(selected < 0 || selected > 6);
    fflush(stdin);
    return selected;
}

int ListActions()
{
    system("cls");
    int selected;
    puts("****************����****************");
    puts("1 - ������ ���������� ��������� ������ ���");
    puts("2 - ������� ������� ������ ���");
    puts("3 - �������� ������� �������� ������ ���");
    puts("4 - ���������� ��������� ������ ���(�� ����.)");
    puts("5 - ����� ��� �� ������������� ��������");
    puts("6 - �����");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 6) puts("������� ������ ���� �� ����������");
    } while(selected < 0 || selected > 6);
    fflush(stdin);
    return selected;
}

void OutputMenu(GSDesc* first)
{
    int item;
    do
    {
        system("cls");
        puts("****************�����****************");
        puts("1 - � ���� �������");
        puts("2 - � ���� ������");
        puts("0 - �����");
        do
        {
            scanf("%d", &item);
            if(item < 0 || item > 2) puts("������� ������ ���� �� ����������");
        } while(item < 0 || item > 2);
        fflush(stdin);
        if(item == 1) OutputGasStationsTable(first);
        else if(item == 2) OutputGasStationsText(first);
    }while(item);
}

GSDesc* InputMenu(GSDesc* Stations)                       //���� ������ �����
{
    system("cls");
    GSDesc* NewStations = NULL;
    int item;
    do
    {
        system("cls");
        puts("****************����****************");
        puts("1 - �������� � ������");
        puts("2 - �������� � �����");
        puts("3 - �������� �� ������������ �����");
        puts("4 - ������ ��������� ������");
        puts("5 - �����");
        do
        {
            scanf("%d", &item);
            if(item < 1 || item > 5) puts("������� ������ ���� �� ����������");
        } while(item < 1 || item > 5);
        fflush(stdin);
        if(item < 3) NewStations = InputStations();
        if(item == 1) Stations = PushForward(NewStations, Stations);
        else if(item == 2) Stations = PushBack(NewStations, Stations);
        else if(item == 3) Stations = PushAnyPlace(Stations);
        else if(item == 4)
        {
            Stations = free_list(Stations);
            Stations = InputStations();
        }
    }while(item != 5);
    return Stations;
}

void Help()
{
    system("cls");
    puts("  ������ ��������� ��������� ��� ������ ��� ������� ���,");
    puts("������� ��������� ���������: ��������, �����, ���� �� ������� � �������");
    puts("  ����� '���������' ������������� ��� ����� ����� ��� ���,");
    puts("������� ������������� ��������� ��������:");
    puts("������� ���� 7, ���� �� 98 ������ ���� 54");
    puts("  ����� ��� �������� ��������� �������� ��� �������:");
    puts("������ ���-�� ��� � ������, ������� ���� ��� �� ������,");
    puts("�������� ������� 2 ��� � ������, ������������� �� �������� ��������");
    puts("(��� ���������� ���������� ����������� ������, ������ �����������!)");
    puts("����� ��� �� ������������� ���������\n");
    puts("  ��������! ���-�� ���� � �������� � ������ �� ����� ��������� 80!\n");
    system("pause");
}
//------------------------------------------------------�������� �� �������------------------------------------------------------
int ListLen(GSDesc* Stations)
{
    int len = 0;
    for(;Stations != NULL; Stations = Stations->next) len++;
    return len;
}

GSDesc* DeleteItem(GSDesc* Stations)
{
    system("cls");
    GSDesc* temp = Stations;
    GSDesc* toDel = NULL;
    int num;
    printf("������� ����� ��������, ������� ������ �������(����� %d ���������): ", ListLen(Stations));
    do
    {
        scanf("%d", &num);
        if(num < 1 || num > ListLen(Stations)) printf("�������� ��� ����� ������� ���. ������� �� 1 �� %d\n", ListLen(Stations));
    } while(num < 1 || num > ListLen(Stations));
    if(num == 1)
    {
        Stations = Stations->next;
        temp = free_station(temp);
    }
    else
    {
        toDel = temp->next;
        while(num > 2)
        {
            temp = temp->next;
            toDel = temp->next;
            num--;
        }
        temp->next = toDel->next;
        toDel = free_station(toDel);
    }
    return Stations;
}

void Sort(GSDesc** Stations, int field)                  //����������: �����, ��������, ���� �� 92,95,98,������, �������
{
    system("cls");
    GSDesc* result = NULL;
    GSDesc* temp = NULL;
    GSDesc* buff = NULL;
    GSDesc* buffThis = NULL;
    int num,
        i,
        j,
        n;
    n = ListLen(*Stations);
    if(field == 1)
    {
        for(i = 1, buffThis = *Stations; i <= n; buffThis = buffThis->next, i++)
        {
            for(j = 1, temp = *Stations; temp->next != NULL; temp = temp->next, j++)
            if(strcmp(buffThis->name, temp->name) < 0)
                Swap(*Stations, i,j);
        }
    }
    else if(field == 2)
    {
        for(i = 1, buffThis = *Stations; i <= n; buffThis = buffThis->next, i++)
        {
            for(j = 1, temp = *Stations; temp->next != NULL; temp = temp->next, j++)
            if(strcmp(buffThis->address, temp->address) < 0)
                Swap(*Stations, i,j);
        }
    }
    else if(field > 2 && field < 7)
    {
        field-=3;
        for(i = 1, buffThis = *Stations; i <= n; buffThis = buffThis->next, i++)
        {
            for(j = 1, temp = *Stations ; temp->next != NULL; temp = temp->next, j++)
            {
                if(buffThis->fuelPrices[field] < temp->fuelPrices[field])
                    Swap(*Stations, i,j);
            }
        }
    }
    else if(field == 7)
    {
        for(i = 1, buffThis = *Stations; i <= n; i++, buffThis = buffThis->next)
			for(j = 1, temp = *Stations; j <= n; j++, temp = temp->next)
			{
				if(buffThis->rating < temp->rating)
					Swap(*Stations, i, j);
			}
    }
    puts("���������� ������ �������!");
    system("pause");
}

void GetItem(GSDesc* Stations)
{
    system("cls");
    GSDesc* result = NULL;
    GSDesc* buff = NULL;
    int ans,
        num;
    float price;
    puts("�������� ���������, �� ������� �� ����");
    puts("1 - ���� �� �������");
    puts("2 - �������");
    puts("3 - ������");
    do
    {
        scanf("%d", &ans);
        if(ans < 1 || ans > 3) puts("������� �� 1 �� 3");
    } while(ans < 1 || ans > 3);
    if(ans == 1)
    {
        puts("\n��������, �� ���� ������ ������� ����� ������\n1 - 92 ������\n2 - 95 ������\n3 - 98 ������\n4 - ������");
        do
        {
            scanf("%d", &num);
            if(num < 1 || num > 4) puts("������� �� 1 �� 4");
        } while(num < 1 || num > 4);
        printf("\n������� ����, �� ������� ����� ������: ");
        do
        {
            scanf("%f", &price);
            if(price < 0) puts("���� ������ ���� ���� 0!");
        } while(price < 0);
        for(; Stations != NULL; Stations = Stations->next)
        {
            if(Stations->fuelPrices[num-1] == price)
            {
                if(result == NULL)
                {
                    result = (GSDesc*)malloc(sizeof(GSDesc));
                    buff = result;
                    CopyStruct(buff, Stations);
                }
                else
                {
                    buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                    buff = buff->next;
                    CopyStruct(buff, Stations);
                }
            }
        }
    }
    else if(ans == 2)
    {
        printf("������� �������, �� �������� ����� ������(�� 1 �� 10): ");
        do
        {
            scanf("%d", &num);
            if(num < 1 || num > 10) puts("������� ������ ���� �� 1 �� 10!");
        } while(num < 1 || num > 10);
        for(; Stations != NULL; Stations = Stations->next)
        {
            if(Stations->rating == num)
            {
                if(result == NULL)
                {
                    result = (GSDesc*)malloc(sizeof(GSDesc));
                    buff = result;
                    CopyStruct(buff, Stations);
                }
                else
                {
                    buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                    buff = buff->next;
                    CopyStruct(buff, Stations);
                }
            }
        }
    }
    if(ans != 3)
        if(result != NULL) OutputMenu(result);
        else
            puts("������ �� �������!"), system("pause");
    result = free_list(result);
}

GSDesc* Process(GSDesc* Stations)                     //��������� ������
{
    GSDesc* result = NULL;
    GSDesc* buff = NULL;
    do
    {
        if(Stations->rating > 7 && Stations->fuelPrices[2] < 54.0)
        {
            if(result == NULL)
            {
                result = (GSDesc*)malloc(sizeof(GSDesc));
                buff = result;
                CopyStruct(buff, Stations);
            }
            else
            {
                buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                buff = buff->next;
                CopyStruct(buff, Stations);
            }
        }
        Stations = Stations->next;
    } while(Stations != NULL);
    if(result == NULL) puts("�� ���� ��� �� �������� ��� ��������");
    else puts("��������� ������ �������!");
    system("pause");
    return result;
}

GSDesc* PushForward(GSDesc* NewStations, GSDesc* Stations)                     //���������� � ������
{
    GSDesc* connector = NULL;
    for(connector = NewStations ; connector->next != NULL ; connector = connector->next);
    connector->next = Stations;
    return NewStations;
}

GSDesc* PushBack(GSDesc* NewStations, GSDesc* Stations)                    //���������� � �����
{
    GSDesc* connector = NULL;
    connector = NewStations;
    if(Stations != NULL)
    {
        for(connector = Stations ; connector->next != NULL ; connector = connector->next);
        connector->next = NewStations;
        connector = Stations;
    }
    return connector;
}

GSDesc* PushAnyPlace(GSDesc* Stations)                  //���������� � ����� �����
{
    system("cls");
    GSDesc* NewStations = NULL;
    GSDesc* connector = NULL;
    GSDesc* buff = NULL;
    GSDesc* buff2 = NULL;
    int ans,
        i,
        len;
    len = ListLen(Stations);
    printf("������� ����� �����, �� ������� ������ �������� ����� ���(�� 1 �� %d)\n", len+1);
    do
    {
        scanf("%d", &ans);
        if(ans < 1 || ans > len+1) printf("������� �� 1 �� %d\n", len+1);
    } while(ans < 1 || ans > len+1);
    NewStations = InputStations();
    if(ans == 1)
        Stations = PushForward(NewStations, Stations);
    else if(ans == len+1)
        Stations = PushBack(NewStations, Stations);
    else
    {
        buff = Stations;
        for(i = 1; i < ans-1; i++)
            buff = buff->next;
        buff2 = buff->next;
        for(connector = NewStations ; connector->next != NULL ; connector = connector->next);
        buff->next = NewStations;
        connector->next = buff2;
    }
    return Stations;
}

void Swap(GSDesc* Stations, int first, int second)                             //�������� ������� 2 ��������
{
    GSDesc* gFirst = NULL;
    GSDesc* gSecond = NULL;
    GSDesc* buff = NULL;
    int i,
        temp;
    if(first > second)
    {
        temp = first;
        first = second;
        second = temp;
    }
    if(first != second)
    {
        buff = (GSDesc*)malloc(sizeof(GSDesc));
        PrepareStruct(buff);
        for(i = 1, gFirst = Stations; i < first; i++, gFirst = gFirst->next);
        for(i = 1, gSecond = Stations; i < second; i++, gSecond = gSecond->next);
        CopyStruct(buff, gFirst);
        CopyStruct(gFirst, gSecond);
        CopyStruct(gSecond, buff);
        free(buff);
    }
}
//------------------------------------------------------����------------------------------------------------------
void InputText(char* string)
{
    char c;                     //��������� ������
    int i;
    i = 0;
    do
    {
        c = getch();
        if(c != 13 && c != 8)
        {
            string[i] = c;
            printf("%c", c);
            i++;
        }
        else if(c == 8)
        {
            if(i > 0)
            {
                string[i-1] = '\0';
                printf("\r%s %c", string, c);
                i--;
            }
        }
        if(c == 13 && i == 0)
            puts("������ �� ����� ���� ������!");
    } while(i < MAXLEN && (c != 13 || i == 0));
    string[i] = '\0';
    fflush(stdin);
}

GSDesc* InputStations()
{
    system("cls");
    int i,
        f;
    GSDesc* first = NULL;
    GSDesc* buff = NULL;
    first = (GSDesc*)malloc(sizeof(GSDesc));
    if(first != NULL)
    {
        for(f = 1, buff = first ; buff != NULL && f ;)
        {
            if(PrepareStruct(buff))
            {
                system("cls");
                puts("������� �������� ���");
                InputText(buff->name);
                puts("\n������� �����");
                InputText(buff->address);
                puts("\n������� ���� �� �������(92,95,98,������). ���� �� ���� 10000");
                for(i = 0; i < 4; i++)
                {
                    do
                    {
                        scanf("%f", &(buff->fuelPrices[i]));
                        if(buff->fuelPrices[i] < 1.0 || buff->fuelPrices[i] > 10000.0) puts("���� �� 1 �� 10000");
                    } while(buff->fuelPrices[i] < 1.0 || buff->fuelPrices[i] > 10000.0);
                }
                puts("������� ������� ��� �� 1 �� 10");
                do
                {
                    scanf("%d", &(buff->rating));
                    if(buff->rating < 1 || buff->rating > 10) puts("������� �� 1 �� 10!");
                } while(buff->rating < 1 || buff->rating > 10);
                puts("���� ������ ���������� ���� ������, ������� ����� �����, �������� �� ����");
                scanf("%d", &f);
            }
            if(f)
            {
                buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                buff = buff->next;
            }
        }
    }
    system("pause");
    return first;
}
//------------------------------------------------------�����------------------------------------------------------
void OutputGasStationsTable(GSDesc* first)
{
    fflush(stdout);
    system("cls");
    int namelen,
        addresslen;
    GSDesc* buff = first;
    namelen = 8, addresslen = 5;
    for(; buff != NULL; buff = buff->next)
    {
        if(strlen(buff->name) > namelen) namelen = strlen(buff->name);
        if(strlen(buff->address) > addresslen) addresslen = strlen(buff->address);
    }
    printf("|%*s|%*s|���� 92 �������|���� 95 �������|���� 98 �������|���� ������|�������|\n", namelen, "��������", addresslen, "�����");
	for(buff = first; buff != NULL; buff = buff->next)
		printf("|%*s|%*s|%15.2f|%15.2f|%15.2f|%11.2f|%7d|\n", namelen, buff->name, addresslen, buff->address,
         buff->fuelPrices[0], buff->fuelPrices[1], buff->fuelPrices[2], buff->fuelPrices[3], buff->rating);
    system("pause");
}

void OutputGasStationsText(GSDesc* first)
{
    fflush(stdout);
    system("cls");
    GSDesc* buff = first;
    int i;
    for(; buff != NULL; buff = buff->next)
    {
        printf("��������: %s", buff->name);
        printf("\n�����: %s", buff->address);
        printf("\n����(92,95,98,������): ");
        for(i = 0; i < 4; i++) printf("%.2f ", buff->fuelPrices[i]);
        printf("\n�������: %d", buff->rating);
        printf("\n\n");
    }
    system("pause");
}
//------------------------------------------------------������------------------------------------------------------
int PrepareStruct(GSDesc* Station)
{
    int res = 0,
        i;
    if(Station != NULL)
    {
        Station->name = (char*)malloc((MAXLEN+1)*sizeof(char));
        Station->address = (char*)malloc((MAXLEN+1)*sizeof(char));
        for(i = 0; i < 4; i++) Station->fuelPrices[i] = 0;
        Station->rating = 0;
        //Station->next = NULL;
        res++;
    }
    return res;
}

GSDesc* free_station(GSDesc* Station)
{
    if(Station != NULL)
    {
        free(Station->name);
        Station->name = NULL;
        free(Station->address);
        Station->address = NULL;
        Station->next = NULL;
        Station = NULL;
    }
    return NULL;
}

GSDesc* free_list(GSDesc* item)
{
    if(item != NULL)
    {
        GSDesc* buff = NULL;
        for(; item != NULL; item = buff)
        {
            buff = item->next;
            item = free_station(item);
        }
    }
    return NULL;
}

void CopyStruct(GSDesc* ThisStation, GSDesc* OtherStation)
{
    int i;
    if(PrepareStruct(ThisStation))
    {
        strcpy(ThisStation->name, OtherStation->name);
        strcpy(ThisStation->address, OtherStation->address);
        for(i = 0; i < 4; i++)
            ThisStation->fuelPrices[i] = OtherStation->fuelPrices[i];
        ThisStation->rating = OtherStation->rating;
    }
}
