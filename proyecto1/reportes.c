#include "reportes.h"

void Rep_mbr(char dir[200], char dir_rep[200])
{
    struct MBR mbr;
    FILE *disco;
    disco = fopen (dir, "rb+");
    if( disco == NULL)
    {
        printf("¡El Disco no existe!\n");
        return;
    }
    fread (&mbr, sizeof(mbr), 1,disco);
    fclose(disco);
    FILE* rep;
    rep = fopen("mbr.dot", "w");
    fprintf(rep,"digraph MBR{\n");
    fprintf(rep,"node[shape=record];\n");

    /*** Aqui biene la magia ***/
    fprintf(rep, "a0 [label=<<TABLE border=\"1\" cellspacing=\"1\" cellpadding=\"1\"  >\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >Nombre: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >Valor:  </TD>\n");
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >mbr_tamaño: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%i  </TD>\n",mbr.mbr_tamano);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >mbr_fecha_creacion: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%s  </TD>\n",ctime(&mbr.mbr_fecha_creacion));
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >mbr_disk_signature: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%i  </TD>\n",mbr.mbr_disk_signature);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_status_1:  </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%c  </TD>\n",mbr.mbr_partition_1.part_status);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_type_1:</TD>\n");
    fprintf(rep, "<TD border=\"1\" >%c  </TD>\n",mbr.mbr_partition_1.part_type);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_fit_1: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%s  </TD>\n",mbr.mbr_partition_1.part_fit);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_start_1: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%i  </TD>\n",mbr.mbr_partition_1.part_start);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_size_1: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%i  </TD>\n",mbr.mbr_partition_1.part_size);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_name_1: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%s  </TD>\n",mbr.mbr_partition_1.part_name);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_status_2: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%c  </TD>\n",mbr.mbr_partition_2.part_status);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_type_2:</TD>\n");
    fprintf(rep, "<TD border=\"1\" >%c  </TD>\n",mbr.mbr_partition_2.part_type);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_fit_2: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%s  </TD>\n",mbr.mbr_partition_2.part_fit);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_start_2: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%i  </TD>\n",mbr.mbr_partition_2.part_start);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_size_2: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%i  </TD>\n",mbr.mbr_partition_2.part_size);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_name_2: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%s  </TD>\n",mbr.mbr_partition_2.part_name);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_status_3: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%c  </TD>\n",mbr.mbr_partition_3.part_status);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_type_3:</TD>\n");
    fprintf(rep, "<TD border=\"1\" >%c  </TD>\n",mbr.mbr_partition_3.part_type);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_fit_3: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%s  </TD>\n",mbr.mbr_partition_3.part_fit);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_start_3: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%i  </TD>\n",mbr.mbr_partition_3.part_start);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_size_3: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%i  </TD>\n",mbr.mbr_partition_3.part_size);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_name_3: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%s  </TD>\n",mbr.mbr_partition_3.part_name);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_status_4: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%c  </TD>\n",mbr.mbr_partition_4.part_status);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_type_4:</TD>\n");
    fprintf(rep, "<TD border=\"1\" >%c  </TD>\n",mbr.mbr_partition_4.part_type);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_fit_4: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%s  </TD>\n",mbr.mbr_partition_4.part_fit);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_start_4: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%i  </TD>\n",mbr.mbr_partition_4.part_start);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_size_4: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%i  </TD>\n",mbr.mbr_partition_4.part_size);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "<TR>\n");
    fprintf(rep, "<TD border=\"1\" >part_name_4: </TD>\n");
    fprintf(rep, "<TD border=\"1\" >%s  </TD>\n",mbr.mbr_partition_4.part_name);
    fprintf(rep, "</TR>\n");

    fprintf(rep, "</TABLE>>];\n");
    /*** Fin ***/

    fprintf(rep,"}\n");
    fclose(rep);
    system("dot -Tpng mbr.dot -o mbr.png");
    system("xdg-open mbr.png");
}
