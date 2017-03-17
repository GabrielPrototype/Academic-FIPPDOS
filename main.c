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
#include "headers/teste_detect_os.h"

/*
 * 
 */
int main(int argc, char** argv) {

    printf("F.I.P.P. DOS");


    //printf("\n\nMah oi, qual o sistema patricia?\n");
    //qualosistemapatricia();
    //diskunit_test();
    printf("\n");
    char info = 'a';
    char *L1;
    char *L2;
    
    L2 = NULL;
    
    if(!((L1 == NULL) && (L2 == NULL)) ){
        printf("Diferentes");
    }
    getchar();
    return (EXIT_SUCCESS);

}


//função para teste da funções relacionadas a unidade de disco

void diskunit_test(void) {

    Disk_unit *ldisk = NULL, *aux = NULL, *aux2 = NULL;

    for (char letra = 'A'; letra <= 'Z'; letra++) {
        diskunit_init(&aux, (char)letra);
        diskunit_insert(&ldisk, &aux);
    }

    printf("\n\n");

    for (aux = ldisk; aux != NULL; aux2 = aux, aux = aux->bottom) {
        printf("unidade %c:\n", aux->unidade);
    }

    printf("\n");

    for (aux2; aux2 != NULL; aux2 = aux2->top) {
        printf("unidade %c:\n", aux2->unidade);
    }

    printf("\n");
    printf("Procurando a unidade A: \n");
    aux = diskunit_find(ldisk, 'A');
    printf("Unidade encontrada = %c:\n", aux->unidade);
    printf("Deletando a Unidade A:");
    diskunit_delete(&ldisk, &aux);

    printf("\n\n");

    for (aux = ldisk; aux != NULL; aux2 = aux, aux = aux->bottom) {
        printf("unidade %c:\n", aux->unidade);
    }

    printf("\n");
    aux = NULL;
    diskunit_init(&aux, (char)'A');
    diskunit_insert(&ldisk, &aux);

    printf("\n");
    
    for (aux = ldisk; aux != NULL; aux2 = aux, aux = aux->bottom) {
        printf("unidade %c:\n", aux->unidade);
    }
    
    printf("\n");
    printf("Deletando toda a lista \n");
    diskunit_delete_all(&ldisk);
    
    if(!ldisk)
        printf("Lista vazia\n");
    
    for (aux = ldisk; aux != NULL; aux2 = aux, aux = aux->bottom) {
        printf("unidade %c:\n", aux->unidade);
    }
    
    printf( "\n",
            "\nInserindo de forma reversa e ordenando automaticamente");
    for (char letra = 'Z'; letra >= 'A'; letra--) {
        diskunit_init(&aux, (char)letra);
        diskunit_insert(&ldisk, &aux);
    }
    
    printf("\n\n");

    for (aux = ldisk; aux != NULL; aux2 = aux, aux = aux->bottom) {
        printf("unidade %c:\n", aux->unidade);
    }
    
    printf("\n");
    printf("Deletando toda a de forma reversa \n");
    diskunit_delete_all_reverse(&ldisk);
    
    if(!ldisk)
        printf("Lista vazia\n");
};