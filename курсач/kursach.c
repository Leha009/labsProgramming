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
    struct Gaslist* prev;                       //Ссылка на предыдущую структуру
} GSDesc;

/*----------------------------ФУНКЦИИ------------------------------*/
int Menu();                                     //Меню+
int ListActions();                              //Действия со списком+
void OutputMenu(GSDesc*);                       //Меню вывода+
GSDesc* InputMenu(GSDesc*);                     //Меню выбора ввода+
void Help();                                    //Справка+

int ListLen(GSDesc*);                           //Длина списка+
GSDesc* DeleteItem(GSDesc*, int);               //Удаление элемента из списка+
void Sort(GSDesc**, int, int);                  //Сортировка по полю+
void Swap(GSDesc*, int, int);                   //Поменять местами 2 элемента+
void GetItem(GSDesc*, int);                     //Вывод АЗС по заданным параметрам+
void EditItem(GSDesc*, int);                    //Изменение элемента    СДЕЛАТЬ
GSDesc* ReverseList(GSDesc*);                   //Реверс списка+

GSDesc* PushBack(GSDesc*, GSDesc*);             //Добавление в конец+
GSDesc* PushForward(GSDesc*, GSDesc*);          //Добавление в начало+
GSDesc* PushAnyPlace(GSDesc*);                  //Добавление в любое место+
GSDesc* InputStations();                        //Ввод данных об АЗС+
GSDesc* Process(GSDesc*);                       //Обработка данных+

int PrepareStruct(GSDesc*);                     //Выделение памяти для полей структуры+
void CopyStruct(GSDesc*, GSDesc*);              //Копирование структуры+

void OutputGasStationsTable(GSDesc*);           //Вывод информации в виде таблицы+
void OutputGasStationsText(GSDesc*);            //Вывод информации в виде текста+
void OutputGasStationsTableReverse(GSDesc*);    //Вывод информации в виде таблицы с конца+
void OutputGasStationsTextReverse(GSDesc*);     //Вывод информации в виде текста с конца+

void InputText(char*);                          //Ввод строки+
GSDesc* InputTextFile();                        //Ввод текста с файла+
GSDesc* fillStruct(char* string);               //Заполняем структуры из данных файла+
void OutputFile(GSDesc*);                       //Вывод в файл+

