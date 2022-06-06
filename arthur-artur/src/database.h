#ifndef DATABASE_H
#define DATABASE_H

#include "strings.h"
#include "xyytree.h"

/*
    - Esse módulo tem por objetivo definir funções para ler e armazenar
      os comandos dos arquivos .geo . qry

    - Todas as funções que recebem Database como entrada assumeme
      Database != NULL
*/

typedef void* Database;

/*
    # Entradas:
        - path: Path para o arquivo
        - name: Nome do arquivo (com extensão)
    
    # Saída:
        - Database: Struct
    
    # Descrição:
        - Abre o arquivo em path/name, armazena os comandos
          contidos nesse arquivo e fecha o arquivo
        
        - path != NULL && name != NULL

        - É necessário liberar a memória utilizada pelo retorno dessa função
*/
Database readData(String path, String name);

/*
    # Entrada:
        - db: Dados
    
    # Saída:
        - string: char*
    
    # Descrição:
        - Retorna o nome do arquivo(sem extensão) do qual
          os comandos armazenados em db foram lidos
*/
String getDBname(Database db);

/*
    # Entrada:
        - db: Struct
    
    # Saída:
        - XyyTree: Árvore
    
    # Descrição:
        - Retorna uma lista contendo os comandos armazenados
          em db
*/
XyyTree getDBdata(Database db);

/*
    # Entrada:
        - db: Struct
    
    # Descrição:
        - Libera a memória utilizada por db
*/
void destroyDB(Database db);

#endif