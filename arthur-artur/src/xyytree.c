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

/*
    # Entrada:
        - node: Nó da XyyTree
    
    # Saída:
        - double
    
    # Descrição:
        - Retorna a coordenada x da
          da forma armazenada em node
*/
double getNodeX(Node node)
{
    if (node == NULL)
        return 0.0;

    NODE *nd = (NODE *)node;

    return getFormX(nd->data);
}

/*
    # Entrada:
        - node: Nó da XyyTree
    
    # Saída:
        - double
    
    # Descrição:
        - Retorna a coordenada y da
          da forma armazenada em node
*/
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

    tree->size++;
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

void countDeaths(Info i, double x, double y, void *aux)
{
    if(i == NULL)
        return;
    
    if(getFormCondition(i) != alive)
        *(int *)aux += 1;
}

void reconstruct(XyyTree t)
{
    Node nodesToReallocate[30];
}

void removeNoXyyT(XyyTree t, Node n)
{
    if(t == NULL || n == NULL)
        return;

    XYYTREE *tree = (XYYTREE *) t;
    NODE *node = (NODE *) n;

    if(getFormCondition(node->data) == alive)
        damageFormProtection(node->data, -1);
    
    int dead = 0;
    visitaProfundidadeXyyT(t, &countDeaths, &dead);

    if((double)dead / tree->size >= tree->max_decay)
        reconstruct(t);
}

Info getInfoXyyT(XyyTree t, Node n)
{
    if(n == NULL)
        return NULL;
    
    NODE *node = (NODE *) n;

    return node->data;
}

void nodeRegiao(List lst, Node node, double x1, double y1, double x2, double y2)
{
    if(node == NULL)
        return;

    NODE *nd = (NODE *) node;

    double x = getNodeX(node);
    double y = getNodeY(node);

    if((x >= x1 && x <= x2) && (y >= y1 && y <= y2))
    {
        insertEnd(lst, node);
        nodeRegiao(lst, nd->left, x1, y1, x2, y2);
        nodeRegiao(lst, nd->center, x1, y1, x2, y2);
        nodeRegiao(lst, nd->right, x1, y1, x2, y2);
    }
    else if(x < x1)
    {
        if(y > y2)
        {
            nodeRegiao(lst, nd->center, x1, y1, x2, y2);
        }
        else if(y < y1)
        {
            nodeRegiao(lst, nd->right, x1, y1, x2, y2);
        }
        else
        {
            nodeRegiao(lst, nd->center, x1, y1, x2, y2);
            nodeRegiao(lst, nd->right, x1, y1, x2, y2);
        }
    }
    else if(x > x2)
    {
        nodeRegiao(lst, nd->left, x1, y1, x2, y2);
    }
    else
    {
        if(y > y2)
        {
            nodeRegiao(lst, nd->left, x1, y1, x2, y2);
            nodeRegiao(lst, nd->center, x1, y1, x2, y2);
        }
        else
        {
            nodeRegiao(lst, nd->left, x1, y1, x2, y2);
            nodeRegiao(lst, nd->right, x1, y1, x2, y2);
        }
    }
}

void infoRegiao(List lst, Node node, double x1, double y1, double x2, double y2, FdentroDe f)
{
    if(node == NULL)
        return;
    
    NODE *nd = (NODE *) node;

    double x = getNodeX(node);
    double y = getNodeY(node);

    if(f(nd->data, x1, y1, x2, y2))
    {
        insertEnd(lst, nd->data);
        infoRegiao(lst, nd->left, x1, y1, x2, y2, f);
        infoRegiao(lst, nd->center, x1, y1, x2, y2, f);
        infoRegiao(lst, nd->right, x1, y1, x2, y2, f);
    }
    else if(x < x1)
    {
        if(y > y2)
        {
            infoRegiao(lst, nd->center, x1, y1, x2, y2, f);
        }
        else if(y < y1)
        {
            infoRegiao(lst, nd->right, x1, y1, x2, y2, f);
        }
        else
        {
            infoRegiao(lst, nd->center, x1, y1, x2, y2, f);
            infoRegiao(lst, nd->right, x1, y1, x2, y2, f);
        }
    }
    else if(x > x2)
    {
        infoRegiao(lst, nd->left, x1, y1, x2, y2, f);
    }
    else
    {
        if(y > y2)
        {
            infoRegiao(lst, nd->left, x1, y1, x2, y2, f);
            infoRegiao(lst, nd->center, x1, y1, x2, y2, f);
        }
        else
        {
            infoRegiao(lst, nd->left, x1, y1, x2, y2, f);
            infoRegiao(lst, nd->right, x1, y1, x2, y2, f);
        }
    }
}

