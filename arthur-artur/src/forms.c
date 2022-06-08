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

    frm->x = strtod(splt[2], NULL);
    frm->y = strtod(splt[3], NULL);
    frm->condition = alive;
    frm->form = command;

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
