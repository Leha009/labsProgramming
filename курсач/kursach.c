#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <locale.h>
#include <string.h>

#define MAXLEN 80
#define DBG puts("DBG");

typedef struct Gaslist
{
    char* name;                                 //��������
    char* address;                              //�����
    float fuelPrices[4];                        //���� ���� �� �������(92,95,98,������)
    int rating;                                 //������� ���(1-10)
    struct Gaslist* next;                       //������ �� ��������� ���������
    struct Gaslist* prev;                       //������ �� ���������� ���������
} GSDesc;

/*----------------------------�������------------------------------*/
int Menu();                                     //����
int ListActions();                              //�������� �� �������
void OutputMenu(GSDesc*);                       //���� ������
GSDesc* InputMenu(GSDesc*);                     //���� ������ �����
void Help();                                    //�������

int ListLen(GSDesc*);                           //����� ������
GSDesc* DeleteItem(GSDesc*);                    //�������� �������� �� ������
GSDesc* Sort(GSDesc*);                          //���������� �� ����
void Swap(GSDesc**);                            //�������� ������� 2 ��������
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
void OutputGasStationsTableReverse(GSDesc*);    //����� ���������� � ���� ������� � �����
void OutputGasStationsTextReverse(GSDesc*);     //����� ���������� � ���� ������ � �����

GSDesc* InputTextFile(GSDesc*);                 //���� ������ � �����
GSDesc* fillStruct(char* string);               //��������� ��������� �� ������ �����
void OutputFile(GSDesc*);                       //����� � ����

GSDesc* free_station(GSDesc*);                  //������������ ������ ����� ���
GSDesc* free_list(GSDesc*);                     //������������ ������ ������ ���
/*-----------------------------------------------------------------*/
int main()
{
    setlocale(LC_ALL, "russian");
    GSDesc*    First = NULL;                    //������ ������
    GSDesc*    GResult = NULL;                  //������ ������ ����������
    int MenuItem, len;
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
                        switch(MenuItem)
                        {
                            case 1:
                                len = ListLen(First);
                                printf("���������� ��������� � ������: %d\n",len);
                                system("pause");
                                break;
                            case 2:
                                First = DeleteItem(First);
                                break;
                            case 3:
                                Swap(&First);
                                break;
                            case 4:
                                First = Sort(First);
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
                    puts("�� ���� ���������� ����������, ���� �� ���� ��� �� ������������� ��������!");
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
    puts("6 - ����� ������");
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
    puts("4 - ���������� ��������� ������ ��� �� ��������(�� ����.)");
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
        puts("3 - � ���� �������, ������� � �����");
        puts("4 - � ���� ������, ������� � �����");
        puts("5 - � ����");
        puts("0 - �����");
        do
        {
            scanf("%d", &item);
            if(item < 0 || item > 5) puts("������� ������ ���� �� ����������");
        } while(item < 0 || item > 5);
        fflush(stdin);
        if(item == 1) OutputGasStationsTable(first);
        else if(item == 2) OutputGasStationsText(first);
        else if(item == 3) OutputGasStationsTableReverse(first);
        else if(item == 4) OutputGasStationsTextReverse(first);
        else if(item == 5) OutputFile(first);
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
        puts("5 - �������� ������ �� �����");
        puts("6 - �����");
        do
        {
            scanf("%d", &item);
            if(item < 0 || item > 6) puts("������� ������ ���� �� ����������");
        } while(item < 0 || item > 6);
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
        else if(item == 5)
        {
            Stations = free_list(Stations);
            Stations = InputTextFile(Stations);
        }
    }while(item != 6);
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
        Stations->prev = NULL;
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
        temp->next->prev = temp;
        toDel = free_station(toDel);
    }
    return Stations;
}

