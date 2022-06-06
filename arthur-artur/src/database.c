#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
#include "forms.h"

#define MAX_SIZE 200

typedef struct _database
{
    String name;
    XyyTree data;
}DATABASE;

/*
    # Entrada:
        - fullpath: path completo para o arquivo a ser aberto
    
    # Saída:
        - FILE*: Ponteiro para FILE

    # Descrição:
        - Abre o arquivo fullpath para leitura
        
        - O programa será finalizado caso não seja possível
          abrir o arquivo
*/
FILE *openFile(String fullpath)
{
    FILE *fptr = fopen(fullpath, "r");
    if(fptr == NULL) 
    {
        printf("ERROR: Could not open %s\n", fullpath);
        exit(EXIT_FAILURE);
    }

    return fptr;
}

XyyTree readFile(FILE *fptr)
{
    // REDO
    double tempFD = 0.50;
    XyyTree tree = newXyyTree(tempFD);

    String line = newEmptyString(MAX_SIZE);
    String data;
    Form form;
    while (fgets(line, MAX_SIZE, fptr))
    {
        data = copyString(line);
        if(data[strlen(data) - 1] == '\n') data[strlen(data) - 1] = '\0';
        
        form = newForm(data);

        insertXyyT(tree, getFormX(form), getFormY(form), data);

        destryForm(form);
    }
    
    free(line);

    return tree;
}

/*
    # Saída:
        - DATABASE: Struct
    
    # Descrição:
        - Retorna um DATABASE vazio
*/
DATABASE *newDatabase() 
{
    DATABASE *db = (DATABASE *) malloc(sizeof(DATABASE));
    if(db == NULL) 
    {
        printf("ERROR: Could not allocate memory for new database\n");
        exit(EXIT_FAILURE);
    }

    db->name = NULL;
    db->data = NULL;

    return db;
}

Database readData(String path, String name) 
{
    if(path == NULL || name == NULL) 
        return NULL;

    String fullpath;
    if(endsWith(path, "/")) 
        fullpath = concat(path, name);
    else 
    {
        String barPath = concat(path, "/");
        fullpath = concat(barPath, name);
        free(barPath);
    }

    // Abrir arquivo para leitura
    FILE *fptr = openFile(fullpath);

    // Criar DATABASE
    DATABASE *db = newDatabase();
    db->name = slice(name, 0, strlen(name) - 5);
    db->data = readFile(fptr);

    // Fechar arquivo
    fclose(fptr);

    free(fullpath);

    return db;
}

String getDBname(Database db)
{
    if(db == NULL) 
        return NULL;

    DATABASE *DB = (DATABASE *) db;

    return DB->name;
}

XyyTree getDBdata(Database db) 
{
    if(db == NULL) 
        return NULL;

    DATABASE *DB = (DATABASE *) db;

    return DB->data;
}

void destroyDB(Database db) 
{
    if(db == NULL) 
        return;

    DATABASE *DB = (DATABASE *) db;

    if(DB->name) 
        free(DB->name);
    // REDO
    if(DB->data != NULL) 
        DestroyList(DB->data, &free);
    free(DB);

    DB = NULL;
    db = NULL;
}