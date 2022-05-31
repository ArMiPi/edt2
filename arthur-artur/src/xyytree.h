#ifndef _XY2TREE__
#define XY2TREE__

//#include "lista.h"
#include <stdbool.h>


/*
 * Uma Arvore Xyy e' uma arvore ternaria, espacial, nao balanceada. 
 * A cada no' r da Arvore e' associado um ponto de 2 dimensoes (r.x e r.y) denominado ancora 
 * do no' e uma informacao relacionada tal ponto. 
 * Um no' divide o plano em 3 regioes, associadas a tres subarvores:
 * 
 *  - sub-arvore esquerda (se) contem nos (d) cujas abscissas (d.x) sao estritamente
 *    menores que a abscissa de r, ou seja: d.x < r.x
 *  - sub-arvore mediana (sm): (d.x >= r.x) & (d.y < r.y)
 *  - sub-arvore direita (sd): (d.x >= r.x) & (d.y >= r.y)
 * 
 * A arvore Xyy implementa 2 percursos: em largura e em profundidade. 
 * Tais percursos recebem como parametro uma funcao que processa a 
 * informacao associada ao no' visitado.
 * 
 * Tambem sao providas operacoes de selecao espacial. 
 * A primeira seleciona os nos da arvore cujas ancoras 
 * sao internas a uma regiao retangular. 
 * A segunda seleciona os nos da Arvore cujas informacoes associadas 
 * podem ser consideradas internas a uma regiao retangular. 
 * Esta operacao recebe por parametro uma funcao que decide se 
 * tal informacao e' considerada (ou nao) interna. 
 * A terceira, similarmente, seleciona os nos da arvore cujo um dado 
 * ponto e' interno 'a informacao associada ao no'.
 * 
 * Nos removidos nao sao desalocados imediatamente, mas apenas 
 * marcados como delidos.
 * Eventualmente, a arvore e' re-criada sem os no's removidos. 
 * Isto ocorre quando o fator de degradacao fd
 *
 *     fd = #removidos/#total_no's > limiar. 
 *
 * Este limiar e' definido no momento da criacao da arvore.
 */


typedef void *XyyTree;
typedef void *Node;
typedef void *Info;

typedef bool (*FdentroDe) (Info i, double x1, double y1 , double x2, double y2);
/*
 * Uma funcao deste tipo deve retornar verdadeiro se a informacao i esta'
 * "dentro" da regiao retangular delimitada pelos pontos opostos (x1,y1) e (x2,y2).
 * Retorna falso, caso contrario.
 */

typedef bool (*FatingidoPor) (Info i, double x, double y);
/*
 * Uma funcao deste tipo deve retornar verdadeiro se o ponto (x,y) 
 * deva ser considerado
 * "interno" da informacao i.
 */

typedef void (*FvisitaNo) (Info i, double x, double y, void *aux);
/*
 * Processa a informacao i associada a um no' da arvore, cuja ancora
 * e' o ponto (x,y). O par�metro aux aponta para conjunto de dados 
 * (provavelmente um registro) que sao compartilhados entre as 
 * sucessivas invocacoes a esta funcao.
 */


XyyTree newXyyTree (double fd);
/*
 * Retorna uma arvore Xyy vazia com fator de degradacao fd.
 * 0 <= fd < 1.0
 */

Node insertXyyT (XyyTree t, double x, double y, Info i);
/*
 * Insere a informacao i, associada 'a ancora (x,y) na Arvore t.
 * Retorna um indicador para o no' inserido.
 */

Node getNodeXyyT (XyyTree t, double x, double y, double epsilon);
/*
 * Retorna o n� cuja ancora seja o ponto (x,y). Aceita-se uma pequena discrep�ncia
 * entre a coordenada da ancora (anc.x,anc.y) e o ponto (x,y) de epsilon unidades.
 * Ou seja, |anc.x - x | < epsilon e |anc.y - y | < epsilon.
 * Retorna NULL caso n�o tenha encontrado o n�.
 */

void removeNoXyyT (XyyTree t, Node n);
/*
 * Marca como removido o no' n. Caso, apos a remocao, o fator de degradacao
 * superar o limiar definido na criacao, a arvore e' recriada sem os no's delidos.
 */

Info getInfoXyyT (XyyTree t, Node n);
/* Retorna a informacao associada ao no' n */

Lista getNodesDentroRegiaoXyyT (XyyTree t, double x1, double y1, double x2, double y2);
/* Retorna uma lista dos nos da arvore t cujas ancoras estao dentro da regiao delimitada pelos
   pontos (x1,y1) e (x2,y2) */

Lista getInfosDentroRegiaoXyyT (XyyTree t, double x1, double y1, double x2, double y2, FdentroDe f);
/* Retorna um lista dos nos cujas respectivas informacoes associadas estao dentro da regiao
   delimitada pelos pontos (x1,y1) e (x2,y2). A funcao f � usada para determinar se uma informacao
   armazenada na arvore esta' dentro da regiao.
   Retorna uma lista vazia, caso n�o existam informacoes internas.
 */

Lista getInfosAtingidoPontoXyyT (XyyTree t, double x, double y, FatingidoPor f);
/* Retorna uma lista dos nos para os quais o ponto (x,y) possa ser considerado
  interno 'as  informacoes associadas ao n�. A funcao f e' invocada para determinar
  se o ponto (x,y) � interno a uma informacao especifica.
 */

void visitaProfundidadeXyyT (XyyTree t, FvisitaNo f, void *aux);
/* Percorre a arvore em profundidade. Invoca a funcao f em cada no visitado.
   O apontador aux e' parametro em cada invocacao de f; assim alguns
   dados podem ser compartilhados entre as diversas invocacoes de f.
 */

void visitaLarguraXyyT (XyyTree t, FvisitaNo f, void *aux);
/* Similar a visitaProfundidadeXyyT, porem, faz o percurso em largura.
 */

#endif