List *getNodesDentroRegiaoXyyT(XyyTree t, double x1, double y1, double x2, double y2)
{
    if(t == NULL)
        return NULL;
    
    List dentroRegiao = newList();

    XYYTREE *tree = (XYYTREE *) t;

    nodeRegiao(dentroRegiao, tree->head, x1, y1, x2, y2);

    return dentroRegiao;
}

List *getInfosDentroRegiaoXyyT(XyyTree t, double x1, double y1, double x2, double y2, FdentroDe f)
{
    if(t == NULL)
        return NULL;
    
    List dentroRegiao = newList();

    XYYTREE *tree = (XYYTREE *) t;

    infoRegiao(dentroRegiao, tree->head, x1, y1, x2, y2, f);

    return dentroRegiao;
}

void atingidoPonto(List lst, Node node, double x, double y, FatingidoPor f)
{
    if(node == NULL)
        return;
    
    NODE *nd = (NODE *) node;

    if(f(nd->data, x, y))
        insertEnd(lst, nd->data);
    
    if(x < getNodeX(nd))
        atingidoPonto(lst, nd->left, x, y, f);
    else
    {
        if(y < getNodeY(nd))
            atingidoPonto(lst, nd->center, x, y, f);
        else
            atingidoPonto(lst, nd->right, x, y, f);
    }
}

List *getInfosAtingidoPontoXyyT(XyyTree t, double x, double y, FatingidoPor f)
{
    if(t == NULL)
        return NULL;

    List atingidos = newList();

    XYYTREE *tree = (XYYTREE *) t;

    atingidoPonto(atingidos, tree->head, x, y, f);

    return atingidos;
}

void profundidade(Node node, FvisitaNo f, void *aux)
{
    if(node == NULL)
        return;
    
    NODE *nd = (NODE *) node;
    
    f(nd->data, getNodeX(node), getNodeY(node), aux);
   
    profundidade(nd->left, f, aux);
    profundidade(nd->center, f, aux);
    profundidade(nd->right, f, aux);
}

void visitaProfundidadeXyyT(XyyTree t, FvisitaNo f, void *aux)
{
    if(t == NULL)
        return;
    
    XYYTREE *tree = (XYYTREE *) t;
    
    profundidade(tree->head, f, aux);
    
}

void largura(List lst, Node node)
{
    if(node == NULL)
        return;
    
    NODE *nd = getItemElement(node);

    if(nd->left != NULL)
        insertEnd(lst, nd->left);
    if(nd->center != NULL)
        insertEnd(lst, nd->center);
    if(nd->right != NULL)
        insertEnd(lst, nd->right);

    largura(lst, getNextItem(node));
}

void visitaLarguraXyyT(XyyTree t, FvisitaNo f, void *aux)
{
    if(t == NULL)
        return;
    
    XYYTREE *tree = (XYYTREE *) t;

    List nodes = newList();
    insertEnd(nodes, tree->head);

    largura(nodes, getFirstItem(nodes));

    NODE *node;
    for(Node nd = getFirstItem(nodes); nd != NULL; nd = getNextItem(nd))
    {
        node = getItemElement(nd);
        f(node->data, getNodeX(node), getNodeY(node), aux);
    }

    destroyList(nodes, NULL);
}
