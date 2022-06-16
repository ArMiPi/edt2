#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"forms.h"

typedef struct _form 
{
    double x, y;            // Ponto âncora da figura
    double protection;      // Nível de proteção da figura
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
        frm->protection = 60.0;
    else if(strcmp(splt[0], "r") == 0) 
        frm->protection = 60.0;
    else if(strcmp(splt[0], "l") == 0) 
        frm->protection = 50.0;
    else if(strcmp(splt[0], "t") == 0) 
        frm->protection = 5.0;

    for(int i = 0; splt[i] != NULL; i++) 
        free(splt[i]);
    free(splt);

    return frm;
}

/*
    # Entrada:
        command: Instrução do .geo
    
    # Saída:
        - string
    
    # Descrição:
        - Retorna uma string contendo o tipo da forma em command

        - c -> circulo
        - r -> retangulo
        - l -> reta
        - t -> texto
*/
String getFormType(String command) {
    if(command == NULL) return NULL;

    String *splt = split(command, " ");
    String type = splt[0];

    if(strcmp(type, "c") == 0) type = copyString("circulo");
    else if(strcmp(type, "r") == 0) type = copyString("retangulo");
    else if(strcmp(type, "l") == 0) type = copyString("reta");
    else if(strcmp(type, "t") == 0) type = copyString("texto");
    else {
        printf("WARNING: %s is not a valid form\n", type);
        type = NULL;
    }

    for(int i = 0; splt[i] != NULL; i++)
        free(splt[i]);
    free(splt);

    return type;
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

double getFormProtection(Form form) 
{
    if(form == NULL) 
        return 0;

    FORM *frm = (FORM *) form;

    return frm->protection;
}

void damageFormProtection(Form form, double damage)
{
    if(form == NULL)
        return;

    FORM *frm = (FORM *) form;

    // Caso seja um torpedo
    if(damage < 0)
    {
        frm->protection = 0.0;
        frm->condition = destroyed;
        return;
    }

    frm->protection -= damage;

    if(frm->protection <= 0)
        frm->condition = inactive;
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

bool isPointInsideForm(Form form, double x, double y)
{
    if(form == NULL)
        return false;
    
    // Dados comuns
    double xF = getFormX(form);
    double yF = getFormY(form);
    bool inside = true;

    // Identificar a forma
    String command = split(getFormForm(form), " ");
    if(strcmp(command[0], "c") == 0)
    {
        double radius = strtod(command[4], NULL);

        if(x > xF + radius || x < xF - radius)
            inside = false;
        if(y > yF + radius || y < yF - radius)
            inside = false;
    }
    else if(strcmp(command[0], "r") == 0)
    {
        double width = strtod(command[4], NULL);
        double heigth = strtod(command[5], NULL);

        if(x > xF + width || x < xF)
            inside = false;
        if(y > yF + heigth || y < yF)
            inside = false;
    }
    else if(strcmp(command[0], "l") == 0)
    {
        xF = strtod(command[2], NULL);
        yF = strtod(command[3], NULL);
        double xL = strtod(command[4], NULL);
        double yL = strtod(command[5], NULL);

        double epsilon = 0.000010;
        double yT = ((yF - yL) * (x - xL) / (xF - xL)) + yL;

        yT = ((yT -y) > 0) ? yT-y : y - yT;
        inside = (yT < epsilon);
    }
    else if(strcmp(command[0], "t") == 0)
    {
        double epsilon = 0.000010;
        xF = ((xF -x) > 0) ? xF-x : x - xF;
        yF = ((yF -y) > 0) ? yF-y : y - yF;
        inside = (xF < epsilon) && (yF < epsilon);
    }

    // Liberar a memória utilizada por command
    for(int i = 0; command[i] != NULL; i++)
        free(command[i]);
    free(command);

    return inside;
}

String reportForm(Form form)
{
    if(form == NULL)
        return NULL;

    String command = getFormForm(form);
    String *splt = split(command, " ");

    String type = getFormType(command);
    String temp = newEmptyString(100);
    String report;

    if(strcmp(type, "circulo") == 0) {
        String x = splt[2];
        String y = splt[3];
        String raio = splt[4];
        String preenchimento = splt[5];
        String borda = splt[6];

        sprintf(temp, "%s\nancora em {%s, %s}\nraio: %s\npreenchimento: %s\nborda: %s\nprotecao: %lf\n", type, x, y, raio, preenchimento, borda, getFormProtection(form));
    }
    else if(strcmp(type, "retangulo") == 0) {
        String x = splt[2];
        String y = splt[3];
        String width = splt[4];
        String height = splt[5];
        String preenchimento = splt[6];
        String borda = splt[7];

        sprintf(temp, "%s\nancora em {%s, %s}\nlargura: %s\naltura: %s\npreenchimento: %s\nborda: %s\nprotecao: %lf\n", type, x, y, width, height, preenchimento, borda, getFormProtection(form));
    }
    else if(strcmp(type, "reta") == 0) {
        String x1 = splt[2];
        String y1 = splt[3];
        String x2 = splt[4];
        String y2 = splt[5];

        String cor = splt[6];

        sprintf(temp, "%s\nP1: {%s, %s}\nP2: {%s, %s}\ncor: %s\nprotecao: %lf\n", type, x1, y1, x2, y2, cor, getFormProtection(form));
    }
    else if(strcmp(type, "texto") == 0) {
        String x = splt[2];
        String y = splt[3];
        String borda = splt[4];
        String preenchimento = splt[5];
        String anchorPos = splt[6];
        String *content = splt;
        content += 7;
        int quantity = 0;
        for(; content[quantity] != NULL; quantity++);
        String txto = join(quantity, content, " ");

        sprintf(temp, "%s\nancora em {%s, %s}\nborda: %s\npreenchimento: %s\na: %s\ntexto: %s\nprotection: %lf\n", type, x, y, borda, preenchimento, anchorPos, txto, getFormProtection(form));
        
        free(txto);
    }

    report = copyString(temp);
    free(temp);
    for(int i = 0; splt[i] != NULL; i++)
        free(splt[i]);
    free(splt);

    return report;
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
