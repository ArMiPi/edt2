#ifndef FORMS_H
#define FORMS_H

#include "strings.h"
#include "enum.c"

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
		- int

	# Descrição:
		- Retorna o nível de proteção atual da forma informada
*/
int getFormProtection(Form form);

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

#endif