#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"

struct ListNode
{
    Info *data;
    struct ListNode *prev;
    struct ListNode *next;
};

struct List
{
    int size;
    ListNode *firstNode;
    ListNode *lastNode;
};

void *getInfoList(ListNode *node)
{
    return node->data;
}

List *createList()
{
    List *list = (List *)malloc(sizeof(List));
    list->size = 0;
    list->firstNode = NULL;
    list->lastNode = NULL;
    return (list);
}

ListNode *createListNode(Info *data)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return (node);
}

bool isEmptyList(List *list)
{
    return list->size == 0;
}

void addFirstNodeToList(ListNode *node, List *list)
{
    list->firstNode = node;
    list->lastNode = node;
    list->size++;
}

void addNthNodeToList(ListNode *node, List *list)
{
    ListNode *currentLastNode = list->lastNode;
    currentLastNode->next = node;
    node->prev = currentLastNode;
    list->lastNode = node;
    list->size++;
}

void addNodeToList(ListNode *node, List *list)
{
    if (isEmptyList(list))
    {
        addFirstNodeToList(node, list);
    }
    else
    {
        addNthNodeToList(node, list);
    }
}

void addNodeBeforeNodeToList(ListNode *node, ListNode *nodeReference, List *list)
{
    if (nodeReference->prev == NULL)
    {
        node->next = nodeReference;
        nodeReference->prev = node;
        list->firstNode = node;
        list->size++;
    }
    else
    {
        ListNode *prevNode = nodeReference->prev;
        ListNode *nextNode = nodeReference;
        prevNode->next = node;
        node->prev = prevNode;
        nextNode->prev = node;
        node->next = nextNode;
        list->size++;
    }
}

void addNodeAfterNodeToList(ListNode *node, ListNode *prevNode, List *list)
{
    ListNode *nextNode = prevNode->next;
    if (nextNode == NULL)
    {
        addNodeToList(node, list);
    }
    else
    {
        nextNode->prev = node;
        prevNode->next = node;
        node->prev = prevNode;
        node->next = nextNode;
        list->size++;
    }
}

ListNode *getFirstNode(List *list)
{
    return list->firstNode;
}

ListNode *getNextNode(ListNode *node)
{
    return node->next;
}

void printAllList(List *list)
{
    ListNode *currentNode = list->firstNode;
    if (isEmptyList(list))
    {
        return;
    }
    while (currentNode != NULL)
    {
        // printInfo(currentNode->data);
        currentNode = currentNode->next;
    }
}

void removeUniqueListNode(ListNode *node, List *list)
{
    list->firstNode = NULL;
    list->lastNode = NULL;
    list->size--;
    free(node->data);
    free(node);
}

void removeFirstListNode(ListNode *node, List *list)
{
    ListNode *firstNode = list->firstNode;
    ListNode *secondNode = list->firstNode->next;

    list->firstNode = secondNode;
    if (secondNode != NULL)
    {
        secondNode->prev = NULL;
    }
    list->size--;
    free(node->data);
    free(node);
}

void removeNthListNode(ListNode *node, List *list)
{
    ListNode *prevNode = node->prev;
    ListNode *nextNode = node->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    list->size--;
    free(node->data);
    free(node);
}

void removeLastListNode(ListNode *node, List *list)
{
    ListNode *prevNode = node->prev;
    prevNode->next = NULL;
    list->lastNode = prevNode;
    list->size--;
    free(node->data);
    free(node);
}

bool removeListNode(ListNode *node, List *list)
{
    if (isEmptyList(list))
    {
        return false;
    }
    else if (list->size == 1)
    {
        removeUniqueListNode(node, list);
    }
    else if (list->firstNode == node)
    {
        removeFirstListNode(node, list);
    }
    else if (list->lastNode == node)
    {
        removeLastListNode(node, list);
    }
    else
    {
        removeNthListNode(node, list);
    }
    return true;
}

int getListSize(List *list)
{
    return list->size;
}
