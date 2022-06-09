#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"forms.h"

typedef struct _form 
{
    double x, y;            // Ponto âncora da figura
    int protection;         // Nível de proteção da figura
    Condition condition;    // Condição da figura
    String form;            // Comando para criação da figura
} FORM;

/*
    # Entadas:
        - x1, y1: Coordenadas de um ponto (p1)
        - x2, y2: Coordenadas de outro ponto (p2)
    
    # Saídas:
        - -1
        - 0
        - 1
    
    # Descrição:
        - Retorna 0 caso os pontos sejam iguais

        - Retorna 1 caso p1 > p2

        - Retorna -1 caso p1 < p2

        - p1 será considerado maior que p2 se a coordenada x de
          p1 for maior que a coordenada x de p2.
          Caso ambos tenham a mesma coordenada x, a comparação será
          realizada com base na coordenada y
*/
int comparePoints(double x1, double y1, double x2, double y2) 
{
    double deltaX = ((x1 - x2) > 0) ? x1 - x2 : x2 - x1;
    double deltaY = ((y1 - y2) > 0) ? y1 - y2 : y2 - y1;
    double epsilon = 0.000010;

    // x1 == x2 && y1 == y2
    if(deltaX < epsilon && deltaY < epsilon) 
        return 0;
    // x1 == x2 && y1 < y2
    else if(deltaX < epsilon && y1 < y2) 
        return -1;
    // x1 == x2 && y1 > y2
    else if(deltaX < epsilon && y1 > y2)
        return 1;
    else if(x1 < x2)
        return -1;
    else
        return 1;
}

Form newForm(String command) 
{
    if(command == NULL) return NULL;

    FORM *frm = (FORM *) malloc(sizeof(FORM));
    if(frm == NULL) 
    {
        printf("ERROR: Could not create new form\n");
        exit(EXIT_FAILURE);
    }

    String *splt = split(command, " ");

    // Coordenada âncora
    if(strcmp(splt[0], "l") == 0) 
    {
        double x1 = strtod(splt[2], NULL);
        double y1 = strtod(splt[3], NULL);
        double x2 = strtod(splt[4], NULL);
        double y2 = strtod(splt[5], NULL);

        if(comparePoints(x1, y1, x2, y2) == -1)
        {
            frm->x = x1;
            frm->y = y1;
        }
        else
        {
            frm->x = x2;
            frm->y = y2;
        }
    }
    else 
    {
        frm->x = strtod(splt[2], NULL);
        frm->y = strtod(splt[3], NULL);
    }

    // Condição
    frm->condition = alive;

    // Comando de criação
    frm->form = command;

    // Nível de proteção
    if(strcmp(splt[0], "c") == 0) 
        frm->protection = 60;
    else if(strcmp(splt[0], "r") == 0) 
        frm->protection = 60;
    else if(strcmp(splt[0], "l") == 0) 
        frm->protection = 50;
    else if(strcmp(splt[0], "t") == 0) 
        frm->protection = 5;

    for(int i = 0; splt[i] != NULL; i++) 
        free(splt[i]);
    free(splt);

    return frm;
}

double getFormX(Form form) 
{
    if(form == NULL) 
        return 0.0;

    FORM *frm = (FORM *) form;

    return frm->x;
}

double getFormY(Form form) 
{
    if(form == NULL) 
        return 0.0;

    FORM *frm = (FORM *) form;

    return frm->y;
}

int getFormProtection(Form form) 
{
    if(form == NULL) 
        return 0;

    FORM *frm = (FORM *) form;

    return frm->protection;
}

Condition getFormCondition(Form form) 
{
    if(form == NULL) 
        return inactive;

    FORM *frm = (FORM *) form;

    return frm->condition;
}

String getFormForm(Form form) 
{
    if(form == NULL) 
        return NULL;

    FORM *frm = (FORM *) form;

    return frm->form;
}

void destroyForm(Form form)
{
    if(form == NULL)
        return;
    
    FORM *forma = (FORM *) form;

    if(forma->form != NULL)
        free(forma->form);
    free(forma);

    form = NULL;
}
