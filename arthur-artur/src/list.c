#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct _structNode
{
    struct _structNode *prev;
    Info info;
    struct _structNode *next;
} NODE;

typedef struct _structList
{
    NODE *head;
    NODE *tail;
} LIST;

NODE *newItem()
{
    NODE *lli = (NODE *)malloc(sizeof(NODE));
    if (lli == NULL)
    {
        printf("ERROR: Could not allocate memory for new list item\n");
        exit(EXIT_FAILURE);
    }

    lli->prev = NULL;
    lli->info = NULL;
    lli->next = NULL;

    return lli;
}

List newList()
{
    LIST *lst = (LIST *)malloc(sizeof(LIST));
    if (lst == NULL)
    {
        printf("ERROR: Could not allocate memory for new list\n");
        exit(EXIT_FAILURE);
    }

    lst->head = NULL;
    lst->tail = NULL;

    return lst;
}

bool isListEmpty(List lst)
{
    if (lst == NULL)
        return true;

    LIST *l = (LIST *)lst;

    return l->head == NULL;
}

int listSize(List lst)
{
    if (lst == NULL)
        return 0;

    int size = 0;

    for (Node li = getFirstItem(lst); li != NULL; li = getNextItem(li))
        size++;

    return size;
}

Node insertStart(List lst, Info info)
{
    if (lst == NULL || info == NULL)
        return NULL;

    LIST *l = (LIST *)lst;

    // Criar novo item
    NODE *lli = newItem();
    lli->info = info;
    lli->next = l->head;

    // Posicionar novo item
    if (!isListEmpty(lst))
        l->head->prev = lli;
    l->head = lli;

    // Verificar se tail == NULL
    if (l->tail == NULL)
        l->tail = l->head;

    return lli;
}

Node insertEnd(List lst, Info info)
{
    if (lst == NULL || info == NULL)
        return NULL;

    if (isListEmpty(lst))
        return insertStart(lst, info);

    // Criar novo item
    NODE *lli = newItem();
    lli->info = info;

    // Posicionar novo item
    NODE *last = getLastItem(lst);
    last->next = lli;
    lli->prev = last;

    // Atualizar valor de tail
    LIST *l = (LIST *)lst;
    l->tail = lli;

    return lli;
}

Node insertAfter(List lst, Node li, Info info)
{
    if (lst == NULL || li == NULL || info == NULL)
        return NULL;

    if (getLastItem(lst) == li)
        return insertEnd(lst, info);

    // Criar novo item
    NODE *lli = newItem();
    lli->info = info;

    // Posicionar item
    NODE *llit = (NODE *)li;

    lli->prev = llit;
    lli->next = llit->next;

    llit->next->prev = lli;
    llit->next = lli;

    return lli;
}

Node insertBefore(List lst, Node li, Info info)
{
    if (lst == NULL || li == NULL || info == NULL)
        return NULL;

    if (getFirstItem(lst) == li)
        return insertStart(lst, info);

    // Criar novo item
    NODE *lli = newItem();
    lli->info = info;

    // Posicionar item
    NODE *llit = (NODE *)li;

    lli->next = llit;
    lli->prev = llit->prev;

    llit->prev->next = lli;
    llit->prev = lli;

    return lli;
}

Info removeItem(List lst, Node li)
{
    if (lst == NULL || li == NULL)
        return NULL;

    if (isListEmpty(lst))
        return NULL;

    // Armazenar elemento que deve ser retornado
    Info info = getItemElement(li);

    // Remover elemento da lista
    LIST *l = (LIST *)lst;
    NODE *lli = (NODE *)li;

    if (getFirstItem(lst) == li)
        l->head = l->head->next;
    if (getLastItem(lst) == li)
        l->tail = l->tail->prev;
    if (lli->prev != NULL)
        lli->prev->next = lli->next;
    if (lli->next != NULL)
        lli->next->prev = lli->prev;

    lli->prev = NULL;
    lli->info = NULL;
    lli->next = NULL;

    free(lli);

    return info;
}

Info getItemElement(Node li)
{
    if (li == NULL)
        return NULL;

    NODE *lli = (NODE *)li;

    return lli->info;
}

Node getFirstItem(List lst)
{
    if (lst == NULL)
        return NULL;

    LIST *l = (LIST *)lst;

    return l->head;
}

Node getLastItem(List lst)
{
    if (lst == NULL)
        return NULL;

    if (isListEmpty(lst))
        return NULL;

    LIST *l = (LIST *)lst;

    return l->tail;
}

Node getNextItem(Node li)
{
    if (li == NULL)
        return NULL;

    NODE *lli = (NODE *)li;

    return lli->next;
}

Node getPreviousItem(Node li)
{
    if (li == NULL)
        return NULL;

    NODE *lli = (NODE *)li;

    return lli->prev;
}

Info replaceItem(List li, Info info)
{
    if (li == NULL || info == NULL)
        return NULL;

    NODE *lli = (NODE *)li;

    Info toReturn = lli->info;
    lli->info = info;

    return toReturn;
}

void destroyList(List lst, void (*destroyElement)())
{
    if (lst == NULL)
        return;

    if (destroyElement != NULL)
    {
        while (!isListEmpty(lst))
        {
            destroyElement(removeItem(lst, getFirstItem(lst)));
        }
    }

    free(lst);
    lst = NULL;
}
