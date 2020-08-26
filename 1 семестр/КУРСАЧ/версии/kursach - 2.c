//�������
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

#define MAX_LEN 80
//--------------------------------------------���� � �������--------------------------------------------

int Menu();
int InputData();                            //����
int CheckData();                            //����������� �����
void Help();                                //�������

//--------------------------------------------���� ������--------------------------------------------

char* GenerateDelimiterArray();             //���� ������������
char* InputKeyWord();                       //���� �����
char** InputTextConsole(int*, char*);       //���� ������ � �������
char** InputTextFile(int*);                 //���� ������ � �����

//--------------------------------------------����� ������--------------------------------------------

void ShowDelimiters(char*);                 //����� ������������
void ShowKeyWord(char*);                    //����� ��������� �����
void ShowTextConsole(char**, int);          //����� ������
void SaveResult(char**, int);               //���� ����������

//--------------------------------------------������� ������--------------------------------------------

char* free_str(char*);                      //�����. ������ ��� ������
char** free_text(char**, int);              //�����. ������ ��� ������

//--------------------------------------------��� ��� ���������--------------------------------------------

int AmountOfWords(char*, char*);            //������� ���-�� ����
int IsDelimiter(char, char*);               //�������� �� �����������
char** ProcessText(char**, int, char*, char*);       //��������� ������

//--------------------------------------------���������--------------------------------------------

int main()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char **text = NULL,                     //�����
         *delims = NULL,                    //�����������
         *keyword = NULL,                   //�����
         **result = NULL;                   //���������
    int DelAmount,                          //���-��
        AItems,                             //����������� ������� ����
        selected,                           //��������� �����
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
                        puts("����������� � ������� ����");
                        system("pause");
                        break;
                    default:
                        puts("�������� ����� ����. �������� ����� ���� ��� ���.");
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
                        puts("����������� � ����");
                        system("pause");
                        break;
                    default:
                        puts("�������� ����� ����. �������� ����� ���� ��� ���.");
                        system("pause");
                }
                break;
            case 4:
                //���������
                result = ProcessText(text, textrows, keyword, delims);
                break;
            case 5:
                //����� ����������
                SaveResult(result, textrows);
                break;
            case 0:
                break;
            default:
                puts("�������� ����� ����. �������� ����� ���� ��� ���.");
                system("pause");
        }
    } while(selected != 0);
    delims = free_str(delims);
    text = free_text(text, textrows);
    return 0;
}

//--------------------------------------------���� � �������--------------------------------------------

int Menu()
{
    int select;
    system("cls");
    puts("*****************����*****************");
    puts("1 - �������");
    puts("2 - ���� ������");
    puts("3 - ����������� ����� ������");
    puts("4 - ��������� ������");
    puts("5 - ����� ����������");
    puts("0 - �����");
    puts("�������� ����� ����");
    scanf("%d", &select);
    fflush(stdin);
    return select;

}

int InputData()
{
    system("cls");
    int select;
    puts("*****************���� ������*****************");
    puts("1 - ���� ������������");
    puts("2 - ���� �����");
    puts("3 - ���� ������ �� �������");
    puts("4 - ���� ������ �� �����");
    puts("5 - �����");
    scanf("%d", &select);
    fflush(stdin);
    return select;
}

int CheckData()
{
    system("cls");
    int select;
    puts("*****************����������� ����� ������*****************");
    puts("1 - ����� ������������");
    puts("2 - ����� ��������� �����");
    puts("3 - ����� ������");
    puts("4 - �����");
    scanf("%d", &select);
    fflush(stdin);
    return select;
}

void Help()
{
    system("cls");
    puts("  ������ ��������� ������������� ��� ������������ ������ ������, �������");
    puts(" �������� ����������� ���������� �������������� ��������� ������:");
    puts(" �� ����� ��������� ������ ������������ ������ �����, � �������");
    puts(" ����� ��������� �������� ����� ����� ����, ���������� �������� ���������� ���� ");
    puts(" ������������ ����� ������� �����, ���������� ������ ���������� ��������, ");
    puts(" ���� ���� ��������� �������� ����� ");
    puts("\n  ���� ������ ������������� ������������� ����� ����� ������,");
    puts(" ���������� ������������ ���������� ���� �� �����, ������� �����.\n");
    system("pause");
}

