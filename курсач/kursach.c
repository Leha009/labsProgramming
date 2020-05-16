#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <locale.h>
#include <string.h>

#define MAXLEN 80
#define DBG puts("DBG");

typedef struct Gaslist
{
    char* name;                                 //Название
    char* address;                              //Адрес
    float fuelPrices[4];                        //Ниже цены на топливо(92,95,98,дизель)
    int rating;                                 //Рейтинг АЗС(1-10)
    struct Gaslist* next;                       //Ссылка на следующую структуру
    struct Gaslist* prev;                       //Ссылка на предыдущую структуру
} GSDesc;

/*----------------------------ФУНКЦИИ------------------------------*/
int Menu();                                     //Меню
int ListActions();                              //Действия со списком
void OutputMenu(GSDesc*);                       //Меню вывода
GSDesc* InputMenu(GSDesc*);                     //Меню выбора ввода
void Help();                                    //Справка

int ListLen(GSDesc*);                           //Длина списка
GSDesc* DeleteItem(GSDesc*);                    //Удаление элемента из списка
GSDesc* Sort(GSDesc*);                          //Сортировка по полю
void Swap(GSDesc**);                            //Поменять местами 2 элемента
void GetItem(GSDesc*);                          //Вывод АЗС по заданным параметрам

GSDesc* PushBack(GSDesc*, GSDesc*);             //Добавление в конец
GSDesc* PushForward(GSDesc*, GSDesc*);          //Добавление в начало
GSDesc* PushAnyPlace(GSDesc*);                  //Добавление в любое место
GSDesc* InputStations();                        //Ввод данных об АЗС
GSDesc* Process(GSDesc*);                       //Обработка данных

int PrepareStruct(GSDesc*);                     //Выделение памяти для полей структуры
void CopyStruct(GSDesc*, GSDesc*);              //Копирование структуры

void OutputGasStationsTable(GSDesc*);           //Вывод информации в виде таблицы
void OutputGasStationsText(GSDesc*);            //Вывод информации в виде текста
void OutputGasStationsTableReverse(GSDesc*);    //Вывод информации в виде таблицы с конца
void OutputGasStationsTextReverse(GSDesc*);     //Вывод информации в виде текста с конца

GSDesc* InputTextFile(GSDesc*);                 //Ввод текста с файла
GSDesc* fillStruct(char* string);               //Заполняем структуры из данных файла
void OutputFile(GSDesc*);                       //Вывод в файл

GSDesc* free_station(GSDesc*);                  //Освобождение памяти одной АЗС
GSDesc* free_list(GSDesc*);                     //Освобождение памяти списка АЗС
/*-----------------------------------------------------------------*/
int main()
{
    setlocale(LC_ALL, "russian");
    GSDesc*    First = NULL;                    //Начало списка
    GSDesc*    GResult = NULL;                  //Начало списка результата
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
                    puts("Нет данных для вывода, список пуст!");
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
                                printf("Количество элементов в списке: %d\n",len);
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
                    puts("Сначала введите список АЗС!");
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
                    puts("Сначала введите список АЗС!");
                    system("pause");
                }
                break;
            case 6:
                if(GResult != NULL) OutputMenu(GResult);
                else
                {
                    puts("Не была обработана информация, либо ни одна АЗС не удовлетворяет условиям!");
                    system("pause");
                }
                break;
        }
    } while(MenuItem);
    First = free_list(First);
    GResult = free_list(GResult);
    return 0;
}
//------------------------------------------------------МЕНЮ------------------------------------------------------
int Menu()
{
    system("cls");
    int selected;
    puts("****************МЕНЮ****************");
    puts("1 - Справка");
    puts("2 - Ввод информации об АЗС");
    puts("3 - Вывод информации об АЗС");
    puts("4 - Действия над списком АЗС");
    puts("5 - Обработка данных");
    puts("6 - Вывод данных");
    puts("0 - Выход");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 6) puts("Данного пункта меню не существует");
    } while(selected < 0 || selected > 6);
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
    puts("3 - Поменять местами элементы списка АЗС");
    puts("4 - Сортировка элементов списка АЗС по рейтингу(по убыв.)");
    puts("5 - Поиск АЗС по определенному критерию");
    puts("6 - Назад");
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
        puts("3 - В виде таблицы, начиная с конца");
        puts("4 - В виде текста, начиная с конца");
        puts("5 - В файл");
        puts("0 - Назад");
        do
        {
            scanf("%d", &item);
            if(item < 0 || item > 5) puts("Данного пункта меню не существует");
        } while(item < 0 || item > 5);
        fflush(stdin);
        if(item == 1) OutputGasStationsTable(first);
        else if(item == 2) OutputGasStationsText(first);
        else if(item == 3) OutputGasStationsTableReverse(first);
        else if(item == 4) OutputGasStationsTextReverse(first);
        else if(item == 5) OutputFile(first);
    }while(item);
}

