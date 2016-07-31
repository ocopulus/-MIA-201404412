#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct particion{
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
}particion;

typedef struct MBR {
    int mbr_tamano;
    int mbr_fecha_creacion;//El tipo cambiar
    int mbr_disk_signature;
    struct particion mbr_partition_1;
    struct particion mbr_partition_2;
    struct particion mbr_partition_3;
    struct particion mbr_partition_4;
}MBR;

typedef struct EBR{
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
}EBR;
void analisador();
int main()
{
   char str[80] = "This is  www.tutorialspoint.com - website";
   const char s[2] = " ";
   char *token;

   /* get the first token */
   token = strtok(str, s);

   /* walk through other tokens */
   /*while( token != NULL )
   {
      printf( " %s\n", token );

      token = strtok(NULL, s);
   } */

    /*char pala[300];
    char *p = "puta mierda;";
    strcpy(pala,p);
    printf(pala);*/
    char p[50] = "hola";
    char *d = "hola";
    if(strcmp(p,"ptua")==0)
    {
        printf("Es igual\n");
    }
    else
    printf("No es igual\n");
    analisador();
   return 0;
}

void analisador()
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
    //printf("Ingreso: %s",comando);
    const char delimitador[2] = " ";
    char *token;
    token = strtok(comando, delimitador);
    if(token == NULL)
    {
        printf("A ingresado mal el comando \n");
        return;
    }

    if(strcmp(token,"mkdisk")==0)
    {
        token = strtok(NULL,"::");
        char tam[20];
        while(token!=NULL)
        {
            if(strcmp(token,"-size")==0)
            {
                token = strtok(NULL," ");
                strcpy(tam,token);
            }
            else if(strcmp(token,"")==0)
            {

            }
            token = strtok(NULL,"::");
        }
    }

}


