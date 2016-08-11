#include "lexico.h"

void Lexico_entrada()
{
    printf("Ingrese Comando: \n");
    char comando[500];
    fflush(stdin);
    scanf(" %[^\n]s", &comando);
    if(comando[strlen(comando)-1]=='\\')
    {
        char restocomando[500];printf("Siguieten linea: ");
        fflush(stdin);
        scanf(" %[^\n]s", &restocomando);
        strncpy(comando,comando,strlen(comando)-1);
        strcat(comando,restocomando);
    }
    Lexico_analisador(comando);
}

void Lexico_script(char path[500])
{
    char cadena[1000];
    FILE *archivo;
    archivo = fopen (path, "r");
    if(archivo == NULL)
    {
        printf("¡El Script no se entonctro en la ruta espesificada!\n");
        return;
    }
    while (fgets(cadena,sizeof(cadena),archivo) != NULL)
    {
        if(cadena[0]=='#')
        {
            printf("Comentario: %s",cadena);
        }
        else
        {
            printf("Sentencia: %s",cadena);
            Lexico_analisador(cadena);
        }
    }
}

void Lexico_analisador(char comando[500])
{
    const char delimitador[2] = " ";
    char *token;
    token = strtok(comando, delimitador);
    if(token == NULL)
    {
        printf("A ingresado mal el comando \n");
        return;
    }
    /*** Varialbes para almacenar los datos analizados ***/
    char tam[20]="\0";
    char unit[3]="\0";
    char dir_disco[200]="\0";
    char name[50]="\0";
    char type[3]="\0";
    char fit[4]="\0";
    char eliminar[6]="\0";
    char add[20]="\0";
    char umount[8]="\0";
    char id[20]="\0";
    /*** Fin ***/

    if(strcasecmp(token,"mkdisk")==0)
    {
        token = strtok(NULL,"::");
        while(token!=NULL)
        {
            if(strcasecmp(token,"-size")==0)
            {
                token = strtok(NULL," ");
                token++;
                strcpy(tam,token);printf("EL size: %s\n",tam); /** eliminar el print **/
            }
            else if(strcasecmp(token,"+unit")==0)
            {
                token = strtok(NULL," ");
                token++;
                strcpy(unit,token);
                printf("Prefijo: %s\n",unit); /** ELiminar el pritn **/
            }
            else if(strcasecmp(token,"-path")==0)
            {
                token = strtok(NULL," ");
                token+=2;
                if(token[strlen(token)-1]=='\"')
                {
                    token[strlen(token)-1]='\0';
                }
                strcpy(dir_disco,token);
                printf("Tengo esto del paht: %s\n",dir_disco);/*** Lo tengo que quitar ***/
            }
            else if(strcasecmp(token,"-name")==0)
            {
                token = strtok(NULL," ");
                token+=2;
                if(token[strlen(token)-1]=='\"')
                {
                    token[strlen(token)-1]='\0';
                }
                strcpy(name,token);
                printf("El nombre es: %s\n",token);/*** Esto lo tengo que borrar ***/
            }
            else
            {
                printf("No se reconocio el parametro: %s\n",token);
            }
            token = strtok(NULL,"::");
        }//fin wile
        /*** Aqui va la validacion de los datos -size +unit -path -name y su respectiva accion ***/
        if(strcasecmp(tam,"")!=0 & strcasecmp(dir_disco,"")!=0 & strcasecmp(name,"")!=0)
        {
            AD_crearDir(dir_disco);
            int tamano;
            tamano = (int) strtol(tam, (char **)NULL, 10);
            if(strcasecmp(unit,"k")==0)
            {

            }
            else if(strcasecmp(unit,"m")==0)
            {
                tamano = tamano * 1024;
            }
            else if(strcasecmp(unit,"\0")==0)
            {
                tamano = tamano * 1024;
            }
            else
            {
                printf("Error no se reconoce el prefijo del tamaño: %s\n",unit);
                return;
            }
            AD_crearDisco(dir_disco,name,tamano);
        }
        else
        {
            printf("Faltan parametros obligatorios \n");
        }
        /*** Fin ***/
    }//fin if de MKDISK
    else if(strcasecmp(token,"rmdisk")==0)
    {
        token = strtok(NULL,"::");
        if(token==NULL){printf("No a ingresado el path\n"); return;}
        if(strcasecmp(token,"-path")==0)
        {
            token = strtok(NULL," ");
            token+=2;
            if(token[strlen(token)-1]=='\"')
            {
                token[strlen(token)-1]='\0';
            }
            strcpy(dir_disco,token);
            printf("Tengo esto del paht: %s\n",dir_disco);/*** Lo tengo que quitar ***/
            /*** Acemos la accion de Eliminar ***/
            if(strcasecmp(token,"")!=0)
            {
                AD_eliminarDisk(dir_disco);
            }
            else
            {
                printf("No a ingresado el Path \n");
            }
            /*** Fin ***/
        }
        else
        {
            printf("No se reconocio el Parametro: %s\n",token);
        }
    }//fin del if de RMDISK
    else if(strcasecmp(token,"fdisk")==0)
    {
        token = strtok(NULL, "::");
        while(token!=NULL)
        {
            if(strcasecmp(token,"-size")==0)
            {
                token = strtok(NULL," ");
                token++;
                strcpy(tam,token);printf("EL size: %s\n",tam); /** eliminar el print **/
            }
            else if(strcasecmp(token,"+unit")==0)
            {
                token = strtok(NULL," ");
                token++;
                strcpy(unit,token);
                printf("Prefijo: %s\n",unit); /** ELiminar el pritn **/
            }
            else if(strcasecmp(token,"-path")==0)
            {
                token = strtok(NULL," ");
                token+=2;
                if(token[strlen(token)-1]=='\"')
                {
                    token[strlen(token)-1]='\0';
                }
                strcpy(dir_disco,token);
                printf("Tengo esto del paht: %s\n",dir_disco);/*** Lo tengo que quitar ***/
            }
            else if(strcasecmp(token,"+type")==0)
            {
                token = strtok(NULL," ");
                token++;
                strcpy(type,token);
                printf("Tipo de parcion: %s\n",type); /*** Lo tengo que quitar ***/
            }
            else if(strcasecmp(token,"+fit")==0)
            {
                token = strtok(NULL," ");
                token++;
                strcpy(fit,token);
                printf("El Fit es: %s\n",fit); /*** Lo tengo que quitar ***/
            }
            else if(strcasecmp(token,"+delete")==0)
            {
                token = strtok(NULL," ");
                token++;
                strcpy(eliminar,token);
                printf("Tengo en Eliminar: %s\n",eliminar);/*** Lo tengo que quitar ***/
            }
            else if(strcasecmp(token,"-name")==0)
            {
                token = strtok(NULL," ");
                token+=2;
                if(token[strlen(token)-1]=='\"')
                {
                    token[strlen(token)-1]='\0';
                }
                strcpy(name,token);
                printf("El nombre es: %s\n",token);/*** Esto lo tengo que borrar ***/
            }
            else if(strcasecmp(token,"+add")==0)
            {
                token = strtok(NULL," ");
                token++;
                strcpy(add,token);
                printf("la Cantidad es: %s\n",add);/*** Esto lo tengo que borrar ***/
            }
            else
            {
                printf("No se reconocio el parametro: %s\n",token);
            }
            token = strtok(NULL,"::");
        }//fin del while
        /*** Aqui validamos y hacemos las acciones para es comando -size +unit -path +type ***/
        if(strcasecmp(tam,"")!=0 & strcasecmp(dir_disco,"")!=0 & strcasecmp(name,"")!=0)
        {
            int tamano;
            tamano = (int) strtol(tam, (char **)NULL, 10);
            if(strcasecmp(unit,"b")==0)
            {

            }
            else if(strcasecmp(unit,"k")==0)
            {
                tamano = tamano * 1024;
            }
            else if(strcasecmp(unit,"m")==0)
            {
                tamano = tamano * 1024 * 1024;
            }
            else if(strcasecmp(unit,"\0")==0)
            {
                tamano = tamano * 1024;
            }
            else
            {
                printf("Error no se reconoce el prefijo del tamaño: %s\n",unit);
                return;
            }

            if((strcasecmp(type,"p")==0) | (strcasecmp(type,"e")==0) | (strcasecmp(type,"l")==0))
            {}
            else if(strcasecmp(type,"\0")==0)
            {
                strcpy(type,"p");
            }
            else
            {
                printf("El valor de TYPE no es permitido: %s\n",type);
                return;
            }

            if((strcasecmp(fit,"bf")==0) | (strcasecmp(fit,"ff")==0) | (strcasecmp(fit,"wf")==0))
            {

            }
            else if(strcasecmp(fit,"\0")==0)
            {
                strcpy(fit,"wf");
            }
            else
            {
                printf("El valor de FIT no es permitido: %s\n",fit);
                return;
            }

            if(strcasecmp(eliminar,"fast")==0)
            {
                /*** Metodo para eliminar rapido ***/
                return;
            }
            else if(strcasecmp(eliminar,"full")==0)
            {
                /*** Metodo para eliminar completo ***/
                return;
            }
            else if(strcasecmp(eliminar,"\0")==0)
            {
                //No hago nada y listo xD
            }
            else
            {
                printf("El valor de Delete no es permitido: %s\n",eliminar);
            }

            if(strcasecmp(add,"\0")!=0)
            { /*** Accion el comando add ***/
                printf("Vino  el ADD\n");
                return;
            }

            /*** Aqui va la accion de acrear la particon ***/
            AD_CrearParticion(name,tamano,fit,type,dir_disco); /*** Llamada al metodo crear Particioens ***/
        }
        else
        {
            printf("Faltan Parametros Obligatorios\n");
        }
        /*** Fin ***/
    }//fin el if de FDISK
    else if(strcasecmp(token,"mount")==0)
    {
        token = strtok(NULL," ::");
        while(token!=NULL)
        {
            if(strcasecmp(token,"-path")==0)
            {
                token = strtok(NULL,"\"");
                token = strtok(NULL,"\"");
                strcpy(dir_disco,token);
                printf("Tengo esto del paht: %s\n",dir_disco);/*** Lo tengo que quitar ***/
            }
            else if(strcasecmp(token,"-name")==0)
            {
                token = strtok(NULL,"\"");
                token = strtok(NULL,"\"");
                strcpy(name,token);
                printf("El nombre es: %s\n",token);/*** Esto lo tengo que borrar ***/
            }
            else
            {
                printf("No se reconocio el Parametro: %s",token);
            }
            token = strtok(NULL," ::");
        }//fin del while
        /****** Acciones yolo ******/
        if(strcasecmp(dir_disco,"")!=0 & strcasecmp(name,"")!=0)
        {
            Lexico_Montar(dir_disco,name);
        }
        else
        {
            printf("Lista de Particiones Montadas:\n");
            Lexico_MostrarParticionesMontadas();
        }
    }//fin del if de MOUNT
    else if(strcasecmp(token,"umount")==0)
    {
        token = strtok(NULL,"::");
        while(token!=NULL)
        {
            if(strcasecmp(token,"-id")==0)//jljkljkljl
            {
                token = strtok(NULL," ");
                token++;
                strcpy(umount,token);
                printf("Lo que tengo en Umount: %s\n",umount);/*** Eliminar ***/
            }
            token = strtok(NULL,"::");
        }
    }
    else if(strcasecmp(token,"exec")==0)
    {
        token = strtok(NULL,"::");
        if(strcasecmp(token,"-path")==0)
        {
            token = strtok(NULL," ");
            token++;
            /*** Accion de ejecutar el script  ***/
            Lexico_script(token);
        }
        else
        {
            printf("Se esperaba -path:: ¬¬¬¬\n");
        }
    }
    else if(strcasecmp(token,"rep")==0)
    {
        token = strtok(NULL," ::");
        while(token != NULL)
        {
            if(strcasecmp(token,"-name")==0)
            {
                token = strtok(NULL," ");
                token++;
                strcpy(name,token);
                printf("Tengo en name: %s\n",name);
            }
            else if(strcasecmp(token,"-path")==0)
            {
                token = strtok(NULL,"\"");
                token = strtok(NULL,"\"");
                strcpy(dir_disco,token);
                printf("Tengo en path: %s\n",dir_disco);
            }
            else if(strcasecmp(token,"-id")==0)
            {
                token = strtok(NULL," ");
                token++;
                strcpy(id,token);
                printf("Tengo en le id: %s\n",id);
            }
            else
            {
                printf("No se reconocio esto: %s\n",token);
            }
            token = strtok(NULL," ::");
        }
        /*** ACCIONES DEL COMANDO REP ***/
        if(strcasecmp(name,"")!=0 & strcasecmp(dir_disco,"")!=0 & strcasecmp(id,"")!=0)
        {
            Lexico_Rep(dir_disco,name,id);
        }
        else
        {
            printf("Faltan paremetros obligatorios\n");
        }
    }
    else
    {
        printf("No se reconocio el comando principal\n");
    }
}

