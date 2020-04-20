#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <locale.h>
#include <string.h>

#define MAXLEN 80

typedef struct
{
    char* name;                         //Название
    char* address;                      //Адрес
    float* fuelPrices;                 //Ниже цены на топливо(92,95,98,дизель)
    int* rating;                        //Рейтинг АЗС(1-10)
    int* stuff;                         //Кол-во сотрудников
} GSDesc;
/*----------------------------ФУНКЦИИ------------------------------*/
int Menu();                                     //Меню
void OutputMenu(GSDesc*, int);                  //Подменю вывода, int - кол-во элементов
void Info();                                    //Справка
void OutputGasStationsTable(GSDesc*, int);      //Вывод информации в виде таблицы, int - кол-во элементов
void OutputGasStationsText(GSDesc*, int);       //Вывод информации в виде текста, int - кол-во элементов
void InputInfo(GSDesc);                         //Ввод элементов
void InputText(char*);                          //Ввод строки
GSDesc* Process(GSDesc*, int, int*);            //Обработка данных
int PrepareStruct(GSDesc*);                     //Выделение памяти для полей структуры
void free_struct(GSDesc*, int);                 //Освобождение памяти
/*-----------------------------------------------------------------*/
int main()
{
    setlocale(LC_ALL, "russian");
    GSDesc  *GasStations = NULL,       //АЗС
            *GSResult = NULL;          //Результат отбора
    int i = 0,                          //Кол-во АЗС
        ri = 0,                         //Кол-во АЗС после обработки
        MenuItem;                       //Выбранный пункт меню
    do
    {
        MenuItem = Menu();
        switch(MenuItem)
        {
            case 1:
                Info();
                break;
            case 2:
                GasStations = (GSDesc*)realloc(GasStations, (i+1)*sizeof(GSDesc));
                if(GasStations != NULL)
                {
                    if(PrepareStruct(GasStations+i))
                    {
                        InputInfo(GasStations[i]);
                        i++;
                    }
                }
                break;
            case 3:
                if(GasStations != NULL) OutputMenu(GasStations, i);
                else
                {
                    puts("Не была введена информация об АЗС");
                    system("pause");
                }
                break;
            case 4:
                if(GasStations != NULL)
                {
                    free_struct(GSResult, ri);
                    ri = 0;
                    GSResult = Process(GasStations, i, &ri);
                }
                else puts("Не была введена информация об АЗС"),system("pause");
                break;
            case 5:
                if(GSResult != NULL) OutputMenu(GSResult, ri);
                else
                {
                    puts("Введенная информация не обработана, либо ни одна АЗС не подходит под указанные условия");
                    system("pause");
                }
                break;
        }
    } while(MenuItem);
    free_struct(GasStations, i);
    free_struct(GSResult, ri);
    return 0;
}

void InputInfo(GSDesc Station)
{
    system("cls");
    int i;
    puts("Введите название АЗС: ");
    InputText(Station.name);
    puts("\nВведите адрес: ");
    InputText(Station.address);
    printf("\nВведите цены на топливо(92,95,98,дизель): ");
    for(i = 0; i < 4; i++)
    {
        do
        {
            scanf("%f", Station.fuelPrices+i);
            if(Station.fuelPrices[i] < 1 || Station.fuelPrices[i] > 10000) puts("1-10000");
        } while(Station.fuelPrices[i] < 1 || Station.fuelPrices[i] > 10000);
    }
    printf("Введите рейтинг АЗС: ");
    do
    {
        scanf("%d", Station.rating);
        if(*(Station.rating) < 1 || *(Station.rating) > 10) puts("1-10");
    } while(*(Station.rating) < 1 || *(Station.rating) > 10);
    printf("Введите количество сотрудников: ");
    do
    {
        scanf("%d", Station.stuff);
        if(*(Station.stuff) < 1 || *(Station.stuff) > 1000000) puts("1-1000000");
    } while(*(Station.stuff) < 1 || *(Station.stuff) > 1000000);
    system("pause");
}

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

void OutputGasStationsTable(GSDesc* GasStations, int lines)
{
    system("cls");
    int i,
        namelen,
        addresslen;
    namelen = 0, addresslen = 0;
    for(i = 0; i < lines; i++)
    {
        if(strlen(GasStations[i].name) > namelen) namelen = strlen(GasStations[i].name);
        if(strlen(GasStations[i].address) > addresslen) addresslen = strlen(GasStations[i].address);
    }
    if(namelen < 8) namelen = 8;
    if(addresslen < 5) addresslen = 5;
    printf("|%*s|%*s|Цена 92 бензина|Цена 95 бензина|Цена 98 бензина|Цена дизеля|Рейтинг|Сотрудников|\n", namelen, "Название", addresslen, "Адрес");
	for(i = 0; i < lines; i++)
		printf("|%*s|%*s|%15.2f|%15.2f|%15.2f|%11.2f|%7d|%11d|\n", namelen, GasStations[i].name, addresslen, GasStations[i].address,
         GasStations[i].fuelPrices[0], GasStations[i].fuelPrices[1], GasStations[i].fuelPrices[2], GasStations[i].fuelPrices[3], *(GasStations[i].rating), *(GasStations[i].stuff));
    system("pause");
}

