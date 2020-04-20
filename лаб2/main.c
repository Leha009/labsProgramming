#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <locale.h>
#include <string.h>

#define MAXLEN 80
#define DBG puts("DBG");

typedef struct
{
    char* name;                         //Название
    char* address;                      //Адрес
    float* fuelPrices;                 //Ниже цены на топливо(92,95,98,дизель)
    int* rating;                        //Рейтинг АЗС(1-10)
    int* stuff;                         //Кол-во сотрудников
} GSDesc;

typedef struct List
{
    struct List* next;
    GSDesc Station;
} Gaslist;
/*----------------------------ФУНКЦИИ------------------------------*/
int Menu();                                     //Меню
int ListActions();                              //Действия со списком
void OutputMenu(Gaslist*);                      //Меню вывода

int ListLen(Gaslist*);                         //Длина списка
Gaslist* DeleteItem(Gaslist*);                      //Удаление элемента из списка

Gaslist* InputStations();                       //Ввод данных об АЗС
Gaslist* Process(Gaslist*);                     //Обработка данных

int PrepareStruct(Gaslist*);                    //Выделение памяти для полей структуры

void OutputGasStationsTable(Gaslist*);          //Вывод информации в виде таблицы
void OutputGasStationsText(Gaslist*);           //Вывод информации в виде текста

void free_station(Gaslist*);                    //Освобождение памяти одной АЗС
void free_list(Gaslist*);                       //Освобождение памяти списка АЗС
/*-----------------------------------------------------------------*/
int main()
{
    setlocale(LC_ALL, "russian");
    Gaslist*    First = NULL;                           //Начало списка
    Gaslist*    GResult = NULL;                         //Начало списка результата
    int MenuItem, len;
    do
    {
        MenuItem = Menu();
        switch(MenuItem)
        {
            case 1:
                free_list(First);
                First = InputStations();
                break;
            case 2:
                if(First != NULL) OutputMenu(First);
                else
                {
                    puts("Нет данных для вывода, список пуст!");
                    system("pause");
                }
                break;
            case 3: //do while
                do
                {
                    MenuItem = ListActions();
                    switch(MenuItem)
                    {
                        case 1:
                            len = ListLen(First);
                            printf("Количество элементов в списке: %d\n",len);
                            system("pause");
                            break;
                        case 2:
                            First = DeleteItem(First);
                            break;
                        case 3:
                            //Swap
                            break;
                        case 4:
                            break;
                    }
                } while(MenuItem != 5);
                break;
            case 4:
                /*if(First != NULL) GResult = Process(First);
                else
                {
                    puts("Не были введены данные. Выполните пункт 1");
                    system("pause");
                }*/
                break;
            case 5:
                if(GResult != NULL) OutputMenu(GResult);
                else
                {
                    puts("Не была обработана информация. Выполните пункт 4");
                    system("pause");
                }
                break;
        }
    } while(MenuItem);
    free_list(First);
    free_list(GResult);
    return 0;
}
//------------------------------------------------------МЕНЮ------------------------------------------------------
int Menu()
{
    system("cls");
    int selected;
    puts("****************МЕНЮ****************");
    puts("1 - Ввод информации об АЗС");
    puts("2 - Вывод информации об АЗС");
    puts("3 - Действия над списком АЗС");
    puts("4 - Обработка данных");
    puts("5 - Вывод данных");
    puts("0 - Выход");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 5) puts("Данного пункта меню не существует");
    } while(selected < 0 || selected > 5);
    fflush(stdin);
    return selected;
}

int ListActions()
{
    system("cls");
    int selected;
    puts("****************МЕНЮ****************");
    puts("1 - Узнать количество элементов списка АЗС");
    puts("2 - Удалить элемент списка АЗС(не удаляет 1, если len> 1)");
    puts("3 - Поменять местами элементы списка АЗС(НЕ ДОСТУПНО)");
    puts("4 - Сортировка элементов списка АЗС(НЕ ДОСТУПНО)");
    puts("5 - Назад");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 5) puts("Данного пункта меню не существует");
    } while(selected < 0 || selected > 5);
    fflush(stdin);
    return selected;
}

void OutputMenu(Gaslist* first)
{
    int item;
    do
    {
        system("cls");
        puts("****************Вывод****************");
        puts("1 - В виде таблицы");
        puts("2 - В виде текста");
        puts("0 - Назад");
        do
        {
            scanf("%d", &item);
            if(item < 0 || item > 2) puts("Данного пункта меню не существует");
        } while(item < 0 || item > 2);
        fflush(stdin);
        if(item == 1) OutputGasStationsTable(first);
        else if(item == 2) OutputGasStationsText(first);
    }while(item);
}
//------------------------------------------------------ДЕЙСТВИЯ СО СПИСКОМ------------------------------------------------------
int ListLen(Gaslist* Stations)
{
    int len = 0;
    for(;Stations != NULL; Stations = Stations->next) len++;
    return len;
}

