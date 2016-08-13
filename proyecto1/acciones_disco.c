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
    strcpy(mbr.mbr_partition_1.part_fit,"0");
    strcpy(mbr.mbr_partition_1.part_name,"0");
    mbr.mbr_partition_1.part_size = 0;
    mbr.mbr_partition_1.part_start = 0;
    mbr.mbr_partition_1.part_type = '0';
    mbr.mbr_partition_2.part_status = '0';
    strcpy(mbr.mbr_partition_2.part_fit,"0");
    strcpy(mbr.mbr_partition_2.part_name,"0");
    mbr.mbr_partition_2.part_size = 0;
    mbr.mbr_partition_2.part_start = 0;
    mbr.mbr_partition_2.part_type = '0';
    mbr.mbr_partition_3.part_status = '0';
    strcpy(mbr.mbr_partition_3.part_fit,"0");
    strcpy(mbr.mbr_partition_3.part_name,"0");
    mbr.mbr_partition_3.part_size = 0;
    mbr.mbr_partition_3.part_start = 0;
    mbr.mbr_partition_3.part_type = '0';
    mbr.mbr_partition_4.part_status = '0';
    strcpy(mbr.mbr_partition_4.part_fit,"0");
    strcpy(mbr.mbr_partition_4.part_name,"0");
    mbr.mbr_partition_4.part_size = 0;
    mbr.mbr_partition_4.part_start = 0;
    mbr.mbr_partition_4.part_type = '0';

    if(tam*1024 < 10485760)
    {
        printf("El disco no se pudo crear porque tiene que tener un tamaño minimo de 10 MB\n");
        return;
    }

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

    if(tam<2097152)
    {
        printf("No se puede crear la Particion, tiene que tener una Minimo de 2 MB.\n");
        return;
    }

    if(strcasecmp(type,"l")==0)
    {
        //Metodo para crear la marticion Logica
        int ex = AD_hayExtendidas(mbr);
        if(ex!=0)
        {
            int numpar = AD_Extendida(mbr);
            if(numpar == 1)
            {
                AD_CrearParticionLogica(disco,mbr.mbr_partition_1.part_start,mbr.mbr_partition_1.part_start+mbr.mbr_partition_1.part_size,name,tam,fit);
                fclose(disco);
                return;
            }
            else if(numpar == 2)
            {
                AD_CrearParticionLogica(disco,mbr.mbr_partition_2.part_start,mbr.mbr_partition_2.part_start+mbr.mbr_partition_2.part_size,name,tam,fit);
                fclose(disco);
                return;
            }
            else if(numpar == 3)
            {
                AD_CrearParticionLogica(disco,mbr.mbr_partition_3.part_start,mbr.mbr_partition_3.part_start+mbr.mbr_partition_3.part_size,name,tam,fit);
                fclose(disco);
                return;
            }
            else if(numpar == 4)
            {
                AD_CrearParticionLogica(disco,mbr.mbr_partition_4.part_start,mbr.mbr_partition_4.part_start+mbr.mbr_partition_4.part_size,name,tam,fit);
                fclose(disco);
                return;
            }
            else
            {
                printf("Yolo paso algo trambolico no encontre la partcion xD\n");
            }

        }
        else
        {
            printf("Debe de crear un particion Extendida primero para poder crear particiones logicas xD\n");
        }
        return;
    }
    //Para saber si hay particiones Extendias ya hechas 0 no hay y si es difente esque que ya hay
    int Ex = AD_hayExtendidas(mbr);
    int inicio = sizeof(mbr);
    if(mbr.mbr_partition_1.part_status=='0')
    {
        if(mbr.mbr_partition_2.part_status!='0')
        {
            if((tam + sizeof(mbr)) < mbr.mbr_partition_2.part_start)
            {
                mbr.mbr_partition_1.part_status = '1';
                mbr.mbr_partition_1.part_size = tam;
                mbr.mbr_partition_1.part_start = sizeof(mbr);
                strcpy(mbr.mbr_partition_1.part_name,name);
                strcpy(mbr.mbr_partition_1.part_fit,fit);
                if(strcasecmp(type,"e")==0)
                {
                    if(Ex==0)
                    {
                        mbr.mbr_partition_1.part_type = 'p';
                        struct EBR ebr;
                        ebr.part_next = -1;
                        ebr.part_start = sizeof(mbr)+sizeof(ebr);
                        ebr.part_status = '0';
                        fseek(disco,sizeof(mbr),SEEK_SET); /****/
                        fwrite(&ebr, sizeof(ebr), 1, disco); /****/
                        fseek(disco,0,SEEK_SET);
                        fwrite(&mbr,sizeof(mbr),1,disco); /****/
                        fclose(disco);
                        printf("Parcion Extendida Creada: %s \n",name);
                        return;
                    }
                    else
                    {
                        printf("Error solo puede haber una particion Extendida \n");
                        fclose(disco);
                        return;
                    }
                }
                mbr.mbr_partition_1.part_type = 'p';
                fseek(disco, 0, SEEK_SET);
                fwrite(&mbr, sizeof(mbr), 1, disco);
                fclose(disco);
                printf("Particon Primaria Creada: %s \n",name);
                return;
            }
            else
            {
                inicio = mbr.mbr_partition_2.part_start + mbr.mbr_partition_2.part_size;
            }
        }
        else if(mbr.mbr_partition_3.part_status!='0')
        {
            if((tam+sizeof(mbr)) < mbr.mbr_partition_3.part_start)
            {
                mbr.mbr_partition_1.part_status = '1';
                mbr.mbr_partition_1.part_size = tam;
                mbr.mbr_partition_1.part_start = sizeof(mbr);
                strcpy(mbr.mbr_partition_1.part_name,name);
                strcpy(mbr.mbr_partition_1.part_fit,fit);
                if(strcasecmp(type,"e")==0)
                {
                    if(Ex==0)
                    {
                        mbr.mbr_partition_1.part_type = 'e';
                        struct EBR ebr;
                        ebr.part_next = -1;
                        ebr.part_start = sizeof(mbr) + sizeof(ebr);
                        ebr.part_status = '0';
                        fseek(disco,sizeof(mbr),SEEK_SET); /****/
                        fwrite(&ebr, sizeof(ebr), 1, disco); /****/
                        fseek(disco,0,SEEK_SET);
                        fwrite(&mbr,sizeof(mbr),1,disco); /****/
                        fclose(disco);
                        printf("Parcion Extendida Creada: %s \n",name);
                        return;
                    }
                    else
                    {
                        printf("Error solo puede haber una particion Extendida \n");
                        fclose(disco);
                        return;
                    }
                }
                mbr.mbr_partition_1.part_type = 'p';
                fseek(disco, 0, SEEK_SET);
                fwrite(&mbr, sizeof(mbr), 1, disco);
                fclose(disco);
                printf("Particon Primaria Creada: %s \n",name);
                return;
            }
            else
            {
                inicio = mbr.mbr_partition_3.part_start + mbr.mbr_partition_3.part_size;
            }
        }
        else if(mbr.mbr_partition_4.part_status!='0')
        {
            if((tam+sizeof(mbr)) < mbr.mbr_partition_4.part_start)
            {
                mbr.mbr_partition_1.part_status = '1';
                mbr.mbr_partition_1.part_size = tam;
                mbr.mbr_partition_1.part_start = sizeof(mbr);
                strcpy(mbr.mbr_partition_1.part_name,name);
                strcpy(mbr.mbr_partition_1.part_fit,fit);
                if(strcasecmp(type,"e")==0)
                {
                    if(Ex==0)
                    {
                        mbr.mbr_partition_1.part_type = 'e';
                        struct EBR ebr;
                        ebr.part_next = -1;
                        ebr.part_start = sizeof(mbr) + sizeof(ebr);
                        ebr.part_status = '0';
                        fseek(disco,sizeof(mbr),SEEK_SET); /****/
                        fwrite(&ebr, sizeof(ebr), 1, disco); /****/
                        fseek(disco,0,SEEK_SET);
                        fwrite(&mbr,sizeof(mbr),1,disco); /****/
                        fclose(disco);
                        printf("Parcion Extendida Creada: %s \n",name);
                        return;
                    }
                    else
                    {
                        printf("Error solo puede haber una particion Extendida \n");
                        fclose(disco);
                        return;
                    }
                }
                mbr.mbr_partition_1.part_type = 'p';
                fseek(disco, 0, SEEK_SET);
                fwrite(&mbr, sizeof(mbr), 1, disco);
                fclose(disco);
                printf("Particon Primaria Creada: %s \n",name);
                return;
            }
            else
            {
                inicio = mbr.mbr_partition_4.part_start + mbr.mbr_partition_4.part_size;
            }
        }
        else
        {
            mbr.mbr_partition_1.part_status = '1';
            mbr.mbr_partition_1.part_size = tam;
            mbr.mbr_partition_1.part_start = sizeof(mbr); /****/
            strcpy(mbr.mbr_partition_1.part_name,name);
            strcpy(mbr.mbr_partition_1.part_fit,fit);
            if(mbr.mbr_tamano < (mbr.mbr_partition_1.part_start + mbr.mbr_partition_1.part_size))
            {
                printf("Error no se puede hacer la particion porque sobrepasa el tamaño de las fronteras del disco\n");
                return;
            }
            if(strcasecmp(type,"e")==0)
            {
                if(Ex==0)
                {
                    /*** Escrio la partcion extendida y le agreso el ebr ***/
                    mbr.mbr_partition_1.part_type = 'e';
                    struct EBR ebr;
                    ebr.part_next = -1;
                    ebr.part_start = sizeof(mbr)+sizeof(ebr); /****/
                    ebr.part_status = '0';
                    fseek(disco,sizeof(mbr),SEEK_SET); /****/
                    fwrite(&ebr, sizeof(ebr), 1, disco); /****/
                    fseek(disco,0,SEEK_SET);
                    fwrite(&mbr,sizeof(mbr),1,disco); /****/
                    fclose(disco);
                    printf("Parcion Extendida Creada: %s \n",name);
                    return;
                }
                else
                {
                    printf("Error solo puede haber una particion Extendida \n");
                    fclose(disco);
                    return;
                }
            }
            mbr.mbr_partition_1.part_type = 'p';
            fseek(disco, 0, SEEK_SET);
            fwrite(&mbr, sizeof(mbr), 1, disco);
            fclose(disco);
            printf("Particon Primaria Creada: %s \n",name);
            return;
        }//Fine de los fi

    }
    else
    {
        inicio = mbr.mbr_partition_1.part_start + mbr.mbr_partition_1.part_size;
    }//fin particon 1

    /************************ Validaciones para la Particion 2 *******************************/

    if(mbr.mbr_partition_2.part_status=='0')
    {
        //printf("Aqui se crea la segunda particion \n");
        if(mbr.mbr_partition_3.part_status !=  '0')
        {
            if((tam + inicio) < mbr.mbr_partition_3.part_start)
            {
                mbr.mbr_partition_2.part_status = '1';
                mbr.mbr_partition_2.part_size = tam;
                mbr.mbr_partition_2.part_start = inicio;
                strcpy(mbr.mbr_partition_2.part_name,name);
                strcpy(mbr.mbr_partition_2.part_fit,fit);
                if(strcasecmp(type,"e")==0)
                {
                    if(Ex==0)
                    {
                        mbr.mbr_partition_2.part_type = 'e';
                        struct EBR ebr;
                        ebr.part_next = -1;
                        ebr.part_start = inicio + sizeof(ebr);
                        ebr.part_status = '0';
                        fseek(disco,inicio,SEEK_SET); /****/
                        fwrite(&ebr, sizeof(ebr), 1, disco); /****/
                        fseek(disco,0,SEEK_SET);
                        fwrite(&mbr,sizeof(mbr),1,disco); /****/
                        fclose(disco);
                        printf("Parcion Extendida Creada: %s \n",name);
                        return;
                    }
                    else
                    {
                        printf("Error solo puede haber una particion Extendida \n");
                        fclose(disco);
                        return;
                    }
                }
                mbr.mbr_partition_2.part_type = 'p';
                fseek(disco, 0, SEEK_SET);
                fwrite(&mbr, sizeof(mbr), 1, disco);
                fclose(disco);
                printf("Particon Primaria Creada: %s \n",name);
                return;
            }
            else
            {
                inicio = mbr.mbr_partition_3.part_start + mbr.mbr_partition_3.part_size;
            }
        }
        else if(mbr.mbr_partition_4.part_status != '0')
        {
            if((tam + inicio) < mbr.mbr_partition_4.part_start)
            {
                mbr.mbr_partition_2.part_status = '1';
                mbr.mbr_partition_2.part_size = tam;
                mbr.mbr_partition_2.part_start = inicio;
                strcpy(mbr.mbr_partition_2.part_name,name);
                strcpy(mbr.mbr_partition_2.part_fit,fit);
                if(strcasecmp(type,"e")==0)
                {
                    if(Ex==0)
                    {
                        mbr.mbr_partition_2.part_type = 'e';
                        struct EBR ebr;
                        ebr.part_next = -1;
                        ebr.part_start = inicio + sizeof(ebr);
                        ebr.part_status = '0';
                        fseek(disco,inicio,SEEK_SET); /****/
                        fwrite(&ebr, sizeof(ebr), 1, disco); /****/
                        fseek(disco,0,SEEK_SET);
                        fwrite(&mbr,sizeof(mbr),1,disco); /****/
                        fclose(disco);
                        printf("Parcion Extendida Creada: %s \n",name);
                        return;
                    }
                    else
                    {
                        printf("Error solo puede haber una particion Extendida \n");
                        fclose(disco);
                        return;
                    }
                }
                mbr.mbr_partition_2.part_type = 'p';
                fseek(disco, 0, SEEK_SET);
                fwrite(&mbr, sizeof(mbr), 1, disco);
                fclose(disco);
                printf("Particon Primaria Creada: %s \n",name);
                return;
            }
            else
            {
                printf("No se puede crear la particion\n");
                return;
            }
        }
        else
        {
            mbr.mbr_partition_2.part_status = '1';
            mbr.mbr_partition_2.part_size = tam;
            mbr.mbr_partition_2.part_start = inicio;
            strcpy(mbr.mbr_partition_2.part_name,name);
            strcpy(mbr.mbr_partition_2.part_fit,fit);
            if(mbr.mbr_tamano < (inicio + tam))
            {
                printf("Error no se puede hacer la particion porque sobrepasa el tamaño de las fronteras del disco\n");
                return;
            }
            if(strcasecmp(type,"e")==0)
            {
                if(Ex==0)
                {
                    mbr.mbr_partition_2.part_type = 'e';
                    struct EBR ebr;
                    ebr.part_next = -1;
                    ebr.part_start = inicio + sizeof(ebr);
                    ebr.part_status = '0';
                    fseek(disco,inicio,SEEK_SET); /****/
                    fwrite(&ebr, sizeof(ebr), 1, disco); /****/
                    fseek(disco,0,SEEK_SET);
                    fwrite(&mbr,sizeof(mbr),1,disco); /****/
                    fclose(disco);
                    printf("Parcion Extendida Creada: %s \n",name);
                    return;
                }
                else
                {
                    printf("Error solo puede haber una particion Extendida \n");
                    fclose(disco);
                    return;
                }
            }
            mbr.mbr_partition_2.part_type = 'p';
            fseek(disco, 0, SEEK_SET);
            fwrite(&mbr, sizeof(mbr), 1, disco);
            fclose(disco);
            printf("Particon Primaria Creada: %s \n",name);
            return;
        }
    }
    else
    {
        inicio = mbr.mbr_partition_2.part_start + mbr.mbr_partition_2.part_size;
    }//Fin particion 2

    /****************** Validaciones Particion 3 ******************/
    if(mbr.mbr_partition_3.part_status == '0')
    {
        if(mbr.mbr_partition_4.part_status != '0')
        {
            if((tam + inicio) < mbr.mbr_partition_4.part_start)
            {
                mbr.mbr_partition_3.part_status = '1';
                mbr.mbr_partition_3.part_size = tam;
                mbr.mbr_partition_3.part_start = inicio;
                strcpy(mbr.mbr_partition_3.part_name,name);
                strcpy(mbr.mbr_partition_3.part_fit,fit);
                if(strcasecmp(type,"e")==0)
                {
                    if(Ex==0)
                    {
                        mbr.mbr_partition_3.part_type = 'e';
                        struct EBR ebr;
                        ebr.part_next = -1;
                        ebr.part_start = inicio + sizeof(ebr);
                        ebr.part_status = '0';
                        fseek(disco,inicio,SEEK_SET); /****/
                        fwrite(&ebr, sizeof(ebr), 1, disco); /****/
                        fseek(disco,0,SEEK_SET);
                        fwrite(&mbr,sizeof(mbr),1,disco); /****/
                        fclose(disco);
                        printf("Parcion Extendida Creada: %s \n",name);
                        return;
                    }
                    else
                    {
                        printf("Error solo puede haber una particion Extendida \n");
                        fclose(disco);
                        return;
                    }
                }
                mbr.mbr_partition_3.part_type = 'p';
                fseek(disco, 0, SEEK_SET);
                fwrite(&mbr, sizeof(mbr), 1, disco);
                fclose(disco);
                printf("Particon Primaria Creada: %s \n",name);
                return;
            }
            else
            {
                printf("Error no puedo crear la parcion no hay espacio sufinenta la fragmentacion chinga yolo xD\n");
                return;
            }
        }
        else
        {
            mbr.mbr_partition_3.part_status = '1';
            mbr.mbr_partition_3.part_size = tam;
            mbr.mbr_partition_3.part_start = inicio;
            strcpy(mbr.mbr_partition_3.part_name,name);
            strcpy(mbr.mbr_partition_3.part_fit,fit);
            if(mbr.mbr_tamano < (inicio + tam))
            {
                printf("Error no se puede hacer la particion porque sobrepasa el tamaño de las fronteras del disco\n");
                return;
            }
            if(strcasecmp(type,"e")==0)
            {
                if(Ex==0)
                {
                    mbr.mbr_partition_3.part_type = 'e';
                    struct EBR ebr;
                    ebr.part_next = -1;
                    ebr.part_start = inicio + sizeof(ebr);
                    ebr.part_status = '0';
                    fseek(disco,inicio,SEEK_SET); /****/
                    fwrite(&ebr, sizeof(ebr), 1, disco); /****/
                    fseek(disco,0,SEEK_SET);
                    fwrite(&mbr,sizeof(mbr),1,disco); /****/
                    fclose(disco);
                    printf("Parcion Extendida Creada: %s \n",name);
                    return;
                }
                else
                {
                    printf("Error solo puede haber una particion Extendida \n");
                    fclose(disco);
                    return;
                }
            }
            mbr.mbr_partition_3.part_type = 'p';
            fseek(disco, 0, SEEK_SET);
            fwrite(&mbr, sizeof(mbr), 1, disco);
            fclose(disco);
            printf("Particon Primaria Creada: %s \n",name);
            return;
        }
    }
    else
    {
        inicio = mbr.mbr_partition_3.part_start + mbr.mbr_partition_3.part_size;
    }

    /******************** Validacion Particion 4 ********************/
    if(mbr.mbr_partition_4.part_status == '0')
    {
        if(mbr.mbr_tamano < (inicio + tam))
        {
            printf("Error no se puede hacer la particion porque sobrepasa el tamaño de las fronteras del disco\n");
            return;
        }
        mbr.mbr_partition_4.part_status = '1';
        mbr.mbr_partition_4.part_size = tam;
        mbr.mbr_partition_4.part_start = inicio;
        strcpy(mbr.mbr_partition_4.part_name,name);
        strcpy(mbr.mbr_partition_4.part_fit,fit);
        if(strcasecmp(type,"e")==0)
        {
            if(Ex==0)
            {
                mbr.mbr_partition_4.part_type = 'e';
                struct EBR ebr;
                ebr.part_next = -1;
                ebr.part_start = inicio + sizeof(ebr);
                ebr.part_status = '0';
                fseek(disco,inicio,SEEK_SET); /****/
                fwrite(&ebr, sizeof(ebr), 1, disco); /****/
                fseek(disco,0,SEEK_SET);
                fwrite(&mbr,sizeof(mbr),1,disco); /****/
                fclose(disco);
                printf("Parcion Extendida Creada: %s \n",name);
                return;
            }
            else
            {
                printf("Error solo puede haber una particion Extendida \n");
                fclose(disco);
                return;
            }
        }
        mbr.mbr_partition_4.part_type = 'p';
        fseek(disco, 0, SEEK_SET);
        fwrite(&mbr, sizeof(mbr), 1, disco);
        fclose(disco);
        printf("Particon Primaria Creada: %s \n",name);
        return;
    }
    else
    {
        printf("No hay espacion para hacer la particon Particion 4 Ocupada tambien jaja\n");
        return;
    }

    printf("No es puedo encontrar una Espacio para la particion puede que tenga todas la partciones o la fragmentacion lo esta chingando\n");
    fclose(disco);
}

