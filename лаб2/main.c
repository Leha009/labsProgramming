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
    float* fuelPrices;                  //Ниже цены на топливо(92,95,98,дизель)
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
Gaslist* InputMenu(Gaslist*);                   //Меню выбора ввода

int ListLen(Gaslist*);                          //Длина списка
Gaslist* DeleteItem(Gaslist*);                  //Удаление элемента из списка
Gaslist* SortByRating(Gaslist*);                //Сортировка по рейтингу убыв   СДЕЛАТЬ
void Swap(Gaslist*);                            //Поменять местами    СДЕЛАТЬ
//void GetItem(Gaslist*);                         //Вывод АЗС по заданным параметрам СДЕЛАТЬ

Gaslist* PushBack(Gaslist*);                    //Добавление в конец
Gaslist* PushForward(Gaslist*);                 //Добавление в начало
Gaslist* InputStations();                       //Ввод данных об АЗС
Gaslist* Process(Gaslist*);                     //Обработка данных

int PrepareStruct(Gaslist*);                    //Выделение памяти для полей структуры
void CopyStruct(Gaslist*, GSDesc);              //Копирование структуры

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
                First = InputMenu(First);
                //free_list(First);
                //First = InputStations();
                break;
            case 2:
                if(First != NULL) OutputMenu(First);
                else
                {
                    puts("Нет данных для вывода, список пуст!");
                    system("pause");
                }
                break;
            case 3:
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
                            //GetItem(First);
                            //Swap
                            break;
                        case 4:
                            break;
                    }
                } while(MenuItem != 5);
                break;
            case 4:
                if(First != NULL) GResult = Process(First);
                else
                {
                    puts("Не были введены данные. Выполните пункт 1");
                    system("pause");
                }
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
    puts("2 - Удалить элемент списка АЗС");
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

Gaslist* InputMenu(Gaslist* Stations)                       //Меню выбора ввода
{
    system("cls");
    int item;
    do
    {
        system("cls");
        puts("****************Вывод****************");
        puts("1 - Добавить в начало");
        puts("2 - Добавить в конец");
        puts("3 - Ввести полностью заново");
        puts("4 - Назад");
        do
        {
            scanf("%d", &item);
            if(item < 0 || item > 4) puts("Данного пункта меню не существует");
        } while(item < 0 || item > 4);
        fflush(stdin);
        if(item == 1) Stations = PushForward(Stations);
        else if(item == 2) Stations = PushBack(Stations);
        else if(item == 3)
        {
            free_list(Stations);
            Stations = InputStations();
        }
    }while(item != 4);
    return Stations;
}
//------------------------------------------------------ДЕЙСТВИЯ СО СПИСКОМ------------------------------------------------------
int ListLen(Gaslist* Stations)
{
    Gaslist* buff = Stations;
    int len = 0;
    for(;buff != NULL; buff = buff->next) len++;
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
        free_station(toDel);
    }
    system("pause");
    printf("%p", first);
    return first;
}

/*void GetItem(Gaslist* Stations)
{
    system("cls");
    Gaslist* result = NULL;
    Gaslist* buff = Stations;
    int ans;
    puts("Выберите категорию, по которой мы ищем");
    puts("1 - Цены на топливо");
    puts("2 - Рейтинг");
    puts("3 - Количество сотрудников");
    do
    {
        scanf("%d", &ans);
        if(ans < 1 || ans > 3) puts("Введите от 1 до 3");
    } while(ans < 1 || ans > 3);
    if(ans == 1)
    {
        do
        {
            s
        } while(buff != NULL);
    }
    else if(ans == 2)
    {
        s
    }
    else
    {
        s
    }
}*/

