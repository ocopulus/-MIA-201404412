#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "lexico.h"

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
    time_t mbr_fecha_creacion;
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

typedef struct SB{
    int s_filesystem_type;
    int s_inodes_count;
    int s_blocks_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    time_t s_mtime;
    time_t s_umtime;
    int s_mnt_count;
    int s_magic;
    int s_inode_size;
    int s_blocks_size;
    int s_first_ino;
    int s_first_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;
}SB;

typedef struct journal{
    //Tengo dudas con los tipos jaja
}journal;


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
    if(strcasecmp(p,"Hola")==0)
    {
        printf("Es igual\n");
    }
    else
    printf("No es igual\n");
    Lexico_entrada();
   return 0;
}


