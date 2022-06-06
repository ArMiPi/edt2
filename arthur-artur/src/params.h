#ifndef PARAMS_H
#define PARAMS_H

#include"strings.h"

/*
    - Este módulo tem como objetivo controlar os parâmetros de chamada
      do programa principal, verificando se todos os parâmetros obrigatórios
      foram passados e armazenado os argumentos de todos os parâmetros
      passados

    - Em todas as funções que recebem params como argumento, params != NULL

    - Parâmetro / Argumento | Opcional |                Descrição
      -e path               |    S     | Diretório-base de entrada(BED)
      -f arq.geo            |    N     | Arquivo com as formas. Este arquivo deve estar sob BED
      -o path               |    N     | Diretório base de saída(BSD)
      -q arqcons.qry        |    S     | Arquivo com consultas. Este arquivo deve estar sob BSD
*/

typedef void *Params;

/*
    # Entradas:
        - argc -> Quantidade de argumentos passados na chamada do programa
        - argv -> Vetor contendo os argumentos
    
    # Saída:
        - Params -> Struct
    
    # Descrição:
        - Retorna uma struct contendo os valores dos argumentos dos parâmetros
          de entrada
        - É necessário desalocar a memória utilizada pelo retorno dessa função
          usando a função destroyParams
*/
Params newParams(int argc, char *argv[]);

/*
    # Entradas:
        - prms -> Struct criada com a função newParams
    
    # Saída:
        - String -> Ponteiro
    
    # Descrição:
        - Retorna ponteiro para o endereço contendo o 
          argumento do parâmetro -e
*/
String getBED(Params prms);

/*
    # Entradas:
        - prms -> Struct criada com a função newParams
    
    # Saídas:
        - String -> Ponteiro
        - NULL
    
    # Descrição;
        - Retorna ponteiro para o endereço contendo o 
          argumento do parâmetro -f
        - Retorna NULL caso o parâmetro não tenha sido informado na
          chamada do programa principal
*/
String getGEO(Params prms);

/*
    # Entradas:
        - prms -> Struct criada com a função newParams
    
    # Saídas:
        - String -> Ponteiro
        - NULL
    
    # Descrição:
        - Retorna ponteiro para o endereço contendo o 
          argumento do parâmetro -o
        - Retorna NULL caso o parâmetro não tenha sido informado na
          chamada do programa principal
*/
String getBSD(Params prms);

/*
    # Entradas:
        - prms -> Struct criada com a função newParams
    
    # Saída:
        - string -> Ponteiro
    
    # Descrição:
        - Retorna ponteiro para o endereço contendo o
          argumento do parâmetro -q
*/
String getQRY(Params prms);

/*
    # Entradas:
        - prms -> Struct criada com a função newParams
    
    # Descrição:
        - Libera toda a memória utilizada por prms
*/
void destroyParams(Params prms);

#endif