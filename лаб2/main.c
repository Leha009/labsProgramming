#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <locale.h>
#include <string.h>

#define MAXLEN 80
#define DBG puts("DBG");

typedef struct Gaslist
{
    char* name;                             //Название
    char* address;                          //Адрес
    float fuelPrices[4];                    //Ниже цены на топливо(92,95,98,дизель)
    int rating;                             //Рейтинг АЗС(1-10)
    int stuff;                              //Кол-во сотрудников
    struct Gaslist* next;                   //Ссылка на следующую структуру
} GSDesc;

/*----------------------------ФУНКЦИИ------------------------------*/
int Menu();                                     //Меню
int ListActions();                              //Действия со списком
void OutputMenu(GSDesc*);                       //Меню вывода
GSDesc* InputMenu(GSDesc*);                     //Меню выбора ввода

int ListLen(GSDesc*);                           //Длина списка
GSDesc* DeleteItem(GSDesc*);                    //Удаление элемента из списка
GSDesc* SortByRating(GSDesc*);                  //Сортировка по рейтингу убыв   СДЕЛАТЬ
void Swap(GSDesc**);                            //Поменять местами
//void GetItem(GSDesc*);                        //Вывод АЗС по заданным параметрам СДЕЛАТЬ

GSDesc* PushBack(GSDesc*);                      //Добавление в конец
GSDesc* PushForward(GSDesc*);                   //Добавление в начало
GSDesc* InputStations();                        //Ввод данных об АЗС
GSDesc* Process(GSDesc*);                       //Обработка данных

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
    GSDesc*    First = NULL;                           //Начало списка
    GSDesc*    GResult = NULL;                         //Начало списка результата
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
                if(First != NULL)
                {
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
                                Swap(&First);
                                break;
                            case 4:
                                break;
                        }
                    } while(MenuItem != 5);
                }
                else
                {
                    puts("Сначала введите список АЗС в пункте 1!");
                    system("pause");
                }
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

GSDesc* InputMenu(GSDesc* Stations)                       //Меню выбора ввода
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
int ListLen(GSDesc* Stations)
{
    GSDesc* buff = Stations;
    int len = 0;
    for(;buff != NULL; buff = buff->next) len++;
    return len;
}

GSDesc* DeleteItem(GSDesc* Stations)
{
    GSDesc* first = Stations;
    GSDesc* temp = Stations;
    GSDesc* toDel = NULL;
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

/*void GetItem(GSDesc* Stations)
{
    system("cls");
    GSDesc* result = NULL;
    GSDesc* buff = Stations;
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

GSDesc* Process(GSDesc* Stations)                     //Обработка данных
{
    GSDesc* result = NULL;
    GSDesc* temp = Stations;
    GSDesc* buff = NULL;
    do
    {
        if(temp->rating > 7 && temp->fuelPrices[2] < 54.0)
        {
            if(result == NULL)
            {
                result = (GSDesc*)malloc(sizeof(GSDesc));
                buff = result;
                CopyStruct(buff, temp);
            }
            else
            {
                buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                buff = buff->next;
                CopyStruct(buff, temp);
            }
            buff->next = NULL;
        }
        temp = temp->next;
    } while(temp != NULL);
    if(result == NULL) puts("Ни одна АЗС не подходит под критерии");
    else puts("Обработка прошла успешно!");
    system("pause");
    return result;
}

GSDesc* PushForward(GSDesc* Stations)                     //Добавление в начало
{
    GSDesc* temp = NULL;
    GSDesc* connector = NULL;
    temp = InputStations();
    for(connector = temp ; connector->next != NULL ; connector = connector->next);
    connector->next = Stations;
    return temp;
}

GSDesc* PushBack(GSDesc* Stations)                    //Добавление в конец
{
    GSDesc* temp = NULL;
    GSDesc* connector;
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

void Swap(GSDesc** Stations)                             //Поменять местами
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
    printf("Введите 2 номера элементов, которые хотите поменять местами(всего %d элементов): ", ListLen(*Stations));
    do
    {
        scanf("%d %d", &first, &second);
        if(first < 1 || second < 1 || first > ListLen(*Stations) || second > ListLen(*Stations)) printf("Данных элементов нет в списке, выберите от 1 до %d\n", ListLen(*Stations));
    } while(first < 1 || second < 1 || first > ListLen(*Stations) || second > ListLen(*Stations));
    if(first != second)
    {
        if(first > second)
        {
            temp = second;
            second = first;
            first = second;
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
            *Stations = gSecond;
        }
        else if(second - first == 1)
        {
            for(buff = *Stations; buff->next != gFirst; buff = buff->next);
            buff->next = gSecond;
            buff2 = gSecond->next;
            gSecond->next = gFirst;
            gFirst->next = buff2;
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
        }
    }
    system("pause");
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
        buff = first;
        for(f = 1;buff != NULL && f;)
        {
            if(PrepareStruct(buff))
            {
                system("cls");
                puts("Введите название АЗС");
                InputText(buff->name);
                puts("\nВведите адрес");
                InputText(buff->address);
                puts("\nВведите цены на топливо(92,95,98,Дизель). Цена не выше 10000");
                for(i = 0; i < 4; i++)
                {
                    do
                    {
                        scanf("%f", &(buff->fuelPrices[i]));
                        if(buff->fuelPrices[i] < 1.0 || buff->fuelPrices[i] > 10000.0) puts("Цена от 1 до 10000");
                    } while(buff->fuelPrices[i] < 1.0 || buff->fuelPrices[i] > 10000.0);
                }
                puts("Введите рейтинг АЗС от 1 до 10");
                do
                {
                    scanf("%d", &(buff->rating));
                    if(buff->rating < 1 || buff->rating > 10) puts("Рейтинг от 1 до 10!");
                } while(buff->rating < 1 || buff->rating > 10);
                puts("Введите количество сотрудников");
                do
                {
                    scanf("%d", &(buff->stuff));
                    if(buff->stuff < 1 || buff->stuff > 1000000) puts("Кол-во сотрудников от 1 до 1000000");
                } while(buff->stuff < 1 || buff->stuff > 1000000);
                puts("Если хотите продолжить ввод данных, введите любое число, отличное от нуля");
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
    printf("|%*s|%*s|Цена 92 бензина|Цена 95 бензина|Цена 98 бензина|Цена дизеля|Рейтинг|Сотрудников|\n", namelen, "Название", addresslen, "Адрес");
	for(buff = first; buff != NULL; buff = buff->next)
		printf("|%*s|%*s|%15.2f|%15.2f|%15.2f|%11.2f|%7d|%11d|\n", namelen, buff->name, addresslen, buff->address,
         buff->fuelPrices[0], buff->fuelPrices[1], buff->fuelPrices[2], buff->fuelPrices[3], buff->rating, buff->stuff);
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
        printf("\nКоличество сотрудников: %d", buff->stuff);
        printf("\n\n");
    }
    system("pause");
}
//------------------------------------------------------ПАМЯТЬ------------------------------------------------------
int PrepareStruct(GSDesc* first)
{
    int res = 0,
        i;
    if(first != NULL)
    {
        first->name = (char*)malloc((MAXLEN+1)*sizeof(char));
        first->address = (char*)malloc((MAXLEN+1)*sizeof(char));
        for(i = 0; i < 4; i++) first->fuelPrices[i] = 0;
        first->rating = 0;
        first->stuff = 0;
        first->next = NULL;
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
        //free(Station->next); тут проблема
        Station->next = NULL;
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
        ThisStation->stuff = OtherStation->stuff;
    }
}
