#ifndef STRINGS_H
#define STRINGS_H

#include <stdbool.h>

/*
    - Esse módulo tem por objetivo implementar um tipo string,
      bem como funções para trabalhar com esse tipo

    - Todas as strings utilizadas nas chamadas das funções devem
      ser != NULL
*/

typedef char* String;

/*
    # Entrada:
        - size: Tamanho a ser armazenado (Não incluir \0)
    
    # Saída:
        - string: char *
    
    # Descrição:
        - Retorna um ponteiro com capacidade para size caracteres;

        - É necessário desalocar a memória utilizada pelo
          retorno dessa função
*/
String newEmptyString(int size);

/*
    # Entrada:
        - str: String
    
    # Saída:
        - string: char *
    
    # Descrição:
        - Cria uma string com conteúdo str;

        - É necessário desalocar a memória utilizada pelo
          retorno dessa função
*/
String copyString(String str);

/*
    # Entradas:
        - str1, str2: Strings

    # Saída:
        - string: char *

    # Descrição:
        - Retorna uma string onde str2 é concatenada ao final de str1

        - É necessário desalocar a memória utilizada pelo
          retorno dessa função
*/
String concat(String str1, String str2);

/*
    # Entradas:
        - str1: String
        - start: Posição inicial
        - end: Posição final
    
    # Saídas:
        - string: char*
        - NULL
    
    # Descrição:
        - Retorna uma string contendo o conteúdo de
          str das posições start à end
        
        - Ex: slice("example", 2, 5) -> "ampl"

        - start && end devem estar dentro dos limites {0, strlen(str)}

        - É necessário desalocar a memória utilizada pelo retorno dessa
          função
*/
String slice(String str, int start, int end);

/*
    # Entradas:
        - str1, str2: Strings
    
    # Saídas:
        - bool
    
    # Descrição:
        - Retorna true se str1 iniciar com str2, false caso contrário
*/
bool startsWith(String str1, String str2);

/*
    # Entradas:
        - str1, str2: Strings
    
    # Saídas:
        - bool
    
    # Descrição:
        - Retorna true se str1 terminar com str2, false caso contrário
*/
bool endsWith(String str1, String str2);

/*
    # Entradas:
        - str1, str2: Strings
    
    # Saídas:
        - -1
        - int >= 0 < strlen(str1)
    
    # Saídas:
        - Retorna -1 se str1 não possuir str2, ou retorna
          a primeira posição em str1 na qual str2 inicia
        
        - Ex: contains("example", "amp") -> 2
*/
int contains(String str1, String str2);

/*
    # Entradas:
        - origin: string de origem
        - separator: string que será utilizada
                     separar origin
                    
    # Saída:
        - string*: Vetor de stirng
    
    # Descrição:
        - origin será separado em sub-strings tendo separator como
          elemento separador de string

        - As substrings serão armazenadas em uma matriz, onde o
          último elemento da string será NULL
        
        - origin != NULL e strlen(origin) > 0

        - Se separator != NULL, strlen(separator) > 0

        - É necessário desalocar a memória utilizada pelo
          retorno dessa função
*/
String *split(String origin, String separator);

/*
    # Entradas:
        - num_strings: Quantidade de strings
        - strings: Vetor de strings
        - joiner: string
    
    # Saída:
        - string: char *
    
    # Descrição:
        - Retorna uma string unindo todas as strings
          de strings com joiner sendo colocado entre
          elas

        - É necessário desalocar a memória utilizada pelo
          retorno dessa função
*/
String join(int num_strings, String *strings, String joiner);

/*
    # Entradas:
        - origin: String base
        - limit: String limite
    
    # Saída:
        - string
    
    # Descrição:
        - Retorna uma string contendo todos os elementos
          de origin até a primeira ocorrência de limit
        
        - origin != NULL && limit != NULL

        - strlen(limit) > 0

        - EX: origin = "string de teste"
              limit = "e"
              saida = "string d"
        
        - É necessário desalocar a memória utilizada pelo
          retorno dessa função
*/
String copyUntil(String origin, String limit);

#endif