//--------------------------------------------���� ������--------------------------------------------
char* GenerateDelimiterArray()
{
    system("cls");
    char *Delims = NULL,
            c;
    int f,                      //���� �������
        i,j;                    //��� �����
    Delims = (char*)malloc(MAX_LEN+1*sizeof(char));
    i = 0;
    if(Delims != NULL)
    {
        printf("��������� ������� �����������. �� ���������� �� ������ ��������� %d!\n������� ��� ������������ �����������, ����� ��������� ����\n", MAX_LEN);
        do
        {
            c = getchar();
            f = 1;
            for(j = 0; f && j < i; j++)
            {
                if(c == Delims[j])
                {
                    f = 0;
                    //puts("������!!!"); DEBUG
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
    else puts("������: �� ������� �������� ������.");
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
        puts("������� ����� �����");
        scanf("%d", &i);
        j = 0;
        do
        {
            {
                word[j] = getchar();
                if(word[j] != '\n') j++;
            }
        } while(j < i);
        word[j] = '\0';
        fflush(stdin);
    }
    else puts("������: �� ������� �������� ������.");
    return word;
}

char** InputTextConsole(int *textrows, char *delims)
{
    char**  text = NULL,        //�����
            tpointer = NULL;    //��� realloc
    int     i,
            j,
            f,                  //����
            max,                //���� ���-�� ����
            cwords;             //���-�� ���� � ������
    char    string[MAX_LEN+1],  //������
            c;                  //��������� ������
    if(delims == NULL) puts("������� ������ ������������!");
    else
    {
        *textrows = 0; max = 0;
        f = 1; i = 0;
        printf("������� �����. ����� ������ �� ������ %d ��������!\n���� �����������, ���� ������� ������ � ����������� ����, \n������� ��������� � ������������ ����������� ���� ���������� �����\n", MAX_LEN);
        do
        {
            j = 0;
            do
            {
                c = getch();
                //printf("%d\n", c);
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
                        printf("\r%s %c", string, c);
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
            printf("| DEBUG | cwords = %d | max = %d | j = %d\n", cwords, max, j);    //DEBUG
        } while(f);
        //else puts("������: �� ������� �������� ������.");
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
         *string = NULL;    //������
    FILE *file = NULL;
    char filename[128];     //��� �����
    int i,
        j,
        size,           //������ �����
        frows,           //����� � �����
        cel;            //������� ������� result
    printf("������� ��� ����� ��� ������. ��� ����� �� ������ ��������� 128 ��������!\n��������! �������� �� ������ �������� %d!\n", MAX_LEN);
    gets(filename);
    file = fopen(filename, "r");
    if(file != NULL)
    {
        fseek(file,0,SEEK_SET);
        fseek(file,0,SEEK_END);
        size = ftell(file);
        rewind(file);
        text = (char*)malloc(size*sizeof(char));
        string = malloc((MAX_LEN+1)*sizeof(char));
        if(text != NULL && string != NULL)
        {
            fread(text, size, 1, file);
            if(fclose(file) == EOF) puts("Error closing!");
            frows = 0;
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
                    for(j = 0; j < MAX_LEN && text[cel] != '\n'; j++, cel++)
                    {
                        string[j] = text[cel];
                    }
                    string[j] = '\0';
                    if(string[j] == '\0') puts("YES");
                    if(strlen(string) > 0)
                    {
                        result[i] = (char*)malloc((strlen(string)+1)*sizeof(char));
                        for(j = 0; j < strlen(string)+1; j++)
                        {
                            result[i][j] = string[j];
                        }
                        i++;
                    }
                    while(text[cel] != '\n') cel++;
                    cel++;
                }
            }
            *textrows = i;
            printf("\n%d\n", *textrows);  //DEBUG
            free_str(text);
            free_str(string);
        }
    }
    else puts("Cannot open file!!!");
    system("pause");
    return result;
}

//--------------------------------------------����� ������--------------------------------------------
void ShowKeyWord(char *word)
{
    system("cls");
    if(word == NULL) puts("����� �� ���� ������!");
    else printf("��������� �����: %s", word);
    puts("");
    system("pause");
}

void ShowDelimiters(char *delims)
{
    system("cls");
    int i;
    i = 0;
    printf("�����������: ");
    if(delims == NULL) puts("�� ������!");
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
    if(text == NULL) puts("����� �� �����!");
    else
    {
        for (int i = 0; i < rows; i++)
        {
            puts(*(text+i));
            //if(text[i][strlen(text[i])] == '\0') puts("END OF STRING");
        }
        fflush(stdout);
    }
    system("pause");
}

void SaveResult(char** text, int rows)
{
    FILE *file = NULL;
    char filename[128];
    int ans;
    ans = 0;
    if(text == NULL) puts("������ ���������!");
    else
    {
        puts("������ ������� ��� ����� ��������������? ������� ����� �����, �������� �� ����. � ��������� ������ ��� ���������� � out.txt");
        scanf("%d", &ans);
        fflush(stdin);
        if(ans)
        {
            puts("������� ��� ����� ��� ����������");
            gets(filename);
            file = fopen(filename, "w");
        }
        else file = fopen("out.txt", "w");
        for(int i = 0; i < rows; i++)
        {
            fputs(*(text+i),file);
            fprintf(file, "\n");
        }
        fclose(file);
    }
    system("pause");
}
//--------------------------------------------������� ������--------------------------------------------

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
    //printf("DEBUG rows = %d", rows);    //DEBUG
    if(text != NULL)
    {
        for(int i = 0; i < rows; i++)
        {
            //puts("TEST");   //DEBUG
            free(*(text+i));
        }
        free(text);
        text = NULL;
    }
    return text;
}

//--------------------------------------------��� ��� ���������--------------------------------------------
int AmountOfWords(char *string, char *delims)
{
    int Amount,
        i;
    i = 1; Amount = 1;
    do
    {
        if(IsDelimiter(string[i], delims) && !IsDelimiter(string[i-1], delims)) Amount++;
        i++;
    } while(i < strlen(string));
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
    //char *string = NULL;
    int i,
        j,
        //k,          //������� ������ text
        f,          //���� ����, ��� ��������� �����
        letters,    //���-�� ����
        word;       //������ �����
    if(text == NULL || keyword == NULL || delims == NULL) puts("������� ������� ��� �������� ������!");
    else
    {
        result = (char**)malloc(rows*sizeof(char*));
        if(result != NULL)
        {
            for(i = 0; i < rows; i++)
            {
                result[i] = (char*)malloc(strlen(text[i])*sizeof(char));
                strcpy(result[i], text[i]);
                puts(result[i]);
            }
        }
    }
    system("pause");
    return result;
}