GSDesc* InputMenu(GSDesc* Stations)                       //Меню выбора ввода
{
    system("cls");
    GSDesc* NewStations = NULL;
    int item;
    do
    {
        system("cls");
        puts("****************Ввод****************");
        puts("1 - Добавить в начало");
        puts("2 - Добавить в конец");
        puts("3 - Добавить на определенное место");
        puts("4 - Ввести полностью заново");
        puts("5 - Получить данные из файла");
        puts("6 - Назад");
        do
        {
            scanf("%d", &item);
            if(item < 0 || item > 6) puts("Данного пункта меню не существует");
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
    puts("  Данная программа расчитана для работы над списком АЗС,");
    puts("имеющий следующую структуру: название, адрес, цены на топливо и рейтинг");
    puts("  Пункт 'обработка' подразумевает под собой отбор тех АЗС,");
    puts("которые удовлетворяют следующим условиям:");
    puts("рейтинг выше 7, цена на 98 бензин ниже 54");
    puts("  Также Вам доступны следующие действия над списком:");
    puts("узнать кол-во АЗС в списке, удалить одну АЗС из списка,");
    puts("поменять местами 2 АЗС в списке, отсортировать по убыванию рейтинга");
    puts("(при сортировке изменяется ИЗНАЧАЛЬНЫЙ список, будьте внимательны!)");
    puts("поиск АЗС по определенному параметру\n");
    puts("  Внимание! Кол-во букв в названии и адресе не могут превышать 80!\n");
    system("pause");
}
//------------------------------------------------------ДЕЙСТВИЯ СО СПИСКОМ------------------------------------------------------
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
    printf("Введите номер элемента, который хотите удалить(всего %d элементов): ", ListLen(Stations));
    do
    {
        scanf("%d", &num);
        if(num < 1 || num > ListLen(Stations)) printf("Элемента под таким номером нет. Введите от 1 до %d\n", ListLen(Stations));
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

GSDesc* Sort(GSDesc* Stations)                  //Сортировка
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
    puts("Выберете поле для сортировки\n1 - цена на 92 бензин, 2 - цена на 95 бензин, 3 - цена на 98 бензин, 4 - цена на дизель, 5 - рейтинг");
    do
    {
        scanf("%d", &field);
        if(field < 1 || field > 5) puts("Такого номера поля нет!");
    } while(field < 1 || field > 5);
    puts("Выберете режим сортировки:\n1 - по возрастанию, 2 - по убыванию");
    do
    {
        scanf("%d", &mode);
        if(mode < 1 || mode > 2) puts("Такого номера режима нет!");
    } while(mode < 1 || mode > 2);
    mode--; field--;
    if(mode)        //убывание
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
    if(result == NULL) puts("Упс... Что-то пошло не так! Попробуйте еще раз!");
    else puts("Сортировка прошла успешно!");
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
    puts("Выберете категорию, по которой мы ищем");
    puts("1 - Цена на топливо");
    puts("2 - Рейтинг");
    puts("3 - Отмена");
    do
    {
        scanf("%d", &ans);
        if(ans < 1 || ans > 3) puts("Введите от 1 до 3");
    } while(ans < 1 || ans > 3);
    if(ans == 1)
    {
        puts("\nВыберете, по цене какого топлива будем искать\n1 - 92 бензин\n2 - 95 бензин\n3 - 98 бензин\n4 - Дизель");
        do
        {
            scanf("%d", &num);
            if(num < 1 || num > 4) puts("Введите от 1 до 4");
        } while(num < 1 || num > 4);
        printf("\nВведите цену, по которой будем искать: ");
        do
        {
            scanf("%f", &price);
            if(price < 0) puts("Цена должна быть выше 0!");
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
        printf("Введите рейтинг, по которому будем искать(от 1 до 10): ");
        do
        {
            scanf("%d", &num);
            if(num < 1 || num > 10) puts("Рейтинг должен быть от 1 до 10!");
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
            puts("Ничего не найдено!"), system("pause");
    result = free_list(result);
}

GSDesc* Process(GSDesc* Stations)                     //Обработка данных
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
    if(result == NULL) puts("Ни одна АЗС не подходит под критерии");
    else puts("Обработка прошла успешно!");
    system("pause");
    return result;
}

GSDesc* PushForward(GSDesc* NewStations, GSDesc* Stations)                     //Добавление в начало
{
    GSDesc* connector = NULL;
    NewStations->prev = NULL;
    for(connector = NewStations ; connector->next != NULL ; connector = connector->next);
    connector->next = Stations;
    if(Stations != NULL) Stations->prev = connector;
    return NewStations;
}

GSDesc* PushBack(GSDesc* NewStations, GSDesc* Stations)                    //Добавление в конец
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

GSDesc* PushAnyPlace(GSDesc* Stations)                  //Добавление в любое место
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
    printf("Введите номер места, на которое хотите добавить новые АЗС(от 1 до %d)\n", len+1);
    do
    {
        scanf("%d", &ans);
        if(ans < 1 || ans > len+1) printf("Введите от 1 до %d\n", len+1);
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

void Swap(GSDesc** Stations)                             //Поменять местами 2 элемента
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
                puts("Если хотите продолжить ввод данных, введите любое число, отличное от нуля");
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
        linebeg;    //индекс начала очередной строки
    puts("Хотите указать свое имя файла? Введите любое число, отличное от нуля\nИначе будет использован файл in.txt");
    scanf("%d", &ans);
    fflush(stdin);
    if(ans)
    {
        puts("\nВведите имя файла для чтения. Имя файла не должно превышать 128 символов!");
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
            puts("Файл пуст!");
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
                puts("Список заполнен!");
            }
            else
                puts("Все строки пустые!");
        }
        free(text);
        text = NULL;
    }
    else puts("Не удалось открыть файл с таким именем!");
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
    printf("|%*s|%*s|Цена 92 бензина|Цена 95 бензина|Цена 98 бензина|Цена дизеля|Рейтинг|\n", namelen, "Название", addresslen, "Адрес");
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
        printf("Название: %s", buff->name);
        printf("\nАдрес: %s", buff->address);
        printf("\nЦены(92,95,98,Дизель): ");
        for(i = 0; i < 4; i++) printf("%.2f ", buff->fuelPrices[i]);
        printf("\nРейтинг: %d", buff->rating);
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
    puts("Хотите указать имя файла самостоятельно? Введите любое число, отличное от нуля.\nВ противном случае все сохранится в out.txt");
    scanf("%d", &ans);
    fflush(stdin);
    if(ans)
    {
        puts("Введите имя файла для сохранения");
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
    fprintf(file, "|%*s|%*s|Цена 92 бензина|Цена 95 бензина|Цена 98 бензина|Цена дизеля|Рейтинг|\n", namelen, "Название", addresslen, "Адрес");
	for(buff = first; buff != NULL; buff = buff->next)
		fprintf(file, "|%*s|%*s|%15.2f|%15.2f|%15.2f|%11.2f|%7d|\n", namelen, buff->name, addresslen, buff->address,
         buff->fuelPrices[0], buff->fuelPrices[1], buff->fuelPrices[2], buff->fuelPrices[3], buff->rating);
    fclose(file);
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
