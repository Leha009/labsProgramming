#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <locale.h>
#include <string.h>

#define MAXLEN 80

typedef struct Gaslist
{
    char* name;                                 //Название
    char* address;                              //Адрес
    float fuelPrices[4];                        //Ниже цены на топливо(92,95,98,дизель)
    int rating;                                 //Рейтинг АЗС(1-10)
    struct Gaslist* next;                       //Ссылка на следующую структуру
} GSDesc;

/*----------------------------ФУНКЦИИ------------------------------*/
int MainMenu();                                 //Меню выбора работы(стек или очередь)
int MenuStack();                                //Меню для стека
int MenuQueue();                                //Меню для очереди
void OutputMenu(GSDesc*);                       //Меню вывода
void Help();                                    //Справка

GSDesc* DeleteItem_Stack(GSDesc*);              //Удаление элемента из стека
GSDesc* DeleteItem_Queue(GSDesc*);              //Удаление элемента из очереди

void GetItem_Stack(GSDesc*);                    //Вывод крайнего элемента стека
void GetItem_Queue(GSDesc*);                    //Вывод крайнего элемента очереди

GSDesc* Push_Stack(GSDesc*);                    //Добавление в стек
GSDesc* Push_Queue(GSDesc*);                    //Добавление в очередь
GSDesc* InputStation();                         //Ввод данных об АЗС

int PrepareStruct(GSDesc*);                     //Выделение памяти для полей структуры
void CopyStruct(GSDesc*, GSDesc*);              //Копирование структуры

void OutputGasStationsTable(GSDesc*);           //Вывод информации в виде таблицы
void OutputGasStationsText(GSDesc*);            //Вывод информации в виде текста

void free_station(GSDesc*);                     //Освобождение памяти одной АЗС
void free_list(GSDesc*);                        //Освобождение памяти списка АЗС
/*-----------------------------------------------------------------*/
int main()
{
    setlocale(LC_ALL, "russian");
    GSDesc*    First = NULL;                    //Начало списка
    int MenuItem;
    do
    {
        MenuItem = MainMenu();
        switch(MenuItem)
        {
            case 1:
                Help();
                break;
            case 2:
                do
                {
                    MenuItem = MenuStack();
                    switch(MenuItem)
                    {
                        case 1:
                            First = Push_Stack(First);
                            break;
                        case 2:
                            if(First) GetItem_Stack(First);
                            else
                            {
                                puts("Вы ничего не ввели, список АЗС пуст! Выполните пункт 1");
                                system("pause");
                            }
                            break;
                        case 3:
                            if(First) OutputMenu(First);
                            else
                            {
                                puts("Вы ничего не ввели, список АЗС пуст! Выполните пункт 1");
                                system("pause");
                            }
                            break;
                        case 4:
                            if(First) First = DeleteItem_Stack(First);
                            else
                            {
                                puts("Вы ничего не ввели, список АЗС пуст! Выполните пункт 1");
                                system("pause");
                            }
                            break;
                    }
                    fflush(stdin);
                } while(MenuItem < 5);
                if(MenuItem == 6) MenuItem = 0;
                break;
            case 3:
                do
                {
                    MenuItem = MenuQueue();
                    switch(MenuItem)
                    {
                        case 1:
                            First = Push_Queue(First);
                            break;
                        case 2:
                            if(First) GetItem_Queue(First);
                            else
                            {
                                puts("Вы ничего не ввели, список АЗС пуст! Выполните пункт 1");
                                system("pause");
                            }
                            break;
                        case 3:
                            if(First) OutputMenu(First);
                            else
                            {
                                puts("Нет данных для вывода! Выполните пункт 1");
                                system("pause");
                            }
                            break;
                        case 4:
                            if(First) First = DeleteItem_Queue(First);
                            else
                            {
                                puts("Вы ничего не ввели, список АЗС пуст! Выполните пункт 1");
                                system("pause");
                            }
                            break;
                    }
                    fflush(stdin);
                } while(MenuItem < 5);
                if(MenuItem == 6) MenuItem = 0;
                break;
            case 4:
                free_list(First);
                puts("Данные очищены!");
                system("pause");
                break;
        }
    } while(MenuItem);
    free_list(First);
    return 0;
}
//------------------------------------------------------МЕНЮ------------------------------------------------------
int MainMenu()
{
    system("cls");
    int selected;
    puts("****************ГЛАВНОЕ МЕНЮ****************");
    puts("1 - Справка");
    puts("2 - Работать с данными, как со стеком");
    puts("3 - Работать с данными, как с очередью");
    puts("4 - Очистить введенные данные");
    puts("0 - Выход");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 4) puts("Данного пункта меню не существует");
    } while(selected < 0 || selected > 4);
    fflush(stdin);
    return selected;
}