void OutputGasStationsText(GSDesc* GasStations, int lines)
{
    system("cls");
    int i,
        j;
    for(i = 0; i < lines; i++)
    {
        printf("Название: %s", GasStations[i].name);
        printf("\nАдрес: %s", GasStations[i].address);
        printf("\nЦены(92,95,98,Дизель): ");
        for(j = 0; j < 4; j++) printf("%.2f ", GasStations[i].fuelPrices[j]);
        printf("\nРейтинг: %d", *(GasStations[i].rating));
        printf("\nКоличество сотрудников: %d", *(GasStations[i].stuff));
        printf("\n\n");
    }
    system("pause");
}

GSDesc* Process(GSDesc* GasStations, int lines, int* rlines)
{
    GSDesc* result = NULL;
    int i,
        j = 0,
        k;
    for(i = 0; i < lines; i++)
        if(*(GasStations[i].rating) > 7 && GasStations[i].fuelPrices[2] < 54.0)
        {
            result = (GSDesc*)realloc(result, (j+1)*sizeof(GSDesc));
            if(PrepareStruct(result+j))
            {
                //printf("%p %p\n%p %p\nBLA BLA\n", result[j].name, GasStations[i].name, result[j].address, GasStations[i].address);
                strcpy(result[j].name, GasStations[i].name);
                strcpy(result[j].address, GasStations[i].address);
                for(k = 0; k < 4; k++)
                    result[j].fuelPrices[k] = GasStations[i].fuelPrices[k];
                *(result[j].rating) = *(GasStations[i].rating);
                *(result[j].stuff) = *(GasStations[i].stuff);
                //result[j] = GasStations[i];
                //printf("%p %p\n%p %p\n", result[j].name, GasStations[i].name, result[j].address, GasStations[i].address);
                j++;
            }
        }
    *rlines = j;
    if(result == NULL) puts("Нет АЗС, удовлетворяющим поставленным условиям");
    else puts("Обработка прошла успешно");
    system("pause");
    return result;
}

int PrepareStruct(GSDesc* Station)
{
    int res = 0;
    if(Station != NULL)
    {
        Station->name = (char*)malloc((MAXLEN+1)*sizeof(char));
        Station->address = (char*)malloc((MAXLEN+1)*sizeof(char));
        Station->fuelPrices = (float*)malloc(4*sizeof(float));
        Station->rating = (int*)malloc(sizeof(int));
        Station->stuff = (int*)malloc(sizeof(int));
        res++;
    }
    return res;
}
//------------------------------------------------Меню и справка---------------------------------------------
int Menu()
{
    system("cls");
    int selected;
    puts("****************МЕНЮ****************");
    puts("1 - Справка");
    puts("2 - Ввод информации об АЗС");
    puts("3 - Контрольный вывод введенной информации");
    puts("4 - Обработка информации");
    puts("5 - Вывод обработанной информации");
    puts("0 - Выход");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 5) puts("Данного пункта меню не существует");
    } while(selected < 0 || selected > 5);
    fflush(stdin);
    return selected;
}

void OutputMenu(GSDesc* GasStations, int lines)
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
        if(item == 1) OutputGasStationsTable(GasStations, lines);
        else if(item == 2) OutputGasStationsText(GasStations, lines);
    }while(item);
}

void Info()
{
    system("cls");
    puts("Условия обработки: рейтинг выше 7, цена на 98 бензин ниже 54");
    system("pause");
}

void free_struct(GSDesc* Stations, int lines)
{
    if(Stations != NULL)
    {
        int i;
        for(i = 0; i < lines; i++)
        {
            free(Stations[i].name);
            Stations[i].name = NULL;
            free(Stations[i].address);
            Stations[i].address = NULL;
            free(Stations[i].fuelPrices);
            Stations[i].fuelPrices = NULL;
            free(Stations[i].rating);
            Stations[i].rating = NULL;
            free(Stations[i].stuff);
            Stations[i].stuff = NULL;
            free(Stations+i);
        }
        Stations = NULL;
    }
}
