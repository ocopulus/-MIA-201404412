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
    mbr.mbr_disk_signature = rand()%25+1; //cambiar por un numero ramdon
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

void AD_CrearParticion(char name[50],int tam, char fit[3], char type[3], char path[200])
{
    struct MBR mbr;
    FILE *disco;
    disco = fopen (path, "rb+");
    //Validamos que el disco indicado si exista
    if( disco == NULL)
    {
        printf("¡El Disco no existe!\n");
        return;
    }
    fread (&mbr, sizeof(mbr), 1,disco);
    //Validamos que la particon no sea mas grande que el disco
    if(mbr.mbr_tamano<tam)
    {
        fclose(disco);
        printf("El tamaño de la parcion es mas grande que el disco\n");
        return;
    }

    if(strcasecmp(type,"l")==0)
    {
        //Metodo para crear la marticion Logica
        printf("Tengo que crear la logica\n falta implementar");
        return;
    }
    //Para saber si hay particiones Extendias ya hechas 0 no hay y si es difente esque que ya hay
    int Ex = AD_hayExtendidas(mbr);

    if(mbr.mbr_partition_1.part_status=='0')
    {
        if(mbr.mbr_partition_2.part_status!='0')
        {

        }
        else if(mbr.mbr_partition_3.part_status!='0')
        {
            printf("Particion 3 esta ocupada\n");
        }
        else if(mbr.mbr_partition_4.part_status!='0')
        {
            printf("Parcion 4 esta ocupada\n");
        }
        else
        {
            mbr.mbr_partition_1.part_status = '1';
            mbr.mbr_partition_1.part_size = tam;
            mbr.mbr_partition_1.part_start = sizeof(mbr)+1;
            strcpy(mbr.mbr_partition_1.part_name,name);
            strcpy(mbr.mbr_partition_1.part_fit,fit);
        }//Fine de los fi

    }//fin particon 1

    fclose(disco);
}

int AD_hayExtendidas(MBR mbr)
{
    int resultado=0;

    if(mbr.mbr_partition_1.part_status!='0')
    {
        if(strcasecmp(mbr.mbr_partition_1.part_type,"e")==0)
        {
            resultado++;
        }
    }

    if(mbr.mbr_partition_2.part_status!='0')
    {
        if(strcasecmp(mbr.mbr_partition_2.part_type,"e")==0)
        {
            resultado++;
        }
    }

    if(mbr.mbr_partition_3.part_status!='0')
    {
        if(strcasecmp(mbr.mbr_partition_3.part_type,"e")==0)
        {
            resultado++;
        }
    }

    if(mbr.mbr_partition_4.part_status!='0')
    {
        if(strcasecmp(mbr.mbr_partition_4.part_type,"e")==0)
        {
            resultado++;
        }
    }
    return resultado;
}
