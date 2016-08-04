#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "lexico.h"

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


