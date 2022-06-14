#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

/*
    - Esse módulo tem por objetivo definir uma lista duplamente encadeada
      bem como funções para manupulá-la

    - Todas as funções que tiverem List, Info e/ou Node como parâmetro de entrada presumem
      List != NULL && Info != NULL && Node != NULL
*/

typedef void *List;
typedef void *Node;
typedef void *Info;

/*
    # Saída:
        - List: Lista

    # Descrição:
        - Retorna um ponteiro para uma lista vazia
*/
List newList();

/*
    # Entrada:
        - lst: Lista

    # Saída:
        - true
        - false

    # Descrição:
        - Retorna true se a l estiver vazia,
          false caso contrário
*/
bool isListEmpty(List lst);

/*
    # Entrada:
        - lst: Lista

    # Saída:
        - int

    # Descrição:
        - Retorna a quantidade de elementos armazenados em lst
*/
int listSize(List lst);

/*
    # Entradas:
        - lst: Lista
        - elem: Elemento

    # Saída:
        - item: Struct

    # Descrição:
        - Insere elem no início da lista

        - Retorna um ponteiro para o Node que foi
          inserido na lista
*/
Node insertStart(List lst, Info elem);

/*
    # Entradas:
        - lst: Lista
        - elem: Elemento

    # Saída:
        - item: Struct

    # Descrição:
        - Insere elem no final da lista

        - Retorna um ponteiro para o Node que foi
          inserido na lista

        - Se isListEmpty(lst) será executada a função
          insertStart()
*/
Node insertEnd(List lst, Info elem);

/*
    # Entradas:
        - lst: Lista
        - li: Node da lista
        - elem: Elemento

    # Saída:
        - item: Struct

    # Descrição:
        - Insere elem após o Node li da lista

        - Retorna um ponteiro para o Node que foi
          inserido na lista
*/
Node insertAfter(List lst, Node li, Info elem);

/*
    # Entradas:
        - lst: Lista
        - li: Node da lista
        - elem: Elemento

    # Saída:
        - item: Struct

    # Descrição:
        - Insere elem antes o Node li da lista

        - Retorna um ponteiro para o Node que foi
          inserido na lista
*/
Node insertBefore(List lst, Node li, Info elem);

/*
    # Entradas:
        - lst: Lista
        - li: Item

    # Saída:
        - element

    # Descrição:
        - Remove o Node li da lista e retorna o
          elemento elem armazenado nesse item

        - Se a lista estiver vazia será retornado
          NULL
*/
Info removeItem(List lst, Node li);

/*
    # Entrada:
        - li: Item

    # Saída:
        - element

    # Descrição:
        - Retorna o elemento element
          armazenado em li
*/
Info getItemElement(Node li);

/*
    # Entrada:
        - lst: Lista

    # Saída:
        - item: Struct

    # Descrição:
        - Retorna um ponteiro para o primeiro
          Node da lista

        - Se a lista for vazia será retornado NULL
*/
Node getFirstItem(List lst);

/*
    # Entrada:
        - lst: Lista

    # Saída:
        - item: Struct

    # Descrição:
        - Retorna um ponteiro para o último
          Node da lista

        - Se a lista for vazia será retornado NULL
*/
Node getLastItem(List lst);

/*
    # Entradas:
        - li: Item

    # Saída:
        - item

    # Descrição:
        - Retorna o próximo Node da lista
*/
Node getNextItem(Node li);

/*
    # Entradas:
        - li: Item

    # Saída:
        - item

    # Descrição:
        - Retorna o Node da lista anterior a li
*/
Node getPreviousItem(Node li);

/*
    # Entradas:
        - li: Node da lista
        - elem: Elemento

    # Saída:
        - elem: Elemento

    # Descrição:
        - Substitui o elemento armazenado em li por elem e retorna
          o elemento que foi substituído
*/
Info replaceItem(List li, Info elem);

/*
    # Entradas:
        - lst: Lista
        - destroyElement: Função

    # Descrição:
        - Libera toda a memória utilizada por l

        - Se destroyInfo == NULL os elements de
          l não terão seus espaços de memória deslocados
*/
void destroyList(List lst, void (*destroyElement)());

#endif