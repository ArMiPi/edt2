#ifndef SVG_H
#define SVG_H

#include "strings.h"
#include "xyytree.h"
#include "list.h"

/*
    - Esse módulo tem por objetivo criar um arquivo .svg a partir
      de instruções com o formato das presentes em um arquivo .geo

    - Comando       Parâmetros               Forma
        c       i x y r corb corp           Círculo
        r       i x y w h corb corp         Retângulo
        l       i x1 y1 x2 y2 cor           Linha
        t       i x y corb corp a txto      Texto
    
    Parâmetros:
        -> i: Id único (inteiro)
        -> (x, y)/(x1, y1): Coordenada âncora (double)
        -> (x2, y2): Ponto final (double)
        -> r: Raio (double)
        -> w: Largura (double)
        -> h: Altura (double)
        -> corb: Cor da borda (string)
        -> corp: Cor de preenchimento (string)
        -> a: Posição da âncora no texto (i/m/f) (string)
        -> txto: Texto (string)
*/

/*
    # Entradas:
        - path: Path onde o arquivo será criado
        - name: Nome do arquivo que será criado (sem extensão)
        - data: Árvore contendo as formas
        - appends: Lista gerada pelos comandos do .qry (opcional)
    
    # Descrição:
        - Cria um arquivo name.svg em path com as formas indicadas
          pelos comandos em data
        
        - path != NULL && name != NULL && data != NULL
*/
void generateSVG(String path, String name, XyyTree data, List appends);

#endif