#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "lexico.h"

int main()
{ char d; char f[5] = "df";
    srand(time(NULL));
    bool menu = true;
    int i = 1;
    int a;
    for(a=0;a<20;a++)
    {
        discos[a].activa = 0;
        int b;
        for(b=0;b<6;b++)
        {
            discos[a].particiones[b].activa = 0;
        }
    }
    while (menu)
    {
        Lexico_entrada();
        printf("\n\nIngrese 1 si desea continuar \n Cuarlquier numero si desea salir\n");
        fflush(stdin);
        scanf(" %i", &i);
        if(i!=1)
        {
            menu = false;
        }
    }
   return 0;
}


