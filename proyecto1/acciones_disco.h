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
void AD_CrearParticionLogica(FILE *disk,int inicio, int fin,char name[50], int tam,char fit[3]);
int AD_hayExtendidas(MBR mbr);
int AD_Extendida(MBR mbr);
void AD_EliminarParticon(char del[6],char dir_disco[200], char name[50]);
#endif // acciones