int MenuStack()
{
    system("cls");
    int selected;
    puts("****************МЕНЮ(СТЕК)****************");
    puts("1 - Добавление АЗС к имеющемуся списку");
    puts("2 - Вывести последний элемент списка");
    puts("3 - Вывод полного списка АЗС");
    puts("4 - Удалить последний элемент списка");
    puts("5 - Назад к выбору режима работы");
    puts("6 - Завершить работу программы");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 6) puts("Данного пункта меню не существует");
    } while(selected < 0 || selected > 6);
    fflush(stdin);
    return selected;
}

int MenuQueue()
{
    system("cls");
    int selected;
    puts("****************МЕНЮ(ОЧЕРЕДЬ)****************");
    puts("1 - Добавление АЗС к имеющемуся списку");
    puts("2 - Вывести первый элемент списка");
    puts("3 - Вывод полного списка АЗС");
    puts("4 - Удалить первый элемент списка");
    puts("5 - Назад к выбору режима работы");
    puts("6 - Завершить работу программы");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 6) puts("Данного пункта меню не существует");
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

void OutputItem(GSDesc* item)
{
    int selected;
    do
    {
        system("cls");
        puts("****************Вывод****************");
        puts("1 - В виде таблицы");
        puts("2 - В виде текста");
        puts("0 - Назад");
        do
        {
            scanf("%d", &selected);
            if(selected < 0 || selected > 2) puts("Данного пункта меню не существует");
        } while(selected < 0 || selected > 2);
        fflush(stdin);
        if(selected == 1) OutputGasStationsTable(item);
        else if(selected == 2) OutputGasStationsText(item);
    }while(selected);
}

void Help()
{
    system("cls");
    puts("  Данная программа предназначена для работы над списком АЗС, имеющим следующую структуру:");
    puts("название, адрес, цены на топливо и рейтинг - в двух режимах:");
    puts("стек(добавление, удаление и получение последнего элемента)");
    puts("и очередь(те же действия, но с первым элементом). В каждом режиме можно вывести полный список АЗС");
    puts("  В главном меню Вы можете выбрать режим работы");
    puts("Стоит заметить, что, поработав в одном режиме, можно поменять его в том же главном меню");
    puts("а введенные ранее данные не нужно будет вводить заново");
    puts("  При желании можно очистить все данные, выбрав в главном меню подходящий пункт\n");
    system("pause");
}
//------------------------------------------------------ДЕЙСТВИЯ СО СПИСКОМ------------------------------------------------------
GSDesc* DeleteItem_Stack(GSDesc* First)
{
    system("cls");
    GSDesc* buff = NULL;
    GSDesc* temp = NULL;
    for(buff = First; buff->next != NULL; buff = buff->next);
    if(First->next != buff && First->next != NULL)
    {
        for(temp = First; temp->next != buff; temp = temp->next);
        temp->next = NULL;
    }
    else if(First == buff)
        First = First->next;
    else if(First->next == buff)
        First->next = NULL;
    free_station(buff);
    return First;
}