GSDesc* free_station(GSDesc*);                  //Освобождение памяти одной АЗС+
GSDesc* free_list(GSDesc*);                     //Освобождение памяти списка АЗС+
/*-----------------------------------------------------------------*/
int main()
{
    setlocale(LC_ALL, "russian");
    GSDesc*    First = NULL;                    //Начало списка
    GSDesc*    GResult = NULL;                  //Начало списка результата
    int MenuItem,                               //Пункт меню
        len,                                    //Длина списка
        field,                                  //Поле поиска
        index1,                                 //Индекс первого элемента для смены
        index2,                                 //Индекс второго элемента для смены
        mode;                                   //Режим сортировки
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
                        len = ListLen(First);
                        MenuItem = ListActions();
                        switch(MenuItem)
                        {
                            case 1:
                                printf("Количество элементов в списке: %d\n",len);
                                system("pause");
                                break;
                            case 2: //удалить
                                system("cls");
                                printf("Введите номер элемента, который хотите удалить(всего %d элементов): ", len);
                                do
                                {
                                    scanf("%d", &index1);
                                    if(index1 < 1 || index1 > len)
                                        puts("Нет элемента под таким номером");
                                } while(index1 < 1 || index1 > len);
                                First = DeleteItem(First, index1);
                                break;
                            case 3: //поменять местами
                                system("cls");
                                printf("Введите два номера элементов для перестановки(от 1 до %d): ", len);
                                do
                                {
                                    scanf("%d %d", &index1, &index2);
                                    if(index1 < 1 || index1 > len || index2 < 1 || index2 > len)
                                        printf("Введенные номера должны быть от 1 до %d!\n", len);
                                } while(index1 < 1 || index1 > len || index2 < 1 || index2 > len);
                                Swap(First, index1, index2);
                                break;
                            case 4: //сортировка
                                system("cls");
                                puts("Выберете поле для сортировки:\n1 - название, 2 - адрес, 3 - цена на 92 бензин,4 - цена на 95 бензин\n5 - цена на 98 бензин, 6 - цена на дизель, 7 - рейтинг");
                                do
                                {
                                    scanf("%d", &field);
                                    if(field < 1 || field > 7) puts("Поля с таким номером нет!");
                                } while(field < 1 || field > 7);
                                puts("Режим сортировки: 1 - по возрастанию, 2 - по убыванию");
                                do
                                {
                                    scanf("%d", &mode);
                                    if(mode < 1 || mode > 2) puts("Режима с таким номером нет!");
                                } while(mode < 1 || mode > 2);
                                mode--;
                                Sort(&First, field, mode);
                                break;
                            case 5: //поиск
                                system("cls");
                                puts("Выберете поле для поиска:\n1 - название, 2 - адрес, 3 - цена на 92 бензин,4 - цена на 95 бензин\n5 - цена на 98 бензин, 6 - цена на дизель, 7 - рейтинг\n0 - искать везде");
                                do
                                {
                                    scanf("%d", &field);
                                    if(field < 0 || field > 7) puts("Поля с таким номером нет!");
                                } while(field < 0 || field > 7);
                                GetItem(First, field);
                                break;
                            case 6: //изменение
                                system("cls");
                                printf("Введите номер элемента, который хотите изменить(от 1 до %d): ", len);
                                do
                                {
                                    scanf("%d", &index1);
                                    if(index1 < 1 || index1 > len)
                                        printf("Введенный номер должен быть от 1 до %d!\n", len);
                                } while(index1 < 1 || index1 > len);
                                EditItem(First, index1);
                                break;
                        }
                    } while(MenuItem != 0);
                    if(MenuItem == 0) MenuItem = 1284;
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
    puts("6 - Изменить данные АЗС");
    puts("0 - Назад");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 6) puts("Данного пункта меню не существует");
    } while(selected < 0 || selected > 6);
    fflush(stdin);
    return selected;
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
        puts("0 - Назад");
        do
        {
            scanf("%d", &item);
            if(item < 0 || item > 5) puts("Данного пункта меню не существует");
        } while(item < 0 || item > 5);
        fflush(stdin);
        if(item > 0 && item < 3) NewStations = InputStations();
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
            Stations = InputTextFile();
        }
    }while(item != 0);
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
    puts("поменять местами 2 АЗС в списке, отсортировать список");
    puts("(при сортировке изменяется ИЗНАЧАЛЬНЫЙ список, будьте внимательны!)");
    puts("поиск АЗС по определенному параметру, изменение данных одной АЗС\n");
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

GSDesc* DeleteItem(GSDesc* Stations, int index)
{
    system("cls");
    GSDesc* temp = Stations;
    GSDesc* toDel = NULL;
    if(index == 1)
    {
        Stations = Stations->next;
        if(Stations) Stations->prev = NULL;
        temp = free_station(temp);
    }
    else
    {
        toDel = temp->next;
        while(index > 2)
        {
            temp = temp->next;
            toDel = temp->next;
            index--;
        }
        temp->next = toDel->next;
        if(temp->next) temp->next->prev = temp;
        toDel = free_station(toDel);
    }
    return Stations;
}

void Sort(GSDesc** Stations, int field, int mode)                  //Сортировка: адрес, название, цена на 92,95,98,дизель, рейтинг
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
    if(mode)        //убывание
        *Stations = ReverseList(*Stations);
    puts("Сортировка прошла успешно!");
    system("pause");
}

GSDesc* ReverseList(GSDesc* First)
{
    GSDesc* result = NULL;
    GSDesc* buff = NULL;
    GSDesc* buffThis = NULL;
	for(buffThis = First; buffThis->next != NULL; buffThis = buffThis->next);
	for(; buffThis != NULL; buffThis = buffThis->prev)
	{
        if(result == NULL)
        {
            result = (GSDesc*)malloc(sizeof(GSDesc));
            buff = result;
            PrepareStruct(buff);
            CopyStruct(buff, buffThis);
            buff->prev = NULL;
        }
        else
        {
            buff->next = (GSDesc*)malloc(sizeof(GSDesc));
            buff->next->prev = buff;
            buff = buff->next;
            PrepareStruct(buff);
            CopyStruct(buff, buffThis);
        }
	}
    return result;
}

