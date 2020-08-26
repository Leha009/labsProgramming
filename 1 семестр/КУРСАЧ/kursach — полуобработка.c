//Сделать
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

#define MAX_LEN 80
//--------------------------------------------МЕНЮ И ПОДМЕНЮ--------------------------------------------

int Menu();
int InputData();                            //Ввод
int CheckData();                            //Контрольный вывод
void Help();                                //Справка

//--------------------------------------------Ввод данных--------------------------------------------

char* GenerateDelimiterArray();             //Ввод разделителей
char* InputKeyWord();                       //Ввод слова
char** InputTextConsole(int*, char*);       //Ввод текста с консоли
char** InputTextFile(int*);                 //Ввод текста с файла

//--------------------------------------------Вывод данных--------------------------------------------

void ShowDelimiters(char*);                 //Вывод разделителей
void ShowKeyWord(char*);                    //Вывод заданного слова
void ShowTextConsole(char**, int);          //Вывод текста
void SaveResult(char**, int);               //Сохр рещультата

//--------------------------------------------ОЧИСТКА ПАМЯТИ--------------------------------------------

char* free_str(char*);                      //Освоб. память для строки
char** free_text(char**, int);              //Освоб. память для текста

//--------------------------------------------ВСЕ ДЛЯ ОБРАБОТКИ--------------------------------------------

int AmountOfWords(char*, char*);            //Счетчик кол-ва слов
int IsDelimiter(char, char*);               //Проверка на разделитель
char** ProcessText(char**, int, char*, char*);       //Обработка текста

//--------------------------------------------ПРОГРАММА--------------------------------------------

int main()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char **text = NULL,                     //Текст
         *delims = NULL,                    //разделители
         *keyword = NULL,                   //Слово
         **result = NULL;                   //Результат
    int DelAmount,                          //Кол-во
        AItems,                             //Доступность пунктов меню
        selected,                           //Выбранный пункт
        textrows;
    AItems = 2; textrows = 0;
    do
    {
        system("cls");
        selected = Menu();
        switch(selected)
        {
            case 1:
                Help();
                break;
            case 2:
                selected = InputData();
                switch(selected)
                {
                    case 1:
                        free_str(delims);
                        delims = GenerateDelimiterArray();
                        break;
                    case 2:
                        free_str(keyword);
                        keyword = InputKeyWord();
                        break;
                    case 3:
                        free_text(text, textrows);
                        text = InputTextConsole(&textrows, delims);
                        break;
                    case 4:
                        free_text(text, textrows);
                        text = InputTextFile(&textrows);
                        break;
                    case 5:
                        system("cls");
                        puts("Возвращение в главное меню");
                        system("pause");
                        break;
                    default:
                        puts("Неверный пункт меню. Выберете пункт меню еще раз.");
                        system("pause");
                }
                break;
            case 3:
                selected = CheckData();
                switch(selected)
                {
                    case 1:
                        ShowDelimiters(delims);
                        break;
                    case 2:
                        ShowKeyWord(keyword);
                        break;
                    case 3:
                        ShowTextConsole(text, textrows);
                        break;
                    case 4:
                        system("cls");
                        puts("Возвращение в меню");
                        system("pause");
                        break;
                    default:
                        puts("Неверный пункт меню. Выберете пункт меню еще раз.");
                        system("pause");
                }
                break;
            case 4:
                //Обработка
                result = ProcessText(text, textrows, keyword, delims);
                break;
            case 5:
                //Вывод результата
                SaveResult(result, textrows);
                break;
            case 0:
                break;
            default:
                puts("Неверный пункт меню. Выберете пункт меню еще раз.");
                system("pause");
        }
    } while(selected != 0);
    delims = free_str(delims);
    text = free_text(text, textrows);
    return 0;
}

//--------------------------------------------МЕНЮ И ПОДМЕНЮ--------------------------------------------

int Menu()
{
    int select;
    system("cls");
    puts("*****************МЕНЮ*****************");
    puts("1 - Справка");
    puts("2 - Ввод данных");
    puts("3 - Контрольный вывод данных");
    puts("4 - Обработка текста");
    puts("5 - Вывод результата");
    puts("0 - Выход");
    puts("Выберете пункт меню");
    scanf("%d", &select);
    fflush(stdin);
    return select;

}