GSDesc* DeleteItem_Queue(GSDesc* First)
{
    system("cls");
    GSDesc* buff = NULL;
    buff = First;
    First = First->next;
    free_station(buff);
    return First;
}

void GetItem_Stack(GSDesc* Stations)
{
    system("cls");
    GSDesc* last = NULL;
    for(last = Stations; last->next != NULL; last = last->next);
    OutputItem(last);
}

void GetItem_Queue(GSDesc* first)
{
    system("cls");
    GSDesc* item = NULL;
    item = (GSDesc*)malloc(sizeof(GSDesc));
    CopyStruct(item, first);
    item->next = NULL;
    OutputItem(item);
    free_station(item);
}

GSDesc* Push_Queue(GSDesc* OtherStations)                     //Добавление в начало
{
    GSDesc* Station = NULL;
    Station = InputStation();
    Station->next = OtherStations;
    return Station;
}

GSDesc* Push_Stack(GSDesc* OtherStations)                    //Добавление в конец
{
    GSDesc* Station = NULL;
    GSDesc* connector = NULL;
    Station = InputStation();
    if(OtherStations)
    {
        for(connector = OtherStations; connector->next != NULL ; connector = connector->next);
        connector->next = Station;
    }
    else
        OtherStations = Station;
    return OtherStations;
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
        if(c == 13 && i == 0)
            puts("Строка не может быть пустой!");
    } while(i < MAXLEN && (c != 13 || i == 0));
    string[i] = '\0';
    fflush(stdin);
}

GSDesc* InputStation()
{
    system("cls");
    int i;
    GSDesc* Station = NULL;
    Station = (GSDesc*)malloc(sizeof(GSDesc));
    if(Station != NULL)
    {
        if(PrepareStruct(Station))
        {
            system("cls");
            puts("Введите название АЗС");
            InputText(Station->name);
            puts("\nВведите адрес");
            InputText(Station->address);
            puts("\nВведите цены на топливо(92,95,98,Дизель). Цена не выше 10000");
            for(i = 0; i < 4; i++)
            {
                do
                {
                    scanf("%f", &(Station->fuelPrices[i]));
                    if(Station->fuelPrices[i] < 1.0 || Station->fuelPrices[i] > 10000.0) puts("Цена от 1 до 10000");
                } while(Station->fuelPrices[i] < 1.0 || Station->fuelPrices[i] > 10000.0);
            }
            puts("Введите рейтинг АЗС от 1 до 10");
            do
            {
                scanf("%d", &(Station->rating));
                if(Station->rating < 1 || Station->rating > 10) puts("Рейтинг от 1 до 10!");
            } while(Station->rating < 1 || Station->rating > 10);
        }
    }
    system("pause");
    return Station;
}
//------------------------------------------------------ВЫВОД------------------------------------------------------
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
    printf("|%*s|%*s|Цена 92 бензина|Цена 95 бензина|Цена 98 бензина|Цена дизеля|Рейтинг|\n", namelen, "Название", addresslen, "Адрес");
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
        printf("Название: %s", buff->name);
        printf("\nАдрес: %s", buff->address);
        printf("\nЦены(92,95,98,Дизель): ");
        for(i = 0; i < 4; i++) printf("%.2f ", buff->fuelPrices[i]);
        printf("\nРейтинг: %d", buff->rating);
        printf("\n\n");
    }
    system("pause");
}
//------------------------------------------------------ПАМЯТЬ------------------------------------------------------
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

void free_station(GSDesc* Station)
{
    if(Station != NULL)
    {
        free(Station->name);
        Station->name = NULL;
        free(Station->address);
        Station->address = NULL;
        Station->next = NULL;
        free(Station);
        Station = NULL;
    }
}

void free_list(GSDesc* item)
{
    if(item != NULL)
    {
        GSDesc* buff = NULL;
        for(; item != NULL; item = buff)
        {
            buff = item->next;
            free_station(item);
        }
    }
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