void GetItem(GSDesc* Stations, int field)       //Поиск: 1: адрес, 2: название, 3-6: цена на 92,95,98,дизель, 7: рейтинг, -1: все
{
    system("cls");
    GSDesc* result = NULL;
    GSDesc* buff = NULL;
    GSDesc* buffThis = NULL;
    char* string = NULL;
    string = (char*)malloc((MAXLEN+1)*sizeof(char));
    puts("Введите, какое значение будем искать");
    InputText(string);
    puts("");
    for(buffThis = Stations; buffThis != NULL; buffThis = buffThis->next)
    {
        if( ((field == 0 || field == 1) && !strcmp(string,buffThis->name)) || ((field == 0 || field == 2) && !strcmp(string,buffThis->address)) || ((field == 0 || field == 3) && atof(string) == buffThis->fuelPrices[0]) || ((field == 0 || field == 4) && atof(string) == buffThis->fuelPrices[1])  || ((field == 0 || field == 5) && atof(string) == buffThis->fuelPrices[2]) || ((field == 0 || field == 6) && atof(string) == buffThis->fuelPrices[3]) || ((field == 0 || field == 7) && atoi(string) == buffThis->rating) )
        {
            if(result == NULL)
            {
                result = (GSDesc*)malloc(sizeof(GSDesc));
                buff = result;
                PrepareStruct(buff);
                CopyStruct(buff, buffThis);
                buff->prev = NULL;
            }
            else
            {
                buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                buff->next->prev = buff;
                buff = buff->next;
                PrepareStruct(buff);
                CopyStruct(buff, buffThis);
            }
        }
    }
    if(result != NULL) OutputMenu(result);
    else
        puts("Ничего не найдено!"), system("pause");
    result = free_list(result);
}

void EditItem(GSDesc* Stations, int index)
{
    GSDesc* buff = Stations;
    int i;
    for(i = 1; i < index; i++, buff = buff->next)
    system("cls");
    printf("Введите название АЗС. Текущее название: %s\n", buff->name);
    InputText(buff->name);
    printf("\nВведите адрес. Текущий адрес: %s\n", buff->address);
    InputText(buff->address);
    puts("\nВведите цены на топливо(92,95,98,Дизель). Цена не выше 10000");
    printf("Текущие значения: %.2f %.2f %.2f %.2f\n", buff->fuelPrices[0], buff->fuelPrices[1], buff->fuelPrices[2], buff->fuelPrices[3]);
    for(i = 0; i < 4; i++)
    {
        do
        {
            scanf("%f", &(buff->fuelPrices[i]));
            if(buff->fuelPrices[i] < 1.0 || buff->fuelPrices[i] > 10000.0) puts("Цена от 1 до 10000");
        } while(buff->fuelPrices[i] < 1.0 || buff->fuelPrices[i] > 10000.0);
    }
    printf("Введите рейтинг АЗС от 1 до 10. Текущий рейтинг: %d\n", buff->rating);
    do
    {
        scanf("%d", &(buff->rating));
        if(buff->rating < 1 || buff->rating > 10) puts("Рейтинг от 1 до 10!");
    } while(buff->rating < 1 || buff->rating > 10);
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
                PrepareStruct(buff);
                CopyStruct(buff, Stations);
                buff->prev = NULL;
            }
            else
            {
                buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                buff->next->prev = buff;
                buff = buff->next;
                PrepareStruct(buff);
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

void Swap(GSDesc* Stations, int first, int second)                             //Поменять местами 2 элемента
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

GSDesc* InputTextFile()
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
                        buff->next->prev = buff;
                        buff = buff->next;
                    }
                    else
                    {
                        newFirst = fillStruct(string);
                        buff = newFirst;
                        buff->prev = NULL;
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
    char empty[] = "Unknown\0";
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
                if(atof(buff[2+i]) > 0)
                   result->fuelPrices[i] = atof(buff[2+i]);
                else
                    result->fuelPrices[i] = 0.0;
            else
                result->fuelPrices[i] = 0.0;
        }
        if(buffi > 6)
            if(atoi(buff[6]) > 0 && atoi(buff[6]) < 11)
                result->rating = atoi(buff[6]);
            else if(atoi(buff[6]) > 0 && atoi(buff[6]) > 10)
                result->rating = 10;
            else
                result->rating = 0;
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
    strcpy(ThisStation->name, OtherStation->name);
    strcpy(ThisStation->address, OtherStation->address);
    for(i = 0; i < 4; i++)
        ThisStation->fuelPrices[i] = OtherStation->fuelPrices[i];
    ThisStation->rating = OtherStation->rating;
}
