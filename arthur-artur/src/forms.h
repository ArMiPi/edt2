#ifndef FORMS_H
#define FORMS_H

#include "strings.h"
#include "enum.h"

/*
	- Esse módulo tem por objetivo definir funções para melhor manipular as formas
	  obtidas através do .geo

	- Todas as funções que recebem Form como parâmetro assumem Form != NULL
*/

typedef void *Form;

/*
	# Entrada:
		- command: Comando de criação da forma, indicado no .geo

	# Saída:
		- Form: Struct

	# Descrição:
		- Cria uma forma com base nas informações contidas em command
*/
Form newForm(String command);

/*
	# Entrada:
		- form: Forma

	# Saída:
		- double

	# Descrição:
		- Retorna a coordenada x do ponto âncora da forma informada
*/
double getFormX(Form form);

/*
	# Entrada:
		- form: Forma

	# Saída:
		- double

	# Descrição:
		- Retorna a coordenada y do ponto âncora da forma informada
*/
double getFormY(Form form);

/*
	# Entrada:
		- form: Forma

	# Saída:
		- double

	# Descrição:
		- Retorna o nível de proteção atual da forma informada
*/
double getFormProtection(Form form);

/*
	# Entradas:
		- form: Forma
		- damage: Dano causado à forma
	
	# Descrição:
		- Causa um dano = damage na proteção da forma

		- Caso damage >= proteção da forma, esta será marcada como inativa

		- Caso o damage seja um valor negativo, a forma terá a sua proteção
		  zerada e será marcada como destruída
*/
void damageFormProtection(Form form, double damage);

/*
	# Entrada:
		- form: Forma

	# Saída:
		- alive
		- inactive
		- dead

	# Descrição:
		- Retorna a condição atual da forma informada
*/
Condition getFormCondition(Form form);

/*
	# Entrada:
		- form: Forma

	# Saída:
		- String

	# Descrição:
		- Retorna o comando de criação da forma informada
*/
String getFormForm(Form form);

/*
	# Entrada:
		- form: Forma

	# Saída:
		- double

	# Descrição:
		- Retorna a área de form
*/
double getFormArea(Form form);

/*
	# Entradas:
		- form: Forma
		- x, y: Coordenada
	
	# Saídas:
		- true
		- false
	
	# Descrição:
		- Retorna true caso o ponto (x, y) seja interno à forma,
		  e false caso contrário
*/
bool isPointInsideForm(Form form, double x, double y);

/*
	# Entradas:
		- form: Forma
		- (x1, y1) (x2, y2): Coordenadas delimitadoras da área
	
	# Saídas:
		- true
		- false
	
	# Descrição:
		- Retorna true caso a forma esteja contida na área informada
*/
bool isFormInsideArea(Form form, double x1, double y1, double x2, double y2);

/*
	# Entrada:
		- form: Forma
	
	# Saída:
		- String: String contendo todas as informações da forma
	
	# Descrição:
		- Retorna uma string contendo todas as informações de form
*/
String reportForm(Form form);

/*
    # Entradas:
        - form: Forma a ser clonada
        - dx, dy: Deslocamento
		- id: Id da nova forma
    
    # Saída:
        - Form
    
    # Descrição:
        - Retorna uma nova forma, clone de form
          na posição (x+dx, y+dy) com as cores
          invertidas
*/
Form createClone(Form form, double dx, double dy, int id);

/*
	# Entrada:
		- form: Forma

	# Descrição:
		- Libera a memória utilizada por form
*/
void destroyForm(Form form);

#endif