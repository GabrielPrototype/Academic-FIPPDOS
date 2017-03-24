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
#include <stdlib.h>
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

void diskunit_init(Disk_unit **Disk, char *Unit) {//criacaixa
    (*Disk) = (Disk_unit*) malloc(sizeof (Disk_unit));
    (*Disk)->bottom = NULL;
    (*Disk)->top = NULL;
    (*Disk)->iniDir = NULL;
    (*Disk)->unidade = Unit;
};

Disk_unit * diskunit_find_pos(Disk_unit *LStart_Dsk, char Disk_letter) {
    Disk_unit *pos_unit = NULL;
    pos_unit = LStart_Dsk;
    while (pos_unit->bottom != NULL && pos_unit->unidade <= Disk_letter)
        pos_unit = pos_unit->bottom;

    return pos_unit;
};

Disk_unit * diskunit_find(Disk_unit *LStart_Dsk, char Disk_letter) {

    Disk_unit *disk = LStart_Dsk;
    while (disk != NULL && disk->unidade < Disk_letter)
        disk = disk->bottom;
    if (disk && disk->unidade == Disk_letter) {
        return disk;
    }

    return NULL;
};

void diskunit_insert(Disk_unit **LStart_Dsk, Disk_unit **Disk) {

    Disk_unit *ptrpos;

    if (*LStart_Dsk == NULL) {
        *LStart_Dsk = *Disk;
    } else if ((*Disk)->unidade < (*LStart_Dsk)->unidade) { //disco será inserido no começo

        (*Disk)->bottom = *LStart_Dsk;
        (*LStart_Dsk)->top = *Disk;
        *LStart_Dsk = *Disk;
    } else {

        ptrpos = diskunit_find_pos(*LStart_Dsk, (*Disk)->unidade);
        if (ptrpos->bottom == NULL) { //inserção no final
            (*Disk)->top = ptrpos;
            ptrpos->bottom = *Disk;
        } else { //inserção entre duas caixas

            (*Disk)->bottom = ptrpos;
            (*Disk)->top = ptrpos->top;
            ptrpos->top->bottom = *Disk;
            ptrpos->top = *Disk;
        }
    }
};

void diskunit_delete(Disk_unit **LStart_Dsk, Disk_unit **Disk) {

    if ((*LStart_Dsk)->unidade == (*Disk)->unidade) {
        *LStart_Dsk = (*Disk)->bottom;
        if ((*Disk)->bottom)
            (*LStart_Dsk)->top = NULL;
    } else {
        if ((*Disk)->top != NULL)
            (*Disk)->top->bottom = (*Disk)->bottom;

        if ((*Disk)->bottom != NULL)
            (*Disk)->bottom->top = (*Disk)->top;
    }

    free((*Disk));

};

void diskunit_delete_teste(Disk_unit **Disk, Disk_unit **LStart_Dsk) {

    if ((*Disk)->top != NULL)
        (*Disk)->top->bottom = (*Disk)->bottom;
    if ((*Disk)->bottom != NULL)
        *LStart_Dsk = (*Disk)->bottom;
    free((*Disk));
};

void diskunit_delete_all(Disk_unit **LStart_Dsk) {

    Disk_unit *aux;
    while ((*LStart_Dsk)) {
        aux = *LStart_Dsk;
        diskunit_delete(&(*LStart_Dsk), &aux);
    }
};

void diskunit_delete_all_reverse(Disk_unit **LStart_Dsk) {
    
    Disk_unit *aux, *aux2;
    
//    aux = *LStart_Dsk;
//    while (aux->bottom){
//        aux = aux->bottom;
//    }
    
    for (aux = *LStart_Dsk; aux->bottom; aux = aux->bottom);
    
    while (aux) {
        aux2 = aux;
        diskunit_delete(&aux, &aux2);
    }
}
#endif /* DISK_STRUCTS_H */