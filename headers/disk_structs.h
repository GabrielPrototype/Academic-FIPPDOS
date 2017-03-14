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
#include "dir_structs.h"

struct disk_unit {
    struct disk_unit *top, *bottom;
    char unidade;
    Dir_header *iniDir;
};

struct disk_unit_list {
    struct disk_unit *LStart_Disk;
    struct disk_unit *LEnd_Disk;
};

typedef struct disk_unit Disk_unit;

void diskunit_init(Disk_unit **Disk, char *Unit) {
    (*Disk) = (Disk_unit*) malloc(sizeof(Disk_unit));
    (*Disk)->bottom = NULL;
    (*Disk)->top = NULL;
    (*Disk)->iniDir = NULL;
    (*Disk)->unidade = Unit;
};

Disk_unit * diskunit_find_pos(Disk_unit *LStart_Dsk, char Disk_letter) {
    Disk_unit *pos_unit;
    while(pos_unit->bottom != NULL && pos_unit->unidade >= Disk_letter)
        pos_unit = pos_unit->bottom;
    
    return pos_unit;
};

void diskunit_insert(Disk_unit **LStart_Dsk, Disk_unit **Disk) {

    Disk_unit *ptrpos;

    if (*LStart_Dsk == NULL) {
        *LStart_Dsk = *Disk;
    } else if ((*LStart_Dsk)->unidade < (*Disk)->unidade) { //disco será inserido no começo

        (*Disk)->bottom = *LStart_Dsk;
        (*LStart_Dsk)->bottom = *Disk;
        *LStart_Dsk = *Disk;
    } else {
        
        ptrpos = diskunit_find_pos(*LStart_Dsk, (*Disk)->unidade);
        if(ptrpos->bottom == NULL) {    //inserção no final
            (*Disk)->top = ptrpos;
            ptrpos->bottom = *Disk;
        } else {                        //inserção entre duas caixas
            (*Disk)->bottom = ptrpos;
            (*Disk)->top = ptrpos->top;
            ptrpos->top->bottom = *Disk;
            ptrpos->top = *Disk;
        }
    }
};
#endif /* DISK_STRUCTS_H */