int InputData()
{
    system("cls");
    int select;
    puts("*****************ВВОД ДАННЫХ*****************");
    puts("1 - Ввод разделителей");
    puts("2 - Ввод слова");
    puts("3 - Ввод текста из консоли");
    puts("4 - Ввод текста из файла");
    puts("5 - Назад");
    scanf("%d", &select);
    fflush(stdin);
    return select;
}

int CheckData()
{
    system("cls");
    int select;
    puts("*****************КОНТРОЛЬНЫЙ ВЫВОД ДАННЫХ*****************");
    puts("1 - Вывод разделителей");
    puts("2 - Вывод заданного слова");
    puts("3 - Вывод текста");
    puts("4 - Назад");
    scanf("%d", &select);
    fflush(stdin);
    return select;
}

void Help()
{
    system("cls");
    puts("  Данная программа предназначена для формирования нового текста, который");
    puts(" является результатом следующего преобразования исходного текста:");
    puts(" Из строк введённого текста сформировать другой текст, в котором");
    puts(" будет вставлено заданное слово после слов, содержащих нечетное количество слов ");
    puts(" одновременно будут удалены слова, содержащие четное количество символов, ");
    puts(" если было вставлено заданное слово ");
    puts("\n  Ввод текста пользователем заканчивается после ввода строки,");
    puts(" содержащей максимальное количество слов из строк, ввдённых ранее.\n");
    system("pause");
}

//--------------------------------------------Ввод данных--------------------------------------------
char* GenerateDelimiterArray()
{
    system("cls");
    char *Delims = NULL,
            c;
    int f,                      //Флаг повтора
        i,j;                    //Для цикла
    Delims = (char*)malloc(MAX_LEN+1*sizeof(char));
    i = 0;
    if(Delims != NULL)
    {
        printf("Построчно введите разделители. Их количество не должно превышать %d!\nВведите уже существующий разделитель, чтобы закончить ввод\n", MAX_LEN);
        do
        {
            c = getchar();
            f = 1;
            for(j = 0; f && j < i; j++)
            {
                if(c == Delims[j])
                {
                    f = 0;
                    //puts("ПОВТОР!!!"); DEBUG
                }
            }
            if(c != '\n' && f)
            {
                Delims[i] = c;
                i++;
            }
            //printf("DEBUG | i = %d\n", i); DEBUG
        } while(i < 8 && f);
        Delims[i] = '\0';
    }
    else puts("Ошибка: Не удалось выделить память.");
    system("pause");
    return Delims;
}

char* InputKeyWord()
{
    char *word = NULL;
    int i,j;
    word = (char*)malloc(MAX_LEN+1*sizeof(char));
    if(word != NULL)
    {
        puts("Введите длину слова");
        scanf("%d", &i);
        for(j = 0; j < i+1; j++)
            word[j] = getchar();
        word[j] = '\0';
        fflush(stdin);
    }
    else puts("Ошибка: Не удалось выделить память.");
    return word;
}

