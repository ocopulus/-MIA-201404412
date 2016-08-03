#include "acciones_disco.h"

void AD_crearDir(char dir_disco[200])
{
    char comando[500] = "mkdir -p ";
    strcat(comando,dir_disco);
    system(comando);
    printf("Se creo el directorio: %s\n",dir_disco);
}

void AD_eliminarDisk(char dir_disco[200])
{
    char comando[500] = "rm -r ";
    strcat(comando,dir_disco);
    system(comando);
    printf("Se elimino el archivo: %s\n",dir_disco);
}
