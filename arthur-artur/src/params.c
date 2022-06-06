#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "params.h"

typedef struct _params
{
    String BED;
    String GEO;
    String BSD;
    String QRY;
}PARAMS;

/*
    # Descrição:
        - Imprime a mensagen informando as informações sobre a chamada do programa
          e finaliza o mesmo
*/
void help() 
{
    printf("Parâmetro / Argumento | Opcional |                Descrição\n");
    printf("-e path               |    S     | Diretório-base de entrada(BED)*\n");
    printf("-f arq.geo            |    N     | Arquivo com as formas. Este arquivo deve estar sob BED\n");
    printf("-o path               |    N     | Diretório base de saída(BSD)\n");
    printf("-q arqcons.qry        |    S     | Arquivo com consultas. Este arquivo deve estar sob BSD\n");
    printf("\n *-> Se -e não for passado, o diretório atual será considerado como BED\n");

    exit(EXIT_SUCCESS);
}

/*
    # Saída:
        - PARAMS* -> Ponteiro
    
    # Descrição:
        - Retorna um ponteiro para PARAMS com todos os
          valores iniciados com NULL
*/
PARAMS *emptyParams() 
{
    PARAMS *args = (PARAMS *) malloc(sizeof(PARAMS));
    if(args == NULL) 
    {
        printf("ERROR: Could not allocate memory for empty params\n");
        exit(EXIT_FAILURE);
    }

    args->BED = NULL;
    args->BSD = NULL;
    args->GEO = NULL;
    args->QRY = NULL;

    return args;
}

Params newParams(int argc, char *argv[]) 
{    
    if(argc == 1) 
    {
        printf("-h for help\n");
        exit(EXIT_SUCCESS);
    }

    if(strcmp(argv[1], "-h") == 0) 
        help();

    PARAMS *args = emptyParams();

    for(int i = 1; i < argc; i++) 
    {
        if(strcmp(argv[i], "-e") == 0)
        {
            i++;
            args->BED = copyString(argv[i]);
        }
        else if(strcmp(argv[i], "-f") == 0)
        {
            i++;
            args->GEO = copyString(argv[i]);
        }
        else if(strcmp(argv[i], "-o") == 0)
        {
            i++;
            args->BSD = copyString(argv[i]);
        }
        else if(strcmp(argv[i], "-q") == 0)
        {
            i++;
            args->QRY = copyString(argv[i]);
        }
        else printf("ERROR: Invalid parameter -> %s\n", argv[i]);
    }

    if(args->GEO == NULL || args->BSD == NULL)
    {
        printf("ERROR: Missing not optional parameter\n");
        printf("-h for help\n");

        exit(EXIT_FAILURE);
    }
    if(args->BED == NULL) 
        args->BED = copyString("./");

    return args;
}

String getBED(Params prms)
{
    if(prms == NULL)
        return NULL;
    
    PARAMS *args = (PARAMS *) prms;

    return args->BED;
}

String getGEO(Params prms)
{
    if(prms == NULL) 
        return NULL;

    PARAMS *args = (PARAMS *) prms;

    return args->GEO;
}

String getBSD(Params prms)
{
    if(prms == NULL)
        return NULL;

    PARAMS *args = (PARAMS *) prms;

    return args->BSD;
}

String getQRY(Params prms)
{
    if(prms == NULL) 
        return NULL;

    PARAMS *args = (PARAMS *) prms;

    return args->QRY;
}

void destroyParams(Params prms)
{
    if(prms == NULL)
        return;

    PARAMS *args = (PARAMS *) prms;

    if(args->BED != NULL) 
        free(args->BED);
    free(args->GEO);
    free(args->BSD);
    if(args->QRY != NULL) 
        free(args->QRY);

    free(prms);

    args = NULL;
    prms = NULL;
}