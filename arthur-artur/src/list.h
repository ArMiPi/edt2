#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct ListNode ListNode;
typedef struct List List;
typedef void *Info;

/*
 * Recebe nó e retorna dado do nó.
 */
void *getInfoList(ListNode *node);

/*
 * Cria a lista dinâmica.
 */
List *createList();

/*
 * Cria um nó de lista dinâmica.
 */
ListNode *createListNode(Info *data);

/*
 * Adiciona o nó criado à lista dinâmica já criada.
 */
void addListNodeToList(ListNode *node, List *list);

/*
 * Adiciona nó criado antes de determinado nó (referência) na lista dinâmica já criada.
 */
void addNodeBeforeNodeToList(ListNode *node, ListNode *nodeReference, List *list);

/*
 * Adiciona nó criado depois de determinado nó (referência) na lista dinâmica já criada.
 */
void addNodeAfterNodeToList(ListNode *node, ListNode *prevNode, List *list);

/*
 * Pegar o primeiro nó da lista dinâmica.
 */
ListNode *getFirstNode(List *list);

/*
 * Recebe um nó determinado e retorno o próximo nó.
 */
ListNode *getNextListNode(ListNode *node);

/*
 * Imprime toda a lista dinâmica.
 */
void printAllList(List *list);

/*
 * recebe a lista e o nó a ser removido.
 * retorna verdadeiro se o nó foi removido e falso se não foi.
 */
bool removeListNode(ListNode *node, List *list);

/*
 * Recebe uma lista e retorna a quantidade de nós da lista.
 */
int getListSize(List *list);

#endif
