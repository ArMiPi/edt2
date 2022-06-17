#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qry.h"
#include "forms.h"
#include "svg.h"
#include "list.h"

#define MAX_SIZE 100

/*
    # Entradas:
        - path: Path para a criação do arquivo
        - name: Nome do arquivo (sem extensão)
    
    # Saída:
        - FILE*: Ponteiro para arquivo
    
    # Descrição:
        - Abre um arquivo name.txt em path para
          escrita
*/
FILE *createTXT(String path, String name)
{
    if(path == NULL || name == NULL) 
        return NULL;

    // Gerar caminho completo para criação do arquivo
    String fullname = concat(name, ".txt");
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

    free(fullpath);

    return fptr;
}

/*
    # Entradas:
        - txt: Ponteiro para um arquivo .txt
        - command: String contendo um comando do .qry
        - toReport: String contendo o conteúdo a ser escrito no .txt
    
    # Descrição:
        - Escreve os conteúdos de command e toReport em txt
        - txt != NULL
*/
void reportTXT(FILE *txt, String command, String toReport)
{
    if(txt == NULL) 
        return;

    if(command != NULL) 
        fprintf(txt, "[*] %s\n", command);
    if(toReport != NULL) 
        fprintf(txt, "%s\n", toReport);
    if(command == NULL && toReport == NULL)
        fprintf(txt, "\n");
}

/*
    # Entradas:
        - x, y: Coordenada
        - txt: Arquivo txt
        - database: Árvore contendo as formas
        - extras: Lista contendo pontos e áreas adicionais geradas dos comandos do .qry
    
    # Descrição:
        - Remover todas as formas para as quais o ponto (x, y) é interno
            
        - TXT: Reportar todas as informações das formas removidas

        - SVG: Marcar o ponto (x, y) com um asterisco vermelho (em caso de acerto),
               ou cinza (em caso de erro)

               Caso mais de uma forma tenha sido atingida, colocar o número de formas
               atingidas ao lado do ponto

*/
void tp(double x, double y, FILE *txt, XyyTree database, List extras)
{
    if(database == NULL)
        return NULL;

    List hit = getInfosAtingidoPontoXyyT(database, x, y, &isPointInsideForm);

    // Adicionar informações no .txt
    Form form;
    int atingidos = 0;
    for(Node node = getFirstItem(hit); node != NULL; node = getNextItem(node))
    {
        form = getInfoXyyT(database, node);

        reportTXT(txt, NULL, reportForm(form));
        damageFormProtection(form, -1.0);

        atingidos++;
    }
    if(atingidos == 0)
        reportTXT(txt, NULL, "AGUA\n");
    reportTXT(txt, NULL, NULL);

    // Adicionar ponto no .svg
    String cor = (atingidos == 0) ? "grey" : "red";
    String command = newEmptyString(MAX_SIZE);
    sprintf(command, "t -1 %lf %lf %s %s i *", x, y, cor, cor);

    insertEnd(extras, newForm(command));

    if(atingidos > 1)
    {
        command = newEmptyString(MAX_SIZE);
        sprintf(command, "t -1 %lf %lf %s %s i %d", x+1, y, cor, cor, atingidos);
    }

    insertEnd(extras, newForm(command));

    destroyList(hit, NULL);
}

/*
    # Entradas:
        - x, y: Coordenada
        - dx, dy: Unidades de transladamento
        - id: Identificador inicial
        - txt: Arquivo txt
        - database: Árvore contendo as formas
        - extras: Lista contendo pontos e áreas adicionais geradas dos comandos do .qry
    
    # Descrição:
        - Cria um clone para cada uma das formas que possuem o ponto interno (x, y)

        - As novas formas são transladados de (dx, dy) de seu original

        - O nível de proteção é o mesmo do original e as cores de borda e preenchimento são
          intercambiadas

        - O id das novas formas deve começar no valor id

        - TXT: Reportar todos os dados das formas clonadas e de seus clones

        - SVG: Colocar um @ no ponto (x, y)  

*/
void tr(double x, double y, double dx, double dy, int id, FILE *txt, XyyTree database, List extras)
{
    if(database == NULL)
        return NULL;
    
    List hit = getInfosAtingidoPontoXyyT(database, x, y, &isPointInsideForm);

    Form form, formToInsert;
    for(Node node = getFirstItem(hit); node != NULL; node = getNextItem(node))
    {
        form = getItemElement(node);

        formToInsert = createClone(form, dx, dy, id);
        id++;

        insertXyyT(database, getFormX(formToInsert), getFormY(formToInsert), formToInsert);

        reportTXT(txt, NULL, "ORIGINAL:\n");
        reportTXT(txt, NULL, reportForm(form));
        reportTXT(txt, NULL, "COPY:\n");
        reportTXT(txt, NULL, reportForm(formToInsert));
    }

    String at = newEmptyString(MAX_SIZE);
    sprintf(at, "t -1 %lf %lf black black i @", x, y);

    insertEnd(extras, at);

    destroyList(hit, NULL);
}

