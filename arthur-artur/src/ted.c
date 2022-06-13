#include <stdio.h>
#include <stdlib.h>

#include "params.h"
#include "strings.h"
#include "database.h"
#include "svg.h"

int main(int argc, char *argv[]) 
{
    // Leitura dos parâmetros de entrada do programa
    Params prms = newParams(argc, argv);

    // Ler e armazenar informações do .geo
    Database geo = readData(getBED(prms), getGEO(prms));
    
    // Criar .svg a partir do .geo
    generateSVG(getBSD(prms), getDBname(geo), getDBdata(geo));

    if(getQRY(prms) != NULL) 
    {
        // Executar comandos do .qry
        

    }

    destroyParams(prms);
    destroyDB(geo);  
}