GSDesc* Sort(GSDesc* Stations)                  //����������
{
    system("cls");
    GSDesc* result = NULL;
    GSDesc* temp = NULL;
    GSDesc* buff = NULL;
    GSDesc* buffThis = NULL;
    int num,
        i,
        field,
        mode;
    float buffF;
    puts("�������� ���� ��� ����������\n1 - ���� �� 92 ������, 2 - ���� �� 95 ������, 3 - ���� �� 98 ������, 4 - ���� �� ������, 5 - �������");
    do
    {
        scanf("%d", &field);
        if(field < 1 || field > 5) puts("������ ������ ���� ���!");
    } while(field < 1 || field > 5);
    puts("�������� ����� ����������:\n1 - �� �����������, 2 - �� ��������");
    do
    {
        scanf("%d", &mode);
        if(mode < 1 || mode > 2) puts("������ ������ ������ ���!");
    } while(mode < 1 || mode > 2);
    mode--; field--;
    if(mode)        //��������
    {
        if(field == 4)
        {
            for(num = 10; ListLen(result) != ListLen(Stations) ; num--)
            {
                for(temp = Stations ; temp != NULL ; temp = temp->next)
                {
                    if(temp->rating == num)
                    {
                        if(result == NULL)
                        {
                            result = (GSDesc*)malloc(sizeof(GSDesc));
                            buff = result;
                            CopyStruct(result, temp);
                            buff->prev = NULL;
                        }
                        else
                        {
                            buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                            buff->next->prev = buff;
                            buff = buff->next;
                            CopyStruct(buff, temp);
                        }
                    }
                }
            }
        }
        else
        {
            for(buffThis = Stations; buffThis != NULL; buffThis = buffThis->next)
            {
                for(temp = Stations, buffF = 0.0; temp != NULL; temp = temp->next)
                {
                    if(!buff)
                    {
                        if(temp->fuelPrices[field] > buffF)
                            buffF = temp->fuelPrices[field];
                    }
                    else
                    {
                        if(temp->fuelPrices[field] > buffF && temp->fuelPrices[field] < buff->fuelPrices[field])
                            buffF = temp->fuelPrices[field];
                    }
                }
                for(temp = Stations ; temp != NULL ; temp = temp->next)
                {
                    if(temp->fuelPrices[field] == buffF)
                    {
                        if(result == NULL)
                        {
                            result = (GSDesc*)malloc(sizeof(GSDesc));
                            buff = result;
                            CopyStruct(result, temp);
                            buff->prev = NULL;
                        }
                        else
                        {
                            buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                            buff->next->prev = buff;
                            buff = buff->next;
                            CopyStruct(buff, temp);
                        }
                    }
                }
            }
        }
    }
    else
    {
        if(field == 4)
        {
            for(num = 0; ListLen(result) != ListLen(Stations) ; num++)
            {
                for(temp = Stations ; temp != NULL ; temp = temp->next)
                {
                    if(temp->rating == num)
                    {
                        if(result == NULL)
                        {
                            result = (GSDesc*)malloc(sizeof(GSDesc));
                            buff = result;
                            CopyStruct(result, temp);
                            buff->prev = NULL;
                        }
                        else
                        {
                            buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                            buff->next->prev = buff;
                            buff = buff->next;
                            CopyStruct(buff, temp);
                        }
                    }
                }
            }
        }
        else
        {
            for(buffThis = Stations; buffThis != NULL; buffThis = buffThis->next)
            {
                for(temp = Stations, buffF = 1000000000.0; temp != NULL; temp = temp->next)
                {
                    if(!buff)
                    {
                        if(temp->fuelPrices[field] < buffF)
                            buffF = temp->fuelPrices[field];
                    }
                    else
                    {
                        if(temp->fuelPrices[field] < buffF && temp->fuelPrices[field] > buff->fuelPrices[field])
                            buffF = temp->fuelPrices[field];
                    }
                }
                for(temp = Stations ; temp != NULL ; temp = temp->next)
                {
                    if(temp->fuelPrices[field] == buffF)
                    {
                        if(result == NULL)
                        {
                            result = (GSDesc*)malloc(sizeof(GSDesc));
                            buff = result;
                            CopyStruct(result, temp);
                            buff->prev = NULL;
                        }
                        else
                        {
                            buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                            buff->next->prev = buff;
                            buff = buff->next;
                            CopyStruct(buff, temp);
                        }
                    }
                }
            }
        }
    }
    if(result == NULL) puts("���... ���-�� ����� �� ���! ���������� ��� ���!");
    else puts("���������� ������ �������!");
    Stations = free_list(Stations);
    system("pause");
    return result;
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
                    buff->prev = NULL;
                }
                else
                {
                    buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                    buff->next->prev = buff;
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
                    buff->prev = NULL;
                }
                else
                {
                    buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                    buff->next->prev = buff;
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
                buff->prev = NULL;
            }
            else
            {
                buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                buff->next->prev = buff;
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
    NewStations->prev = NULL;
    for(connector = NewStations ; connector->next != NULL ; connector = connector->next);
    connector->next = Stations;
    if(Stations != NULL) Stations->prev = connector;
    return NewStations;
}

GSDesc* PushBack(GSDesc* NewStations, GSDesc* Stations)                    //���������� � �����
{
    GSDesc* connector = NULL;
    NewStations->prev = NULL;
    connector = NewStations;
    if(Stations != NULL)
    {
        for(connector = Stations ; connector->next != NULL ; connector = connector->next);
        connector->next = NewStations;
        NewStations->prev = connector;
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
        NewStations->prev = buff;
        buff2->prev = connector;
    }
    return Stations;
}

