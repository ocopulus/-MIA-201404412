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

void AD_crearDisco(char dir_disco[200], char name[50], int tam)
{
    struct MBR mbr;
    mbr.mbr_tamano = tam * 1024;
    time(&mbr.mbr_fecha_creacion);
    mbr.mbr_disk_signature = 24; //cambiar por un numero ramdon
    mbr.mbr_partition_1.part_status = '0';
    mbr.mbr_partition_2.part_status = '0';
    mbr.mbr_partition_3.part_status = '0';
    mbr.mbr_partition_4.part_status = '0';

    char dir[500];
    strcat(dir,dir_disco);
    strcat(dir,"/");
    strcat(dir,name);
    FILE *disco = fopen (dir, "wb+");
    int i;
    char es[1];
    for(i=0; i < tam; i++){
        fwrite(es, sizeof(es), 1024, disco);
    }
    rewind(disco);
    fwrite(&mbr, sizeof(mbr), 1, disco);
    fclose(disco);
    printf("Disco Creado exitosamente \n");
}
