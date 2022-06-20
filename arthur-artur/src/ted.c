#include <stdio.h>
#include <stdlib.h>

#include "params.h"
#include "strings.h"
#include "database.h"
#include "svg.h"
#include "qry.h"

int main(int argc, char *argv[]) 
{
    // Leitura dos parâmetros de entrada do programa
    Params prms = newParams(argc, argv);

    // Ler e armazenar informações do .geo
    Database geo = readData(getBED(prms), getGEO(prms));
    
    // Criar .svg a partir do .geo
    generateSVG(getBSD(prms), getDBname(geo), getDBdata(geo), NULL);
    
    if(getQRY(prms) != NULL) 
    {
        String qryName;
        if(endsWith(getBED(prms), "/"))
            qryName = concat(getBED(prms), getQRY(prms));
        else
        {
            String barpath = concat(getBED(prms), "/");
            qryName = concat(barpath, getQRY(prms));

            free(barpath);
        }
        
        // Executar comandos do .qry
        executeQry(getBSD(prms), getDBname(geo), qryName, getDBdata(geo));

        free(qryName);
    }

    destroyParams(prms);    
    destroyDB(geo);
}