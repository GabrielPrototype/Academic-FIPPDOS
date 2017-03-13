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
    struct disk_unit *LStart_Disk;
    struct disk_unit *LEnd_Disk;
};

typedef disk_unit Disk_unit;

void init_disk_unit (Disk_unit **Disk, char *Unit){

    (*Disk)->bottom = NULL;
    (*Disk)->top = NULL;
    (*Disk)->iniDir = NULL;
    (*Disk)->unidade = Unit;
};

Disk_unit * search_disk_unit (Disk_unit *LStart_Dsk, char Disk_letter) {
    
};

void insert_disk_unit (Disk_unit **LStart_Dsk, Disk_unit **Disk) {
    
    Disk_unit aux_unit;
    
    if(*LStart_Dsk = NULL){
        *LStart_Dsk = *Disk;
    }
    else{
        aux_unit = search_disk_unit(*LStart_Dsk, (*Disk)->unidade);
        
        if(aux_unit->top == NULL) { //disco será inserido no começo
            
        }
        else if(aux_unit->bottom == NULL) { //disco será inserido no final
            
            
        } else { //disco será inserido no meio
        
        }
    }
};
#endif /* DISK_STRUCTS_H */