char** InputTextConsole(int *textrows, char *delims)
{
    char**  text = NULL,        //Текст
            tpointer = NULL;    //Для realloc
    int     i,
            j,
            f,                  //Флаг
            max,                //Макс кол-во слов
            cwords;             //Кол-во слов в строке
    char    string[MAX_LEN+1],  //Строка
            c;                  //Введенный символ
    if(delims == NULL) puts("Введите строку разделителей!");
    else
    {
        free_text(text, *textrows);
        *textrows = 0; max = 0;
        f = 1; i = 0;
        printf("Введите текст. Длина строки не больше %d символов!\nВвод завершается, если введена строка с количеством слов, \nкоторое совпадает с максимальным количеством слов предыдущих строк\n", MAX_LEN);
        do
        {
            j = 0;
            do
            {
                c = getch();
                if(c != 13 && c != 8 && !(j == 0 && IsDelimiter(c, delims)))
                {
                    string[j] = c;
                    printf("%c", c);
                    //printf("(%d)", IsDelimiter(c, delims));   //DEBUG
                    j++;
                }
                else if(c == 8)
                {
                    if(j > 0)
                    {
                        string[j] = '\0';
                        printf("\r%s", string);
                        j--;
                    }
                }
            } while(j < MAX_LEN && c != 13);
            string[j] = '\0';
            //printf("|DEBUG| %d | %d\n", strlen(string),i);      //DEBUG
            if(strlen(string) > 0)
            {
                cwords = AmountOfWords(string, delims);
                if(i > 0 && cwords == max) f = 0;
                if(max < cwords) max = cwords;
                text = (char**)realloc(text, (i+1)*sizeof(char*));
                *(text+i) = (char*)malloc((MAX_LEN+1)*sizeof(char));
                strcpy(text[i], string);
                puts("");
                i++;
            }
            fflush(stdin);
            //printf("| DEBUG | cwords = %d | max = %d | j = %d\n", cwords, max, j);    //DEBUG
        } while(f);
        //else puts("Ошибка: Не удалось выделить память.");
        *textrows = i;
        //printf("DEBUG | %d | %d\n", *textrows, i);    //DEBUG
    }
    system("pause");
    return text;
}

char** InputTextFile(int *textrows)
{
    char *text = NULL,
         **result = NULL,
         *string = NULL;    //Строка
    FILE *file = NULL;
    char filename[128];     //Имя файла
    int i,
        j,
        size,           //Размер файла
        frows,           //Строк в файле
        cel;            //Текущий элемент result
    printf("Введите имя файла для чтения. Имя файла не должно превышать 128 символов!\nВнимание! Символов на строке максимум %d!\n", MAX_LEN);
    gets(filename);
    file = fopen(filename, "r");
    if(file != NULL)
    {
        fseek(file,0,SEEK_SET);
        fseek(file,0,SEEK_END);
        size = ftell(file);
        rewind(file);
        //printf("DEBUG | size = %d\n", size); //DEBUG
        text = (char*)malloc(size*sizeof(char));
        string = malloc((MAX_LEN+1)*sizeof(char));
        if(text != NULL && string != NULL)
        {
            fread(text, size, 1, file);
            if(fclose(file) == EOF) puts("Error closing!");
            frows = 1;
            for(i = 0; i < size; i++)
            {
                if(text[i] == '\n') frows++;
            }
            result = (char**)malloc(frows*sizeof(char*));
            if(result != NULL)
            {
                cel = 0; i = 0;
                for(int k = 0; k < frows; k++)
                {
                    for(j = 0; j < MAX_LEN && text[cel] != '\n';j++)
                    {
                        string[j] = text[cel];
                        cel++;
                    }
                    *(string+j) = '\0';
                    //printf("DEBUG | %c (len: %d)\n", string[j], strlen(string));      //DEBUG
                    //puts(string);     //DEBUG
                    if(strlen(string) > 0)
                    {
                        *(result+i) = (char*)malloc(j*sizeof(char));
                        strcpy(*(result+i), string);
                        i++;
                        //printf("  | %d | %d\n", i, frows);        //DEBUG
                    }
                    while(text[cel] != '\n') cel++;
                    cel++;
                    //printf("*******\nDEBUG result | %s\nDEBUG string | %s\nDEBUG cel | %d %c\n*******\n" , *(result+i), string, cel, text[cel]); //DEBUG
                }
            }
            *textrows = i;
            free(text);
            free(string);
            //puts(text); //DEBUG
            //printf("DEBUG | frows = %d\n", frows);    //DEBUG
        }
    }
    else puts("Cannot open file!!!");
    system("pause");
    return result;
}

//--------------------------------------------ВЫВОД ДАННЫХ--------------------------------------------
void ShowKeyWord(char *word)
{
    system("cls");
    if(word == NULL) puts("Слово не было задано!");
    else printf("Введенное слово: %s", word);
    puts("");
    system("pause");
}

void ShowDelimiters(char *delims)
{
    system("cls");
    int i;
    i = 0;
    printf("Разделители: ");
    if(delims == NULL) puts("не заданы!");
    else
    {
            while(delims[i] != '\0')
        {
            printf("'%c' ", delims[i]);
            i++;
        }
        puts("");
    }
    system("pause");
}