Gaslist* Process(Gaslist* Stations)                     //Обработка данных
{
    Gaslist* result = NULL;
    Gaslist* temp = Stations;
    Gaslist* buff = NULL;
    do
    {
        if(*(temp->Station.rating) > 7 && temp->Station.fuelPrices[2] < 54.0)
        {
            if(result == NULL)
            {
                result = (Gaslist*)malloc(sizeof(Gaslist));
                buff = result;
                CopyStruct(buff, temp->Station);
            }
            else
            {
                buff->next = (Gaslist*)malloc(sizeof(Gaslist));
                buff = buff->next;
                CopyStruct(buff, temp->Station);
            }
            buff->next = NULL;
        }
        temp = temp->next;
    } while(temp != NULL);
    return result;
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
                system("cls");
                puts("Введите название АЗС");
                InputText(buff->Station.name);
                puts("\nВведите адрес");
                InputText(buff->Station.address);
                puts("\nВведите цены на топливо(92,95,98,Дизель). Цена не выше 10000");
                for(i = 0; i < 4; i++)
                {
                    do
                    {
                        scanf("%f", buff->Station.fuelPrices+i);
                        if(buff->Station.fuelPrices[i] < 1.0 || buff->Station.fuelPrices[i] > 10000.0) puts("Цена от 1 до 10000");
                    } while(buff->Station.fuelPrices[i] < 1.0 || buff->Station.fuelPrices[i] > 10000.0);
                }
                puts("Введите рейтинг АЗС от 1 до 10");
                do
                {
                    scanf("%d", buff->Station.rating);
                    if(*(buff->Station.rating) < 1 || *(buff->Station.rating) > 10) puts("Рейтинг от 1 до 10!");
                } while(*(buff->Station.rating) < 1 || *(buff->Station.rating) > 10);
                puts("Введите количество сотрудников");
                do
                {
                    scanf("%d", buff->Station.stuff);
                    if(*(buff->Station.stuff) < 1 || *(buff->Station.stuff) > 1000000) puts("Кол-во сотрудников от 1 до 1000000");
                } while(*(buff->Station.stuff) < 1 || *(buff->Station.stuff) > 1000000);
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

Gaslist* PushForward(Gaslist* Stations)                     //Добавление в начало
{
    Gaslist* temp = NULL;
    Gaslist* connector = NULL;
    temp = InputStations();
    for(connector = temp->next ; connector->next != NULL ; connector = temp->next);
    connector->next = Stations;
    return temp;
}

Gaslist* PushBack(Gaslist* Stations)                    //Добавление в конец
{
    Gaslist* temp = NULL;
    Gaslist* connector;
    temp = InputStations();
    connector = temp;
    if(Stations != NULL)
    {
        for(connector = Stations->next ; connector->next != NULL ; connector = connector->next);
        connector->next = temp;
        connector = Stations;
    }
    return connector;
}
//------------------------------------------------------ВЫВОД------------------------------------------------------
void OutputGasStationsTable(Gaslist* first)
{
    fflush(stdout);
    system("cls");
    int namelen,
        addresslen;
    Gaslist* buff = first;
    namelen = 8, addresslen = 5;
    for(; buff != NULL; buff = buff->next)
    {
        if(strlen(buff->Station.name) > namelen) namelen = strlen(buff->Station.name);
        if(strlen(buff->Station.address) > addresslen) addresslen = strlen(buff->Station.address);
    }
    printf("|%*s|%*s|Цена 92 бензина|Цена 95 бензина|Цена 98 бензина|Цена дизеля|Рейтинг|Сотрудников|\n", namelen, "Название", addresslen, "Адрес");
	for(buff = first; buff != NULL; buff = buff->next)
		printf("|%*s|%*s|%15.2f|%15.2f|%15.2f|%11.2f|%7d|%11d|\n", namelen, buff->Station.name, addresslen, buff->Station.address,
         buff->Station.fuelPrices[0], buff->Station.fuelPrices[1], buff->Station.fuelPrices[2], buff->Station.fuelPrices[3], *(buff->Station.rating), *(buff->Station.stuff));
    system("pause");
}

void OutputGasStationsText(Gaslist* first)
{
    fflush(stdout);
    system("cls");
    Gaslist* buff = first;
    int i;
    for(; buff != NULL; buff = buff->next)
    {
        printf("Название: %s", buff->Station.name);
        printf("\nАдрес: %s", buff->Station.address);
        printf("\nЦены(92,95,98,Дизель): ");
        for(i = 0; i < 4; i++) printf("%.2f ", buff->Station.fuelPrices[i]);
        printf("\nРейтинг: %d", *(buff->Station.rating));
        printf("\nКоличество сотрудников: %d", *(buff->Station.stuff));
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

void CopyStruct(Gaslist* ThisStation, GSDesc SDesc)
{
    int k;
    if(PrepareStruct(ThisStation))
    {
        strcpy(ThisStation->Station.name, SDesc.name);
        strcpy(ThisStation->Station.address, SDesc.address);
        for(k = 0; k < 4; k++)
            ThisStation->Station.fuelPrices[k] = SDesc.fuelPrices[k];
        *(ThisStation->Station.rating) = *(SDesc.rating);
        *(ThisStation->Station.stuff) = *(SDesc.stuff);
    }
}