void Lexico_Montar(char path[500],char nombre[50])
{
    int i;
    char letras[] = "abcdefghijkmlñopqrstuvwxyz";
    FILE *disco;
    disco = fopen (path, "rb+");
    if(disco == NULL)
    {
        printf("No se puede abrir el diso o no existe\n");
        return;
    }
    struct MBR mbr;
    fread (&mbr, sizeof(mbr), 1,disco);
    if((mbr.mbr_partition_1.part_status!='0') & (strcasecmp(mbr.mbr_partition_1.part_name,nombre)==0))
    {

    }
    else if((mbr.mbr_partition_2.part_status!='0') & (strcasecmp(mbr.mbr_partition_2.part_name,nombre)==0))
    {

    }
    else if((mbr.mbr_partition_3.part_status!='0') & (strcasecmp(mbr.mbr_partition_3.part_name,nombre)==0))
    {

    }
    else if((mbr.mbr_partition_4.part_status!='0') & (strcasecmp(mbr.mbr_partition_4.part_name,nombre)==0))
    {

    }
    else
    {
        printf("Error no se encontro la particon inidicada\n");
        return;
    }
    for(i=0; i<20; i++)
    {
        if(discos[i].activa==1) //Miramos si ya hay un disco montado
        {
            if(strcasecmp(discos[i].path,path)==0) //miramos si tiene a misma ruta
            {
                int f;
                for(f=0; f<6;f++)
                {
                    if(discos[i].particiones[f].activa==1) //miramos si la particon esta activa
                    {
                        if(strcasecmp(discos[i].particiones[f].nombre,nombre)==0)
                        {
                            printf("La particon de este disco ya fue montada\n");
                            return;
                        }
                    }
                    else
                    {
                        discos[i].particiones[f].activa = 1;
                        strcpy(discos[i].particiones[f].nombre,nombre);
                        char let = letras[i];
                        sprintf(discos[i].particiones[f].id,"%s%c%d","vd",let,f);
                        printf("Se le asigno el id: %s\n",discos[i].particiones[f].id);
                        return;
                    }
                }
            }
        }
        else
        {
            discos[i].activa = 1;
            strcpy(discos[i].path,path);
            discos[i].particiones[0].activa = 1;
            strcpy(discos[i].particiones[0].nombre,nombre);
            char let = letras[i];
            sprintf(discos[i].particiones[0].id,"%s%c%d","vd",let,0);
            printf("Se le asigno el id: %s\n",discos[i].particiones[0].id);
            return;
        }
    }
    fclose(disco);
}

