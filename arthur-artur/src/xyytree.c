#include <stdio.h>
#include <stdlib.h>

#include "xyytree.h"
#include "strings.h"
#include "forms.h"

#include "enum.h"

// Constante de erro aceitado para comparação de double
// #define EPSILON 0.0000009

typedef struct _node
{
    struct _node *parent;
    Info *data; // Dados da forma armazenada nesse nó
    struct _node *left;
    struct _node *center;
    struct _node *right;
} NODE;

typedef struct _xyytree
{
    int size;         // Quantidade de elementos na árvore
    int dead;         // Quantidade de elementos mortos/inativados na árvore
    double max_decay; // Decaimento máximo da árvore
    NODE *head;       // Raíz da árvore
} XYYTREE;

XyyTree newXyyTree(double fd)
{
    XYYTREE *tree = (XYYTREE *)malloc(sizeof(XYYTREE));
    if (tree == NULL)
    {
        printf("ERROR: Could not allocate memory for new XyyTree\n");
        exit(EXIT_FAILURE);
    }

    // Atribuição de valores
    tree->size = 0;
    tree->dead = 0;
    tree->max_decay = fd;
    tree->head = NULL;

    return tree;
}

/*
    # Entrada:
        - t: XyyTree
    # Saída:
        - true
        - false
    # Descrição:
        - Retorna true caso a árvore esteja vazia,
          false caso contrário
        - t != NULL
*/
bool isTreeEmpty(XyyTree t)
{
    if (t == NULL)
        return true;

    XYYTREE *tree = (XYYTREE *)t;

    return tree->head == NULL;
}

/*
    # Entrada:
        - info: Informação a ser armazenada no nó
    # Saída:
        - Node: Nó criado
    # Descrição:
        - Cria um nó e armazena nele a informação passada
*/
Node newNode(Info info)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("ERROR: Could not allocate memory for new node\n");
        exit(EXIT_FAILURE);
    }

    // Atribuição de valores
    node->parent = NULL;
    node->data = info;
    node->left = NULL;
    node->center = NULL;
    node->right = NULL;

    return node;
}

double getNodeX(Node node)
{
    if (node == NULL)
        return 0.0;

    NODE *nd = (NODE *)node;

    return getFormX(nd->data);
}

double getNodeY(Node node)
{
    if (node == NULL)
        return 0.0;

    NODE *nd = (NODE *)node;

    return getFormY(nd->data);
}

/*
    # Entradas:
        - node: Nó de uma XyyTree
        - x, y: Coordenadas de forma a ser inserida na árvore
        - i: Informação a ser criada no nó que será inserido
    # Saída:
        - Node: Nó criado
    # Descrição:
        - Percorre a árvore e insere i na posição correta
        - Retorna um ponteiro para o nó no qual i foi inserida
*/
Node insertNode(Node node, double x, double y, Info i)
{
    // Coordenadas x e y da forma no nó atual
    double xNode = getNodeX(node);
    double yNode = getNodeY(node);

    NODE *nd = (NODE *)node;
    Node nextNode;
    if (x < xNode)
    {
        nextNode = nd->left;
        if (nextNode != NULL)
            return insertNode(nextNode, x, y, i);

        // Criar e posicionar novo nó
        Node insertedNode = newNode(i);
        nd->left = insertedNode;

        return insertedNode;
    }
    else if (y < yNode)
    {
        nextNode = nd->center;
        if (nextNode != NULL)
            return insertNode(nextNode, x, y, i);

        // Criar e posicionar novo nó
        Node insertedNode = newNode(i);
        nd->center = insertedNode;

        return insertedNode;
    }
    else
    {
        nextNode = nd->right;
        if (nextNode != NULL)
            return insertNode(nextNode, x, y, i);

        // Criar e posicionar novo nó
        Node insertedNode = newNode(i);
        nd->right = insertedNode;

        return insertedNode;
    }
}

Node insertXyyT(XyyTree t, double x, double y, Info i)
{
    if (t == NULL || i == NULL)
        return NULL;

    XYYTREE *tree = (XYYTREE *)t;
    NODE *inserted;
    if (isTreeEmpty(t))
    {
        inserted = newNode(i);

        tree->head = inserted;
    }
    else
    {
        inserted = insertNode(tree->head, x, y, i);
    }

    return inserted;
}

/*
    # Entradas:
        - node: Nó de uma XyyTree
        - x, y: Coordenada âncora da figura procurada
        - epsilon: Erro aceito na comparação de double

    # Saída:
        - Node: Nó contendo a forma procurada

    # Descrição:
        - Retorna o nó que armazena a forma com ponto âncora na
          coordenada (x, y)
*/
Node searchXyyTree(Node node, double x, double y, double epsilon)
{
    if (node == NULL)
        return NULL;

    double nodeX = getNodeX(node);
    double nodeY = getNodeY(node);

    double deltaX = nodeX - x;
    deltaX = (deltaX < 0) ? (deltaX * -1) : deltaX;
    double deltaY = nodeY - y;
    deltaY = (deltaY < 0) ? (deltaY * -1) : deltaY;

    NODE *nd = (NODE *)node;
    if (deltaX <= epsilon && deltaY <= epsilon)
        return node;
    else if (x < nodeX)
        return searchXyyTree(nd->left, x, y, epsilon);
    else if (y < nodeY)
        return searchXyyTree(nd->center, x, y, epsilon);

    return searchXyyTree(nd->right, x, y, epsilon);
}

Node getNodeXyyT(XyyTree t, double x, double y, double epsilon)
{
    if (t == NULL)
        return NULL;

    XYYTREE *tree = (XYYTREE *)t;

    return searchXyyTree(tree->head, x, y, epsilon);
}

// ------------------------------------------

void removeNoXyyT(XyyTree t, Node n)
{
    // TODO:
}

Info getInfoXyyT(XyyTree t, Node n)
{
    // TODO:
}

List *getNodesDentroRegiaoXyyT(XyyTree t, double x1, double y1, double x2, double y2)
{
    // TODO:
}

List *getInfosDentroRegiaoXyyT(XyyTree t, double x1, double y1, double x2, double y2, FdentroDe f)
{
    // TODO:
}

List *getInfosAtingidoPontoXyyT(XyyTree t, double x, double y, FatingidoPor f)
{
    // TODO:
}

void visitaProfundidadeXyyT(XyyTree t, FvisitaNo f, void *aux)
{
    // TODO:
}

void visitaLarguraXyyT(XyyTree t, FvisitaNo f, void *aux)
{
    // TODO:
}
