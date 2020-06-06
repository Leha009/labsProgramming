#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct AnyName
{
    int data;                  //Рейтинг АЗС(1-10)
    struct AnyName* next;        //Ссылка на следующую структуру
} Any;

//Напишите функцию для добавления элемента в кольцевой список после элемента с заданным номером

Any* insert_after(Any* first, int place, Any* toInsert)
{
    int i;
    Any* buff = first;
    if(place == 0)
    {
        toInsert->next = first;
        for(;buff->next != first; buff = buff->next);
        buff->next = toInsert;
        first = toInsert;
    }
    else
    {
        for(i = 1; i < place; i++, buff = buff->next);
        toInsert->next = buff->next;
        buff->next = toInsert;
    }
    return first;
}

int main()
{
    Any* first = (Any*)malloc(sizeof(Any));
    first->data = 0;
    Any* p1 = (Any*)malloc(sizeof(Any));
    p1->data = 1;
    Any* p2 = (Any*)malloc(sizeof(Any));
    p2->data = 2;
    Any* p3 = (Any*)malloc(sizeof(Any));
    p3->data = 141232;

    first->next = p1;
    p1->next = p2;
    p2->next = first;

    int k = 0;

    first = insert_after(first, k, p3);
    p1 = first;
    do
    {
        printf("%d\n", p1->data);
        p1 = p1->next;
    } while(p1 != first);
    return 0;
}