Gaslist* DeleteItem(Gaslist* Stations)
{
    Gaslist* first = Stations;
    Gaslist* temp = Stations;
    Gaslist* toDel = NULL;
    int num;
    printf("Введите номер элемента, который хотите удалить(всего %d элементов): ", ListLen(Stations));
    do
    {
        scanf("%d", &num);
        if(num < 1 || num > ListLen(Stations)) printf("Элемента под таким номером нет. Введите от 1 до %d\n", ListLen(Stations));
    } while(num < 1 || num > ListLen(Stations));
    if(num == 1)
    {
        if(ListLen(Stations) == 1)
        {
            free_station(Stations);
            first = NULL;
        }
        else
        {
            first = first->next;
            free_station(temp);
            temp = NULL;
        }
    }
    if(num > 1)
    {
        toDel = temp->next;
        while(num > 2)
        {
            temp = Stations->next;
            toDel = temp->next;
            num--;
        }
        temp->next = toDel->next;
        free_station(toDel);
    }
    system("pause");
    return first;
}
//------------------------------------------------------ВВОД------------------------------------------------------
void InputText(char* string)
{
    char c;                     //Введенный символ
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
    } while(i < MAXLEN && c != 13);
    string[i] = '\0';
    fflush(stdin);
}

Gaslist* InputStations()
{
    system("cls");
    int i,
        f;
    Gaslist* first = NULL;
    Gaslist* buff = NULL;
    first = (Gaslist*)malloc(sizeof(Gaslist));
    if(first != NULL)
    {
        buff = first;
        for(f = 1;buff != NULL && f;)
        {
            buff->next = NULL;
            if(PrepareStruct(buff))
            {
                puts("Введите название АЗС");
                InputText(buff->Station.name);
                puts("\nВведите адрес");
                InputText(buff->Station.address);
                puts("\nВведите цены на топливо(92,95,98,Дизель)");
                for(i = 0; i < 4; i++) scanf("%f", buff->Station.fuelPrices+i);
                puts("Введите рейтинг АЗС");
                scanf("%d", buff->Station.rating);
                puts("Введите количество сотрудников");
                scanf("%d", buff->Station.stuff);
                puts("Если хотите продолжить ввод данных, введите любое число, отличное от нуля");
                scanf("%d", &f);
            }
            if(f)
            {
                buff->next = (Gaslist*)malloc(sizeof(Gaslist));
                buff = buff->next;
            }
        }
    }
    system("pause");
    return first;
}
//------------------------------------------------------ВЫВОД------------------------------------------------------
void OutputGasStationsTable(Gaslist* first)
{
    system("cls");
    int namelen,
        addresslen;
    Gaslist* buff = first;
    namelen = 0, addresslen = 0;
    for(; buff != NULL; buff = buff->next)
    {
        if(strlen(first->Station.name) > namelen) namelen = strlen(first->Station.name);
        if(strlen(first->Station.address) > addresslen) addresslen = strlen(first->Station.address);
    }
    if(namelen < 8) namelen = 8;
    if(addresslen < 5) addresslen = 5;
    printf("|%*s|%*s|Цена 92 бензина|Цена 95 бензина|Цена 98 бензина|Цена дизеля|Рейтинг|Сотрудников|\n", namelen, "Название", addresslen, "Адрес");
	for(; first != NULL; first = first->next)
		printf("|%*s|%*s|%15.2f|%15.2f|%15.2f|%11.2f|%7d|%11d|\n", namelen, first->Station.name, addresslen, first->Station.address,
         first->Station.fuelPrices[0], first->Station.fuelPrices[1], first->Station.fuelPrices[2], first->Station.fuelPrices[3], *(first->Station.rating), *(first->Station.stuff));
    system("pause");
}

void OutputGasStationsText(Gaslist* first)
{
    system("cls");
    int i;
    for(; first != NULL; first = first->next)
    {
        printf("Название: %s", first->Station.name);
        printf("\nАдрес: %s", first->Station.address);
        printf("\nЦены(92,95,98,Дизель): ");
        for(i = 0; i < 4; i++) printf("%.2f ", first->Station.fuelPrices[i]);
        printf("\nРейтинг: %d", *(first->Station.rating));
        printf("\nКоличество сотрудников: %d", *(first->Station.stuff));
        printf("\n\n");
    }
    system("pause");
}

//------------------------------------------------------ПАМЯТЬ------------------------------------------------------
int PrepareStruct(Gaslist* first)
{
    int res = 0;
    if(first != NULL)
    {
        first->Station.name = (char*)malloc((MAXLEN+1)*sizeof(char));
        first->Station.address = (char*)malloc((MAXLEN+1)*sizeof(char));
        first->Station.fuelPrices = (float*)malloc(4*sizeof(float));
        first->Station.rating = (int*)malloc(sizeof(int));
        first->Station.stuff = (int*)malloc(sizeof(int));
        res++;
    }
    return res;
}

void free_station(Gaslist* List)
{
    if(List != NULL)
    {
        free(List->Station.name);
        List->Station.name = NULL;
        free(List->Station.address);
        List->Station.address = NULL;
        free(List->Station.fuelPrices);
        List->Station.fuelPrices = NULL;
        free(List->Station.rating);
        List->Station.rating = NULL;
        free(List->Station.stuff);
        List->Station.stuff = NULL;
        free(List->next);
        List->next = NULL;
        List = NULL;
    }
}

void free_list(Gaslist* item)
{
    if(item != NULL)
    {
        Gaslist* buff = NULL;
        for(; item != NULL;)
        {
            buff = item;
            free_station(item);
            item = buff->next;
            free(buff);
            buff = NULL;
        }
    }
}