int AD_hayExtendidas(MBR mbr)
{
    int resultado=0;

    if(mbr.mbr_partition_1.part_status!='0')
    {
        if(mbr.mbr_partition_1.part_type == 'e')
        {
            resultado++;
        }
    }

    if(mbr.mbr_partition_2.part_status!='0')
    {
        if(mbr.mbr_partition_2.part_type == 'e')
        {
            resultado++;
        }
    }

    if(mbr.mbr_partition_3.part_status!='0')
    {
        if(mbr.mbr_partition_3.part_type == 'e')
        {
            resultado++;
        }
    }

    if(mbr.mbr_partition_4.part_status!='0')
    {
        if(mbr.mbr_partition_4.part_type == 'e')
        {
            resultado++;
        }
    }
    return resultado;
}

int AD_Extendida(MBR mbr)
{
    int resultado = 0;
    if(mbr.mbr_partition_1.part_status!='0')
    {
        if(mbr.mbr_partition_1.part_type == 'e')
        {
            return 1;
        }
    }

    if(mbr.mbr_partition_2.part_status!='0')
    {
        if(mbr.mbr_partition_2.part_type == 'e')
        {
            return 2;
        }
    }

    if(mbr.mbr_partition_3.part_status!= '0')
    {
        if(mbr.mbr_partition_3.part_type == 'e')
        {
            return 3;
        }
    }

    if(mbr.mbr_partition_4.part_type == '0')
    {
        if(mbr.mbr_partition_4.part_type == 'e')
        {
            return 4;
        }
    }

    return resultado;
}

