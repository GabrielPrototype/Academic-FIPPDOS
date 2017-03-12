/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   disk_structs.h
 * Author: titan
 *
 * Created on 12 de Março de 2017, 15:53
 */

#ifndef DISK_STRUCTS_H
#define DISK_STRUCTS_H

#include <stddef.h>



struct disk_unit {
    struct disk_unit *top, *bottom;
    char unidade;
    Dir_header *iniDir;
};

struct disk_unit_list{

};

typedef disk_unit Disk_unit;

void init_disk_unit (Disk_unit **Disk, char *Unit){

    (*Disk)->bottom = NULL;
    (*Disk)->top = NULL;
    (*Disk)->iniDir = NULL;
    (*Disk)->unidade = Unit;
};

void insert_disk_unit (Disk_unit **LStart_Dsk, Disk_unit **Disk) {
    
    if(*LStart_Dsk = NULL){
        (*LSt)
    }
    else{
    
    }
};
#endif /* DISK_STRUCTS_H */