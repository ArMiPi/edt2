#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qry.h"
#include "forms.h"
#include "svg.h"

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

    if(command == NULL) 
        command = "NULL";

    fprintf(txt, "[*] %s\n", command);
    if(toReport != NULL) 
        fprintf(txt, "%s\n\n", toReport);
}

/*
    # Entradas:
        - v: Nível de agressividade
        - database: Árvore contendo as formas
    
    # Descrição:
        - Atribui o nível de agressividade v às regiões de ataque

*/
void na(double v, XyyTree database) 
{

}

/*
    # Entradas:
        - x, y: Coordenada
        - database: Árvore contendo as formas
    
    # Saída:
        - String: Contém as informações a serem reportadas no .txt
    
    # Descrição:
        - Remover todas as formas para as quais o ponto (x, y) é interno
            
        - SVG: Marcar o ponto (x, y) com um asterisco vermelho (em caso de acerto),
               ou cinza (em caso de erro)

*/
String tp(double x, double y, XyyTree database) 
{

}

/*
    # Entradas:
        - x, y: Coordenada
        - dx, dy: Unidades de transladamento
        - id: Identificador inicial
        - database: Árvore contendo as formas
    
    # Saída:
        - String: Contém todos os dados das formas clonadas e de seus clones
    
    # Descrição:
        - Cria um clone para cada uma das formas que possuem o ponto interno (x, y)

        - As novas formas são transladados de (dx, dy) de seu original

        - O nível de proteção é o mesmo do original e as cores de borda e preenchimento são
          intercambiadas

        - O id das novas formas deve começar no valor id

        - SVG: Colocar um @ no ponto (x, y)  

*/
String tr(double x, double y, double dx, double dy, int id, XyyTree database) 
{

}

/*
    # Entradas:
        - x, y: Coordenada
        - w: Largura
        - h: Altura
        - database: Árvore contendo as formas
    
    # Saída:
        - String: Contém todos os dados das formas atingidas, acrescentar
                  REMOVIDA para as formas removidas
    
    # Descrição:
        - Formas inteiramente contidas na região devem ter seu nível de proteção diminuído
          proporcionalmente (Redução = (Agressividade * Area(equipamento)) / Area(região))
          Area(texto) = 0.1; Area(linha) = 0.1 * Comprimento(linha)
        
        - Formas cujo nível de proteção atingir 0 devem ser removidas

        - SVG: Desenhar a regiãp com contorno vermelho e sem preenchimento
               Por um ponto vermelho na posição das âncoras das formas atingidas


*/
String be(double x, double y, double w, double h, XyyTree database) 
{

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

    // Executar os comandos do .qry
    String *splt;
    String command = newEmptyString(MAX_SIZE);
    while (fgets(command, MAX_SIZE, qry))
    {
        splt = split(command, " ");

        if(strcmp(splt[0], "na") == 0)
        {
            na(strtod(splt[1], NULL), database);
        }
        else if(strcmp(splt[0], "tp") == 0)
        {
            toReport = tp(strtod(splt[1], NULL), strtod(splt[2], NULL), database);
            reportTXT(txt, command, toReport);
        }
        else if(strcmp(splt[0], "tr") == 0)
        {
            toReport = tr(strtod(splt[1], NULL), strtod(splt[2], NULL), strtod(splt[3], NULL), strtod(splt[4], NULL), atoi(splt[5]), database);
            reportTXT(txt, command, toReport);
        }
        else if(strcmp(splt[0], "be") == 0)
        {
            toReport = be(strtod(splt[1], NULL), strtod(splt[2], NULL), strtod(splt[3], NULL), strtod(splt[4], NULL), database);
            reportTXT(txt, command, toReport);
        }
        else
            printf("ERROR: Unkown command\n");
    }

    if(txt != NULL) fclose(txt);

    // Criar o svg resultante das qrys
    generateSVG(BSD, resultName, database);

    free(resultName);
}