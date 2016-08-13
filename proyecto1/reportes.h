#ifndef REPORTES
#define REPORTES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "estructuras.h"

void Rep_mbr(char dir[200], char dir_rep[200]);
void Rep_log(FILE *disk,struct EBR ebr,FILE *rep);
int Rep_hayExtendidas(MBR mbr);
int Rep_Extendida(MBR mbr);
void Rep_disk(char dir[200], char dir_rep[200]);

#endif // REPORTES
