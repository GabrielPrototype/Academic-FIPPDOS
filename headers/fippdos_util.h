/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   fippdos_util.h
 * Author: titan
 *
 * Created on 10 de Abril de 2017, 19:18
 */

#ifndef FIPPDOS_UTIL_H
#define FIPPDOS_UTIL_H

#include <stddef.h>

char fippdos_fgets(char vetchar[]) {
    
    char *pos;
    if ((pos = strchr(vetchar, '\n')) != NULL)
        *pos = '\0';
    else
        return 0; /* input too long for buffer, flag error */
};


#endif /* FIPPDOS_UTIL_H */

