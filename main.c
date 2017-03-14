/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: titan
 *
 * Created on 12 de Março de 2017, 01:48
 */

#include <stdio.h>
#include <stdlib.h>

#include "headers/disk_structs.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    printf("F.I.P.P. DOS");
    
    Disk_unit *ldisk = NULL, *aux = NULL;
    
    for(char letra = 'A'; letra <= 'Z'; letra++){
        diskunit_init(&aux, letra);
        diskunit_insert(&ldisk,&aux);
    }
    
    printf("\n");
    
    for( aux = ldisk; aux->bottom != NULL; aux = aux->bottom){
        printf("unidade %c:\n", aux->unidade);
    }
    
    printf("\n");
    return (EXIT_SUCCESS);
}