void ShowTextConsole(char** text, int rows)
{
    system("cls");
    if(text == NULL) puts("Текст не задан!");
    else
    {
        for (int i = 0; i < rows; i++)
            puts(*(text+i));
        fflush(stdout);
    }
    system("pause");
}

void SaveResult(char** text, int rows)
{
    FILE *file = NULL;
    char filename[128];
    if(text == NULL) puts("Нечего сохранять!");
    else
    {
        puts("Введите имя файла для сохранения");
        gets(filename);
        file = fopen(filename, "w");
        for(int i = 0; i < rows; i++)
        {
            fputs(*(text+i),file);
            fprintf(file, "\n");
        }
        fclose(file);
    }
    system("pause");
}
//--------------------------------------------ОЧИСТКА ПАМЯТИ--------------------------------------------

char* free_str(char* str)
{
    if(str != NULL)
    {
        free(str);
        str = NULL;
    }
    return str;
}

char** free_text(char** text, int rows)
{
    if(text != NULL)
    {
        for(int i = 0; i < rows; i++)
            free(*(text+i));
        free(text);
        text = NULL;
    }
    return text;
}

//--------------------------------------------ВСЕ ДЛЯ ОБРАБОТКИ--------------------------------------------
int AmountOfWords(char *string, char *delims)
{
    int Amount,
        i;
    i = 1; Amount = 1;
    do
    {
        if(IsDelimiter(string[i], delims) && !IsDelimiter(string[i-1], delims)) Amount++;
        i++;
    } while(string[i] != '\0');
    if(IsDelimiter(string[i-1], delims)) Amount--;
    return Amount;
}

int IsDelimiter(char symbol, char* delims)
{
    int f,
        i;
    f = 0; i = 0;
    while(delims[i] != '\0' && !f)
    {
        if(symbol == delims[i]) f = 1;
        //printf("%c | %c |\n", symbol, delims[i]);
        i++;
    }
    return f;
}

char** ProcessText(char **text, int rows, char *keyword, char *delims)
{
    char **result = NULL;
    char *string = NULL;
    int i,
        j,
        k,          //Элемент строки text
        f,          //Флаг того, что вставлено слово
        letters,    //Кол-во букв
        word;       //Начало слова
    if(text == NULL || keyword == NULL || delims == NULL) puts("Сначала введите все исходные данные!");
    else
    {
        //for (int i = 0; i < rows; i++)            //DEBUG
        //    puts(*(text+i));
        result = (char**)malloc(rows*sizeof(char*));
        for(i = 0; i < rows; i++)
        {
            word = 0; letters = 0; j = 0; k = 0;
            //string = malloc((MAX_LEN+1)*sizeof(char));
            string = calloc(MAX_LEN+1, sizeof(char));
            //strcpy(string, *(text+i));
            //puts(*(text+i));
            //puts(string);

            //for (int i = 0; i < rows; i++)
            //puts(*(text+i));

            do
            {
                if(text[i][k] != '\n' && text[i][k] != '\0') string[j] = text[i][k];
                if(IsDelimiter(text[i][j],delims))
                {
                    if(letters % 2 == 1)
                    {
                        puts("NECHET");
                        for(f = 1; keyword[f] != '\0'; f++)
                        {
                            j++;
                            string[j] = keyword[f];
                        }
                        puts(string);
                    }
                    //printf("DEBUG | Кол-во симв в %d слове = %d\n", word, letters);
                    letters = 0;
                }
                else letters++;
                printf("DEBUG | j = %d | k(%c) = %d\n", j, text[i][k], k);    //DEBUG
                k++; j++;
            } while(text[i][k] != '\0' && text[i][k] != '\n');
            //printf("letters = %d | k = %d | j = %d\n", letters, k, j);
            //printf("DEBUG| i = %d | j = %d\n", i, j);    //DEBUG
            //printf("len = %d\n", strlen(string));  //DEBUG
            //printf("DEBUG | %d | %c", string[j], string[j]);
            *(result+i) = (char*)malloc(j*sizeof(char));
            strcpy(*(result+i), string);
            puts("");
            //puts(string); //DEBUG
        }
    }
    system("pause");
    return result;
}
