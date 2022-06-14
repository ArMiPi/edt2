#ifndef QRY_H
#define QRY_H

#include "xyytree.h"
#include "strings.h"

/*
    - Esse módulo tem por objetivo implementar os comandos do .qry
*/

/*
    # Entradas:
        - BSD: Diretório base de saída
        - geoName: Nome do arquivo .geo
        - qryName: Nome do arquivo .qry
        - database: Árvore contendo os comandos do .geo
    
    # Descrição:
        - Realiza os comandos do .qry e gera os aquivos
          resultantes
*/
void executeQry(String BSD, String geoName, String qryName, XyyTree database);

#endif