void Swap(GSDesc** Stations)                             //�������� ������� 2 ��������
{
    GSDesc* gFirst = NULL;
    GSDesc* gSecond = NULL;
    GSDesc* buff = NULL;
    GSDesc* buff2 = NULL;
    GSDesc* buff3 = NULL;
    int first,
        second,
        temp,
        i,
        j;
    printf("������� 2 ������ ���������, ������� ������ �������� �������(����� %d ���������): ", ListLen(*Stations));
    do
    {
        scanf("%d %d", &first, &second);
        if(first < 1 || second < 1 || first > ListLen(*Stations) || second > ListLen(*Stations)) printf("������ ��������� ��� � ������, �������� �� 1 �� %d\n", ListLen(*Stations));
    } while(first < 1 || second < 1 || first > ListLen(*Stations) || second > ListLen(*Stations));
    if(first != second)
    {
        if(first > second)
        {
            temp = second;
            second = first;
            first = temp;
        }
        for(i = 1, gFirst = *Stations; i < first; i++, gFirst = gFirst->next);
        for(i = 1, gSecond = *Stations; i < second; i++, gSecond = gSecond->next);
        if(first == 1)
        {
            for(buff = *Stations; buff->next != gSecond; buff = buff->next);
            buff->next = gFirst;
            buff = gFirst->next;
            buff2 = gSecond->next;
            gFirst->next = buff2;
            gSecond->next = buff;
            gFirst->prev = gSecond->prev;
            if(gFirst->next) gFirst->next->prev = gFirst;
            gSecond->next->prev = gSecond;
            gSecond->prev = NULL;
            *Stations = gSecond;
        }
        else if(second - first == 1)
        {
            for(buff = *Stations; buff->next != gFirst; buff = buff->next);
            buff->next = gSecond;
            buff2 = gSecond->next;
            gSecond->next = gFirst;
            gFirst->next = buff2;

            gSecond->prev = gFirst->prev;
            gFirst->prev = gSecond;
            gFirst->next->prev = gFirst;
        }
        else
        {
            for(buff = *Stations; buff->next != gFirst; buff = buff->next);
            for(buff2 = *Stations; buff2->next != gSecond; buff2 = buff2->next);
            buff3 = gFirst->next;
            buff->next = gSecond;
            buff2->next = gFirst;
            gFirst->next = gSecond->next;
            gSecond->next = buff3;

            buff3 = gSecond->prev;
            gSecond->prev = gFirst->prev;
            gSecond->next->prev = gSecond;
            gFirst->prev = buff3;
            gFirst->next->prev = gFirst;
        }
    }
    system("pause");
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
        first->prev = NULL;
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
                buff->next->prev = buff;
                buff = buff->next;
            }
        }
    }
    system("pause");
    return first;
}

GSDesc* InputTextFile(GSDesc* First)
{
    system("cls");
    GSDesc* newFirst = NULL;
    GSDesc* buff = NULL;
    char *text = NULL,
         *string = NULL;
    FILE *file = NULL;
    char filename[128];
    int ans,
        i,
        f,
        size,
        frows,
        strsize,
        linebeg;    //������ ������ ��������� ������
    puts("������ ������� ���� ��� �����? ������� ����� �����, �������� �� ����\n����� ����� ����������� ���� in.txt");
    scanf("%d", &ans);
    fflush(stdin);
    if(ans)
    {
        puts("\n������� ��� ����� ��� ������. ��� ����� �� ������ ��������� 128 ��������!");
        gets(filename);
        fflush(stdin);
        file = fopen(filename, "r");
    }
    else file = fopen("in.txt", "r");
    if(file != NULL)
    {
        fflush(file);
        fseek(file, 0, SEEK_SET);
        fseek(file,0,SEEK_END);
        size = ftell(file);
        rewind(file);
        if(size == 0)
            puts("���� ����!");
        text = (char*)malloc(size*sizeof(char));
        if(text != NULL && size)
        {
            fread(text, size, 1, file);
            if(fclose(file) == EOF) puts("Error closing!");
            frows = 0; f = 0;
            for(i = 0; i < size+1 && !f; i++)
            {
                if(text[i] <= 0) f = 1, text[i] = '\0';
                if(text[i] == '\n' || text[i] == '\0')
                    frows++;
            }
            if(frows > 0)
            {
                linebeg = 0;
                do
                {
                    strsize = 0;
                    while(text[linebeg+strsize] != '\n' && text[linebeg+strsize] != '\0') strsize++;
                    //printf("%d", strsize);
                    string = (char*)malloc((strsize+1)*sizeof(char));
                    for(i = 0; i < strsize; i++)
                        string[i] = text[linebeg+i];
                    string[i] = '\0';
                    if(newFirst)
                    {
                        buff->next = fillStruct(string);
                        buff = buff->next;
                    }
                    else
                    {
                        newFirst = fillStruct(string);
                        buff = newFirst;
                    }
                    frows--;
                    while(text[linebeg] != '\n' && text[linebeg] != '\0') linebeg++;
                    linebeg++;
                    free(string);
                } while(frows != 0);
                puts("������ ��������!");
            }
            else
                puts("��� ������ ������!");
        }
        free(text);
        text = NULL;
    }
    else puts("�� ������� ������� ���� � ����� ������!");
    system("pause");
    return newFirst;
}

