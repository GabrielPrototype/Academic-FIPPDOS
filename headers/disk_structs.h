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


#endif /* DISK_STRUCTS_H */