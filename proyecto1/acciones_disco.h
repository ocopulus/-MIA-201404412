#ifndef acciones
#define acciones
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "estructuras.h"

void AD_crearDir(char dir_disco[200]);
void AD_eliminarDisk(char dir_disco[200]);
void AD_crearDisco(char dir_disco[200], char name[50], int tam);
void AD_CrearParticion(char name[50],int tam, char fit[3], char type[3], char path[200]);
int AD_hayExtendidas(MBR mbr);
#endif // acciones
