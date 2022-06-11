#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILL_OPACITY "0.5"
#define FONT_SIZE "5"
#define LINE_HEIGHT "0"
#define STROKE_WIDTH "2"

#include"svg.h"

/*
    # Entradas:
        - path: Path para a criação do arquivo
        - name: Nome do arquivo (sem extensão)
    
    # Saída:
        - FILE*: Ponteiro para arquivo
    
    # Descrição:
        - Abre um arquivo name.svg em path para
          escrita
*/
FILE *createSVG(String path, String name)
{
    // Gerar caminho completo para criação do arquivo
    String fullname = concat(name, ".svg");
    String fullpath;
    if(endsWith(path, "/")) 
        fullpath = concat(path, fullname);
    else 
    {
        String barPath = concat(path, "/");
        fullpath = concat(barPath, fullname);
        free(barPath);
    }
    free(fullname);

    FILE *fptr = fopen(fullpath, "w");
    if(fptr == NULL) 
        printf("WARNING: Could not create %s\n", fullpath);

    if(fptr != NULL) 
    {
        fprintf(fptr, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
    }

    free(fullpath);

    return fptr;
}

/*
    # Entradas:
        - fptr: Ponteiro para arquivo de escrita
        - splt: Matriz de strings contendo os parâmetros de
                criação de uma forma
    
    # Descrição:
        - Cria um cŕiculo em fptr com as informações em
          splt
*/
void drawCircle(FILE *fptr, String *splt) 
{
    if(fptr == NULL || splt == NULL) 
        return;

    String x = getSubstring(splt, 2);
    String y = getSubstring(splt, 3);
    String r = getSubstring(splt, 4);
    String corb = getSubstring(splt, 5);
    String corp = getSubstring(splt, 6);

    fprintf(fptr, "\t<circle style=\"fill:%s; fill-opacity:%s; ", corp, FILL_OPACITY);
    fprintf(fptr, "stroke=%s; stroke-width=%s;\" ", corb, STROKE_WIDTH);
    fprintf(fptr, "r=\"%s\" ", r);
    fprintf(fptr, "cy=\"%s\" ", y);
    fprintf(fptr, "cx=\"%s\" />\n", x);
}

/*
    # Entradas:
        - fptr: Ponteiro para arquivo de escrita
        - splt: Matriz de strings contendo os parâmetros de
                criação de uma forma
    
    # Descrição:
        - Cria um retângulo em fptr com as informações em
          splt
*/
void drawRectangle(FILE *fptr, String *splt) 
{
    if(fptr == NULL || splt == NULL) 
        return;

    String x = getSubstring(splt, 2);
    String y = getSubstring(splt, 3);
    String w = getSubstring(splt, 4);
    String h = getSubstring(splt, 5);
    String corb = getSubstring(splt, 6);
    String corp = getSubstring(splt, 7);

    fprintf(fptr, "\t<rect style=\"fill:%s; fill-opacity:%s; ", corp, FILL_OPACITY);
    fprintf(fptr, "stroke:%s\" ", corb);
    fprintf(fptr, "height=\"%s\" ", h);
    fprintf(fptr, "width=\"%s\" ", w);
    fprintf(fptr, "y=\"%s\" ", y);
    fprintf(fptr, "x=\"%s\" />\n", x);
}

/*
    # Entradas:
        - fptr: Ponteiro para arquivo de escrita
        - splt: Matriz de strings contendo os parâmetros de
                criação de uma forma
    
    # Descrição:
        - Cria uma reta em fptr com as informações em
          splt
*/
void drawLine(FILE *fptr, String *splt) 
{
    if(fptr == NULL || splt == NULL) 
        return;

    String x1 = getSubstring(splt, 2);
    String y1 = getSubstring(splt, 3);
    String x2 = getSubstring(splt, 4);
    String y2 = getSubstring(splt, 5);
    String cor = getSubstring(splt, 6);

    fprintf(fptr, "\t<line x1=\"%s\" y1=\"%s\" ", x1, y1);
    fprintf(fptr, "x2=\"%s\" y2=\"%s\" ", x2, y2);
    fprintf(fptr, "style=\"stroke:%s; stroke-width:%s\" />\n", cor, STROKE_WIDTH);
}

/*
    # Entradas:
        - fptr: Ponteiro para arquivo de escrita
        - splt: Matriz de strings contendo os parâmetros de
                criação de uma forma
    
    # Descrição:
        - Cria um texto em fptr com as informações em
          splt
*/
void drawText(FILE *fptr, String *splt) 
{
    if(fptr == NULL || splt == NULL) 
        return;

    String x = getSubstring(splt, 2);
    String y = getSubstring(splt, 3);
    String corb = getSubstring(splt, 4);
    String corp = getSubstring(splt, 5);
    String a = getSubstring(splt, 6);
    String *content = getAllSubstrings(splt);
    content += 7;
    String txto = join((getNumSubstrings(splt) - 7), content, " ");

    String anchor;
    if(strcmp(a, "i") == 0) 
        anchor = "start";
    else if(strcmp(a, "m") == 0) 
        anchor = "middle";
    else if(strcmp(a, "f") == 0) 
        anchor = "end";

    fprintf(fptr, "\t<text text-anchor=\"%s\" x=\"%s\" y=\"%s\" ", anchor, x, y);
    fprintf(fptr, "style=\"fill:%s; fill-opacity:%s; ", corp, FILL_OPACITY);
    fprintf(fptr, "stroke:%s; stroke-width:%s;\"", corb, STROKE_WIDTH);
    fprintf(fptr, ">%s</text>\n", txto);

    free(txto);
}

void generateSVG(String path, String name, XyyTree data) 
{
    if(path == NULL || name == NULL || data == NULL) 
        return;

    FILE *fptr = createSVG(path, name);
    if(fptr == NULL) 
        return;

    String *splt;
    // TODO: Percorrer árvore lendo os comandos e inserindo eles no .svg

    fprintf(fptr, "</svg>");

    fclose(fptr);
}