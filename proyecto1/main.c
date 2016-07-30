#include <stdio.h>
#include <stdlib.h>

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

int main()
{
    printf("Hello world!\n");
    return 0;
}
