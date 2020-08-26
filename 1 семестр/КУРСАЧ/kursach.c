//�������
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

#define MAX_LEN 80
#define MEM_ERROR puts("������: ������ �� ������� ��������!")
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
void ShowResult(char**, int);               //����� ����������

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
                free_text(result, textrows);
                result = ProcessText(text, textrows, keyword, delims);
                break;
            case 5:
                //����� ����������
                if(result != NULL) ShowResult(result, textrows);
                else
                {
                    puts("������ ��������!");
                    system("pause");
                }
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
    result = free_text(result, textrows);
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
                }
            }
            if(c != '\n' && f)
            {
                Delims[i] = c;
                i++;
            }
        } while(i < 8 && f);
        Delims[i] = '\0';
    }
    else MEM_ERROR;
    system("pause");
    return Delims;
}

char* InputKeyWord()
{
    system("cls");
    char *word = NULL;
    int i,j;
    word = (char*)malloc(MAX_LEN+1*sizeof(char));
    if(word != NULL)
    {
        puts("������� ����� �����. ��� �� ������ ��������� 80 ��������!");
        do
        {
            scanf("%d", &i);
        } while(i < 1 || i > 80);
        printf("������� �����: ");
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
    else MEM_ERROR;
    return word;
}

char** InputTextConsole(int *textrows, char *delims)
{
    system("cls");
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
                if(c != 13 && c != 8 && !(j == 0 && IsDelimiter(c, delims)))
                {
                    string[j] = c;
                    printf("%c", c);
                    j++;
                }
                else if(c == 8)
                {
                    if(j > 0)
                    {
                        string[j-1] = '\0';
                        printf("\r%s %c", string, c);
                        j--;
                    }
                }
            } while(j < MAX_LEN && c != 13);
            string[j] = '\0';
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
        } while(f);
        *textrows = i;
    }
    system("pause");
    return text;
}

char** InputTextFile(int *textrows)
{
    system("cls");
    char *text = NULL,
         **result = NULL,
         *string = NULL;    //������
    FILE *file = NULL;
    char filename[128];     //��� �����
    int ans,            //�����
        i,
        j,
        size,           //������ �����
        frows,           //����� � �����
        cel;            //������� ������� result
    puts("������ ������� ���� ��� �����? ������� ����� �����, �������� �� ����\n����� ����� ����������� ���� in.txt\n\n��������! ���������, ��� � ��������� ������ � ����� ������� ������� �� ����� ������!");
    scanf("%d", &ans);
    fflush(stdin);
    if(ans)
    {
        printf("\n������� ��� ����� ��� ������. ��� ����� �� ������ ��������� 128 ��������!\n��������! �������� �� ������ �������� %d!\n", MAX_LEN);
        gets(filename);
        file = fopen(filename, "r");
    }
    else file = fopen("in.txt", "r");
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
            free_str(text);
            free_str(string);
        }
    }
    else puts("�� ������� ������� ����!");
    system("pause");
    return result;
}

//--------------------------------------------����� ������--------------------------------------------
void ShowKeyWord(char *word)
{
    system("cls");
    if(word == NULL) puts("����� �� ���� ������!");
    else printf("��������� �����: %s\n", word);
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
        }
        fflush(stdout);
    }
    system("pause");
}

void SaveResult(char** text, int rows)
{
    system("cls");
    FILE *file = NULL;
    char filename[128];
    int ans;
    ans = 0;
    if(text == NULL) puts("������ ���������!");
    else
    {
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
        for(int i = 0; i < rows; i++)
        {
            fputs(*(text+i),file);
            fprintf(file, "\n");
        }
        fclose(file);
    }
    system("pause");
}

void ShowResult(char **result, int rows)
{
    system("cls");
    int select;
    puts("������� 1, ����� ������� ��������� � �������");
    puts("������� 2, ����� ������� ��������� � ����");
    puts("������� 3, ����� ���������");
    do
    {
        scanf("%d", &select);
    } while(select < 0 || select > 3);
    if(select == 1) ShowTextConsole(result, rows);
    else if(select == 2) SaveResult(result, rows);
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
    if(text != NULL)
    {
        for(int i = 0; i < rows; i++)
        {
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
        i++;
    }
    return f;
}

char** ProcessText(char **text, int rows, char *keyword, char *delims)
{
    system("cls");
    char **result = NULL;
    int i,
        j,
        k,          //������� ������ result
        f,          //���� ����, ��� ��������� �����
        letters,    //���-�� ����
        word,       //������ �����
        len;
    if(text == NULL || keyword == NULL || delims == NULL) puts("������� ������� ��� �������� ������!");
    else
    {
        result = (char**)malloc(rows*sizeof(char*));
        if(result != NULL)
        {
            for(i = 0; i < rows; i++)
            {
                len = strlen(text[i])+1;
                result[i] = (char*)malloc(len*sizeof(char));
                //result[i] = (char*)malloc((strlen(text[i])+1)*sizeof(char));
                k = 0; letters = 0; f = 0; word = 0;
                if(result[i] != NULL)
                {
                    for(j = 0; j < strlen(text[i]); j++, k++)
                    {
                        result[i][k] = text[i][j];
                        if(IsDelimiter(text[i][j],delims) && letters % 2 == 1)
                        {
                            len += strlen(keyword);
                            result[i] = (char*)realloc(result[i], len*sizeof(char));
                            for(f = 0; f < strlen(keyword); f++, k++)
                            {
                                result[i][k+1] = keyword[f];
                            }
                            result[i][k+1] = delims[0];
                            k++;
                            word = k+1;
                            letters = 0;
                        }
                        else if(IsDelimiter(text[i][j], delims)) letters = 0;
                        else letters++;
                        //printf(" | letters = %d\n",letters);
                    }
                    if(letters % 2 == 1)
                    {
                        result[i][k] = delims[0];
                        k++;
                        len += strlen(keyword);
                        result[i] = (char*)realloc(result[i], len*sizeof(char));
                        for(f = 0; f < strlen(keyword); f++, k++)
                        {
                            result[i][k] = keyword[f];
                        }
                        result[i][k] = '\0';
                    }
                    else if(f && letters % 2 == 0)
                    {
                        result[i][word] = '\0';
                    }
                    else result[i][k] = '\0';
                }
                else MEM_ERROR;
            }
        }
        else MEM_ERROR;
    }
    system("pause");
    return result;
}
