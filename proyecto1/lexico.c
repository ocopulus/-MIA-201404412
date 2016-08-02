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
    char tam[20];
    char unit[3];
    char dir_disco[200];
    char name[16];
    char type[3];
    char fit[4];
    char eliminar[6];
    char add[20];
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
                token++;
                strcpy(name,token);
                printf("El nombre es: %s",token);/*** Esto lo tengo que borrar ***/
            }
            else
            {
                printf("No se reconocio el parametro: %s\n",token);
            }
            token = strtok(NULL,"::");
        }//fin wile
        /*** Aqui va la validacion de los datos -size +unit -path -name y su respectiva accion ***/

        /*** Fin ***/
    }//fin if de MKDISK
    else if(strcasecmp(token,"rmdisk")==0)
    {
        token = strtok(NULL,"::");
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
                token++;
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
    }//fin el if de FDISK
    else if(strcasecmp(token,"mount")==0)
    {
        token = strtok(NULL,"::");
        while(token!=NULL)
        {
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

            }
            else if(strcasecmp(token,"-name")==0)
            {
                token = strtok(NULL," ");
                token++;
                strcpy(name,token);
                printf("El nombre es: %s\n",token);/*** Esto lo tengo que borrar ***/
            }
            else
            {
                printf("No se reconocio el Parametro: %s",token);
            }
            token = strtok(NULL,"::");
        }//fin del while
    }//fin del if de MOUNT
}
