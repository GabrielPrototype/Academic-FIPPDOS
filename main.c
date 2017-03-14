/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   file_structs.h
 * Author: titan
 *
 * Created on 12 de Março de 2017, 15:54
 */

#ifndef FILE_STRUCTS_H
#define FILE_STRUCTS_H

#include "headers/disk_structs.h"

/*
 * 
 */
int main(int argc, char** argv) {

    printf("F.I.P.P. DOS");

    diskunit_test();

    printf("\n");
    return (EXIT_SUCCESS);
}

void diskunit_test(void) {

    Disk_unit *ldisk = NULL, *aux = NULL, *aux2 = NULL;

    for (char letra = 'A'; letra <= 'Z'; letra++) {
        diskunit_init(&aux, letra);
        diskunit_insert(&ldisk, &aux);
    }

    printf("\n");

    /*aux = ldisk;
    while (aux){
        
        printf("unidade %c:\n", aux->unidade);
        aux2 = aux;
        aux = aux->bottom;
    }*/

    printf("\n");
    for (aux = ldisk; aux != NULL; aux2 = aux, aux = aux->bottom) {
        printf("unidade %c:\n", aux->unidade);
    }

    printf("\n");

    /*while (aux2){
        
        printf("unidade %c:\n", aux2->unidade);
        
        aux2 = aux2->top;
    }*/

    for (aux2; aux2 != NULL; aux2 = aux2->top) {
        printf("unidade %c:\n", aux2->unidade);
    }
    
    printf("\n");
    
    aux = diskunit_find_pos(&ldisk,'C');
    printf("Unidade encontrada = %c:", aux->unidade);
};