void AD_EliminarParticon(char del[6],char dir_disco[200], char name[50])
{
    struct MBR mbr;
    FILE *disco;
    disco = fopen (dir_disco, "rb+");
    if( disco == NULL)
    {
        printf("¡El Disco no existe!\n");
        return;
    }
    fread (&mbr, sizeof(mbr), 1,disco);
    printf("Esta seguro que quiere ELIMINAR la particon????? S = 1/N = 0 \n");
    int si;
    scanf("%i", &si);
    if(si==0)
    {
        printf("Se cancelo la operacion de Eliminar\n");
        return;
    }

    struct particion *par;
    if(strcasecmp(mbr.mbr_partition_1.part_name,name)==0)
    {
        par = &mbr.mbr_partition_1;
    }
    else if(strcasecmp(mbr.mbr_partition_2.part_name,name)==0)
    {
        par = &mbr.mbr_partition_2;
    }
    else if(strcasecmp(mbr.mbr_partition_3.part_name,name)==0)
    {
        par = &mbr.mbr_partition_3;
    }
    else if(strcasecmp(mbr.mbr_partition_4.part_name,name)==0)
    {
        par = &mbr.mbr_partition_4;
    }
    else
    {
        par = NULL;
    }

    if(par!=NULL)
    {
        if(strcasecmp(del,"fast")==0)
        {
            par->part_status = '0';
            /*par->part_type = '0';
            strcpy(par->part_fit,"0");
            par->part_start = 0;
            par->part_size = 0;
            strcpy(par->part_name,"0");*/
            fseek(disco,0,SEEK_SET);
            fwrite(&mbr,sizeof(mbr),1,disco);
            fclose(disco);
            printf("La particion: %s Fue eliminada FAST\n",name);
            return;
        }
        else if(strcasecmp(del,"full")==0)
        {
            par->part_status = '0';
            fseek(disco,par->part_start,SEEK_SET);
            int i;
            char es[1];
            for(i=0; i < par->part_size; i++)
            {
                fwrite(es,sizeof(es),1,disco);
            }
            fseek(disco,0,SEEK_SET);
            fwrite(&mbr,sizeof(mbr),1,disco);
            fclose(disco);
            printf("La particion: %s Fue eliminada FULL\n",name);
            return;
        }
    }
    else
    {
        /*** Talves es logica hay que buscala y programar ***/
    }
}