/*
    # Entradas:
        - x, y: Coordenada
        - w: Largura
        - h: Altura
        - agressividade: Agressividade
        - txt: Arquivo txt
        - database: Árvore contendo as formas
        - extras: Lista contendo pontos e áreas adicionais geradas dos comandos do .qry
    
    # Descrição:
        - Formas inteiramente contidas na região devem ter seu nível de proteção diminuído
          proporcionalmente (Redução = (Agressividade * Area(equipamento)) / Area(região))
          Area(texto) = 0.1; Area(linha) = 0.1 * Comprimento(linha)
        
        - Formas cujo nível de proteção atingir 0 devem ser removidas

        - TXT: Reportar todos os dados das formas atingidas
               Acrescentar REMOVIDA às formas removidas

        - SVG: Desenhar a regiãp com contorno vermelho e sem preenchimento
               Por um ponto vermelho na posição das âncoras das formas atingidas


*/
void be(double x, double y, double w, double h, double agressividade, FILE *txt, XyyTree database, List extras)
{
    if(database == NULL)
        return NULL;

    List hit = getInfosDentroRegiaoXyyT(database, x, y, w, h, &isFormInsideArea);

    double reduction, area;
    String command;
    Form form;
    for(Node node = getFirstItem(hit); node != NULL; node = getNextItem(node))
    {
        form = getItemElement(node);

        area = getFormArea(form);
        reduction = agressividade * area / (w * h);
        damageFormProtection(form, reduction);

        if(getFormCondition(form) == inactive)
            reportTXT(txt, NULL, "[REMOVIDA]");
        reportTXT(txt, NULL, reportForm(form));

        // Adicionar círculos vermelhos nos pontos âncora das formas atingidas
        command = newEmptyString(MAX_SIZE);
        sprintf(command, "c -1 %lf %lf 1.00 red red", getFormX(form), getFormY(form));

        insertEnd(extras, newForm(command));
    }

    command = newEmptyString(MAX_SIZE);
    sprintf(command, "r -1 %lf %lf %lf %lf red none", x, y, w, h);

    insertEnd(extras, newForm(command));
}

void executeQry(String BSD, String geoName, String qryName, XyyTree database) {
    if(BSD == NULL || geoName == NULL || qryName == NULL || database == NULL) 
        return;
    
    // String a ser inserida no .txt
    String toReport;

    // Nome dos arquivos .txt e .svg resultantes da consulta
    String *name = split(qryName, "/");
    String names[2];
    names[0] = geoName;
    names[1] = getSubstring(name, getNumSubstrings(name)-1);

    String resultName = join(2, names, "-");

    destroySplited(name);
    
    // txt de saída utilizado por algumas qrys
    FILE *txt = createTXT(BSD, resultName);

    // Abrir o .qry
    String fullpath;
    if(endsWith(BSD, "/")) 
        fullpath = concat(BSD, qryName);
    else 
    {
        String barPath = concat(BSD, "/");
        fullpath = concat(barPath, qryName);
        free(barPath);
    }

    FILE *qry = fopen(fullpath, "r");
    if(qry == NULL)
    {
        printf("ERROR: Could not open %s\n", fullpath);
        return;
    }
    free(fullpath);

    // Nível de Agressividade
    double agressividade = 0.0;

    // Lista contendo os "extras" gerados pelos comandos do .qry
    List extras = newList();

    // Executar os comandos do .qry
    String *splt;
    String command = newEmptyString(MAX_SIZE);
    while (fgets(command, MAX_SIZE, qry))
    {
        splt = split(command, " ");

        if(strcmp(splt[0], "na") == 0)
        {
            reportTXT(txt, command, NULL);
            agressividade = strtod(splt[1], NULL);
        }
        else if(strcmp(splt[0], "tp") == 0)
        {
            reportTXT(txt, command, NULL);
            tp(strtod(splt[1], NULL), strtod(splt[2], NULL), txt, database, extras);
        }
        else if(strcmp(splt[0], "tr") == 0)
        {
            reportTXT(txt, command, NULL);
            tr(strtod(splt[1], NULL), strtod(splt[2], NULL), strtod(splt[3], NULL), strtod(splt[4], NULL), atoi(splt[5]), txt, database, extras);
        }
        else if(strcmp(splt[0], "be") == 0)
        {
            reportTXT(txt, command, NULL);
            be(strtod(splt[1], NULL), strtod(splt[2], NULL), strtod(splt[3], NULL), strtod(splt[4], NULL), agressividade, txt, database, extras);
        }
        else
            printf("ERROR: Unkown command\n");

        // Liberar a memória utilizada por splt
        for(int i = 0; splt[i] != NULL; i++)
            free(splt[i]);
        free(splt);
    }

    // Calcular as pontuações e inserir no .txt

    // Fechar arquivos
    fclose(txt);
    fclose(qry);

    // Criar o svg resultante das qrys
    generateSVG(BSD, resultName, database, extras);

    free(resultName);
    free(command);
}