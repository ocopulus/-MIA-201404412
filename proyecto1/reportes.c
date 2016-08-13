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

    int ex = Rep_hayExtendidas(mbr);
    if(ex!=0)
    {
        int numpar = Rep_Extendida(mbr);
        struct EBR ebr;
        if(numpar == 1)
        {
            fseek(disco,mbr.mbr_partition_1.part_start,SEEK_SET);
            fread(&ebr,sizeof(ebr),1,disco);
            Rep_log(disco,ebr,rep);
        }
        else if(numpar == 2)
        {
            fseek(disco,mbr.mbr_partition_2.part_start,SEEK_SET);
            fread(&ebr,sizeof(ebr),1,disco);
            Rep_log(disco,ebr,rep);
        }
        else if(numpar == 3)
        {
            fseek(disco,mbr.mbr_partition_3.part_start,SEEK_SET);
            fread(&ebr,sizeof(ebr),1,disco);
            Rep_log(disco,ebr,rep);
        }
        else if(numpar == 4)
        {
            fseek(disco,mbr.mbr_partition_4.part_start,SEEK_SET);
            fread(&ebr,sizeof(ebr),1,disco);
            Rep_log(disco,ebr,rep);
        }
    }

    /*** Fin ***/

    fprintf(rep,"}\n");
    fclose(rep);
    fclose(disco);
    system("dot -Tpng mbr.dot -o mbr.png");
    system("xdg-open mbr.png");
}

void Rep_log(FILE *disk,struct EBR ebr,FILE *rep)
{
    if(ebr.part_status == '1')
    {
        fprintf(rep, "a%i [label=<<TABLE border=\"1\" cellspacing=\"1\" cellpadding=\"1\"  >\n",ebr.part_start);

        fprintf(rep, "<TR>\n");
        fprintf(rep, "<TD border=\"1\" >Nombre: </TD>\n");
        fprintf(rep, "<TD border=\"1\" >Valor  </TD>\n");
        fprintf(rep, "</TR>\n");

        fprintf(rep, "<TR>\n");
        fprintf(rep, "<TD border=\"1\" >part_status_l: </TD>\n");
        fprintf(rep, "<TD border=\"1\" >%c  </TD>\n",ebr.part_status);
        fprintf(rep, "</TR>\n");

        fprintf(rep, "<TR>\n");
        fprintf(rep, "<TD border=\"1\" >part_fit_l: </TD>\n");
        fprintf(rep, "<TD border=\"1\" >%s  </TD>\n",ebr.part_fit);
        fprintf(rep, "</TR>\n");

        fprintf(rep, "<TR>\n");
        fprintf(rep, "<TD border=\"1\" >part_start_l: </TD>\n");
        fprintf(rep, "<TD border=\"1\" >%i  </TD>\n",ebr.part_start);
        fprintf(rep, "</TR>\n");

        fprintf(rep, "<TR>\n");
        fprintf(rep, "<TD border=\"1\" >part_size_l: </TD>\n");
        fprintf(rep, "<TD border=\"1\" >%i  </TD>\n",ebr.part_size);
        fprintf(rep, "</TR>\n");

        fprintf(rep, "<TR>\n");
        fprintf(rep, "<TD border=\"1\" >part_next_l: </TD>\n");
        fprintf(rep, "<TD border=\"1\" >%i  </TD>\n",ebr.part_next);
        fprintf(rep, "</TR>\n");

        fprintf(rep, "<TR>\n");
        fprintf(rep, "<TD border=\"1\" >part_name_l: </TD>\n");
        fprintf(rep, "<TD border=\"1\" >%s  </TD>\n",ebr.part_name);
        fprintf(rep, "</TR>\n");

        fprintf(rep, "</TABLE>>];\n");
        if(ebr.part_next > ebr.part_start)
        {
            fseek(disk,ebr.part_next,SEEK_SET);
            fread(&ebr,sizeof(ebr),1,disk);
            Rep_log(disk,ebr,rep);
        }
    }
}

int Rep_hayExtendidas(MBR mbr)
{
    int resultado=0;

    if(mbr.mbr_partition_1.part_status!='0')
    {
        if(mbr.mbr_partition_1.part_type == 'e')
        {
            resultado++;
        }
    }

    if(mbr.mbr_partition_2.part_status!='0')
    {
        if(mbr.mbr_partition_2.part_type == 'e')
        {
            resultado++;
        }
    }

    if(mbr.mbr_partition_3.part_status!='0')
    {
        if(mbr.mbr_partition_3.part_type == 'e')
        {
            resultado++;
        }
    }

    if(mbr.mbr_partition_4.part_status!='0')
    {
        if(mbr.mbr_partition_4.part_type == 'e')
        {
            resultado++;
        }
    }
    return resultado;
}
int Rep_Extendida(MBR mbr)
{
    int resultado = 0;
    if(mbr.mbr_partition_1.part_status!='0')
    {
        if(mbr.mbr_partition_1.part_type == 'e')
        {
            return 1;
        }
    }

    if(mbr.mbr_partition_2.part_status!='0')
    {
        if(mbr.mbr_partition_2.part_type == 'e')
        {
            return 2;
        }
    }

    if(mbr.mbr_partition_3.part_status!= '0')
    {
        if(mbr.mbr_partition_3.part_type == 'e')
        {
            return 3;
        }
    }

    if(mbr.mbr_partition_4.part_type == '0')
    {
        if(mbr.mbr_partition_4.part_type == 'e')
        {
            return 4;
        }
    }

    return resultado;
}

void Rep_disk(char dir[200], char dir_rep[200])
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
    FILE* rep;
    rep = fopen("disk.dot", "w");
    fprintf(rep,"digraph DISk{\n");
    fprintf(rep,"subgraph sub {\n");
    fprintf(rep,"node[shape=record];\n");

    fprintf(rep,"MBR[label=\" MBR \"];\n");
    if(mbr.mbr_partition_1.part_status=='1')
    {
        fprintf(rep,"p1[label=\" Nombre: %s \\n type: %c \"];\n",mbr.mbr_partition_1.part_name,mbr.mbr_partition_1.part_type);
    }
    else
    {
        fprintf(rep,"p1[label=\" LIBRE \"];\n");
    }

    if(mbr.mbr_partition_2.part_status=='1')
    {
        fprintf(rep,"p2[label=\" Nombre: %s \\n type: %c \"];\n",mbr.mbr_partition_2.part_name,mbr.mbr_partition_2.part_type);
    }
    else
    {
        fprintf(rep,"p2[label=\" LIBRE \"];\n");
    }

    if(mbr.mbr_partition_3.part_status=='1')
    {
        fprintf(rep,"p3[label=\" Nombre: %s \\n type: %c \"];\n",mbr.mbr_partition_3.part_name,mbr.mbr_partition_3.part_type);
    }
    else
    {
        fprintf(rep,"p3[label=\" LIBRE \"];\n");
    }

    if(mbr.mbr_partition_4.part_status=='1')
    {
        fprintf(rep,"p4[label=\" Nombre: %s \\n type: %c \"];\n",mbr.mbr_partition_4.part_name,mbr.mbr_partition_4.part_type);
    }
    else
    {
        fprintf(rep,"p4[label=\" LIBRE \"];\n");
    }

    fprintf(rep,"}\n");
    fprintf(rep,"}\n");
    fclose(disco);
    fclose(rep);
    system("dot -Tpng disk.dot -o disk.png");
    system("xdg-open mbr.png");
}