void Lexico_MostrarParticionesMontadas()
{
    int i;
    for(i=0;i<20;i++)
    {
        if(discos[i].activa==1)
        {
            int f;
            for(f=0;f<6;f++)
            {
                if(discos[i].particiones[f].activa==1)
                {
                    printf("\t# id::%s -path::%s -name::%s",discos[i].particiones[f].id,discos[i].path,discos[i].particiones[f].nombre);
                }
            }
        }
    }
}

void Lexico_Rep(char dir_disco[200], char name[50], char id[20])
{
    int i;
    for(i=0; i<20; i++)
    {
        if(discos[i].activa==1)
        {
            int f;
            for(f=0; f<6; f++)
            {
                if(discos[i].particiones[f].activa==1)
                {
                    if(strcasecmp(discos[i].particiones[f].id,id)==0)
                    {
                        if(strcasecmp(name,"mbr")==0)
                        {
                            printf("Se crear el reporte del MBR del disco\n");

                            return;
                        }
                        else if(strcasecmp(name,"disk")==0)
                        {
                            printf("Se crear el reporte del DISK del disco\n");
                            /*** Accion a implementar ***/
                            return;
                        }
                        else
                        {
                            printf("Ester reporte no se reconocio puede que falte de implementar o Es un Error: %s",name);
                        }
                        return;
                    }
                }
            }
        }
    }
    printf("Error no se encontro el id: %s espesificado\n",id);
}