void AD_CrearParticionLogica(FILE *disk,int inicio, int fin,char name[50], int tam,char fit[3])
{
    struct EBR ebr;
    struct EBR newebr;
    fseek(disk,inicio,SEEK_SET);
    fread(&ebr, sizeof(ebr), 1, disk);

    if(ebr.part_next==-1)
    {
        if((inicio+sizeof(ebr)+tam) < fin)
        {
            ebr.part_status = '1';
            ebr.part_next = inicio + sizeof(ebr)+tam;
            ebr.part_start = inicio+sizeof(ebr);
            ebr.part_size = tam;
            strcpy(ebr.part_fit,fit);
            strcpy(ebr.part_name,name);

            newebr.part_next = -1;
            newebr.part_start = inicio + sizeof(ebr)+tam;
            newebr.part_status = '0';
            newebr.part_size = 0;
            strcpy(newebr.part_fit,"0");
            strcpy(ebr.part_name,"0");
            fseek(disk,inicio,SEEK_SET);
            fwrite(&ebr,sizeof(ebr),1,disk);
            fseek(disk,ebr.part_next,SEEK_SET);
            fwrite(&newebr,sizeof(newebr),1,disk);
            printf("Se creo la particon Logica: %s \n",name);
            return;
        }
        else
        {
            printf("No hay espacio Disponible para hacer la particon logica: %s\n",name);
            return;
        }

    }
    else
    {
        AD_CrearParticionLogica(disk,ebr.part_next,fin,name,tam,fit);
    }
}
