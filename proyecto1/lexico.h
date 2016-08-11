#ifndef LEXICOH
#define LEXICOH
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "acciones_disco.h"

typedef struct par{
    int activa;
    char id[50];
    char nombre[50];
}par;

typedef struct disco{
    char path[200];
    int activa;
    struct par particiones[6];
}disco;

struct disco discos[20];

void Lexico_entrada();
void Lexico_analisador(char comando[500]);
void Lexico_script(char path[500]);
void Lexico_Montar(char path[500],char nombre[50]);
void Lexico_MostrarParticionesMontadas();
#endif // LEXICOH