GSDesc* fillStruct(char* string)
{
    GSDesc* result = NULL;
    int i,
        len,
        j,
        index,
        buffi;
    char empty[] = "Unknown";
    char** buff = NULL;
    len = strlen(string);
    //printf("DBG: %s\n%d\n", string,len);
    index = 0; buffi = 0;
    buff = (char**)malloc(7*sizeof(char*));
    do
    {
        i = 0;
        while(string[i+index] != ';' && string[i+index] != '\0') i++;
        //printf("%d | %d\n", index, i);
        buff[buffi] = (char*)malloc((i+1)*sizeof(char));
        for(j = 0; j < i; j++)
            buff[buffi][j] = string[index+j];
        buff[buffi][j] = '\0';
        buffi++;
        index += i+1;
    } while(index < len);
    result = (GSDesc*)malloc(sizeof(GSDesc));
    if(PrepareStruct(result))
    {
        if(buffi != 0)
            strcpy(result->name, buff[0]);
        else
            strcpy(result->name, empty);
        if(buffi > 1 && strlen(buff[1]) > 0)
            strcpy(result->address, buff[1]);
        else
            strcpy(result->address, empty);
        for(i = 0; i < 4; i++)
        {
            if(buffi > 2+i)
                result->fuelPrices[i] = atof(buff[2+i]);
            else
                result->fuelPrices[i] = 0.0;
        }
        if(buffi > 6)
            result->rating = atoi(buff[6]);
        else
            result->rating = 0;
    }
    for(i = 0; i < 7; i++)
        free(buff[i]);
    free(buff);
    return result;
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

void OutputGasStationsTableReverse(GSDesc* first)
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
	for(buff = first; buff->next != NULL; buff = buff->next);
	for(; buff != NULL; buff = buff->prev)
		printf("|%*s|%*s|%15.2f|%15.2f|%15.2f|%11.2f|%7d|\n", namelen, buff->name, addresslen, buff->address,
         buff->fuelPrices[0], buff->fuelPrices[1], buff->fuelPrices[2], buff->fuelPrices[3], buff->rating);
    system("pause");
}

void OutputGasStationsTextReverse(GSDesc* first)
{
    fflush(stdout);
    system("cls");
    GSDesc* buff = first;
    int i;
    for(; buff->next != NULL; buff = buff->next);
    for(; buff != NULL; buff=buff->prev)
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

void OutputFile(GSDesc* first)
{
    system("cls");
    FILE *file = NULL;
    GSDesc* buff = first;
    char filename[128];
    int ans,
        i,
        namelen,
        addresslen;
    ans = 0;
    puts("������ ������� ��� ����� ��������������? ������� ����� �����, �������� �� ����.\n� ��������� ������ ��� ���������� � out.txt");
    scanf("%d", &ans);
    fflush(stdin);
    if(ans)
    {
        puts("������� ��� ����� ��� ����������");
        gets(filename);
        file = fopen(filename, "w");
    }
    else file = fopen("out.txt", "w");
    namelen = 8, addresslen = 5;
    for(; buff != NULL; buff = buff->next)
    {
        if(strlen(buff->name) > namelen) namelen = strlen(buff->name);
        if(strlen(buff->address) > addresslen) addresslen = strlen(buff->address);
    }
    fprintf(file, "|%*s|%*s|���� 92 �������|���� 95 �������|���� 98 �������|���� ������|�������|\n", namelen, "��������", addresslen, "�����");
	for(buff = first; buff != NULL; buff = buff->next)
		fprintf(file, "|%*s|%*s|%15.2f|%15.2f|%15.2f|%11.2f|%7d|\n", namelen, buff->name, addresslen, buff->address,
         buff->fuelPrices[0], buff->fuelPrices[1], buff->fuelPrices[2], buff->fuelPrices[3], buff->rating);
    fclose(file);
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
        Station->next = NULL;
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
        Station->prev = NULL;
        free(Station);
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
