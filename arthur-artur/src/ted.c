#include <stdio.h>
#include <stdlib.h>

#include "params.h"
#include "strings.h"

int main(int argc, char *argv[]) 
{
    // Leitura dos parâmetros de entrada do programa
    Params prms = newParams(argc, argv);

    // Ler e armazenar informações do .geo
    

    // Criar .svg a partir do .geo
    

    if(getQRY(prms) != NULL) {
        // Ler e armazenar informações do .qry
        

        // Executar comandos do .qry
        

    }

    destroyParams(prms);    
}