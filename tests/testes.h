/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   structs_test.h
 * Author: titan
 *
 * Created on 9 de Abril de 2017, 16:27
 */

#ifndef TESTES_H
#define TESTES_H

#include "headers/disk_structs.h"
#include "headers/dir_structs.h"
#include "headers/teste_detect_os.h"
#include "headers/commands.h"

void tempo_test(void) {

    time_t t = time(NULL);
    struct tm *tempo = localtime(&t);
    struct tm tempo2 = *tempo;
    printf("\nnow: %d-%d-%d %d:%d:%d\n", tempo2.tm_year + 1900, tempo2.tm_mon + 1, tempo2.tm_mday, tempo2.tm_hour, tempo2.tm_min, tempo2.tm_sec);
};

void diskunit_test(void) {

    Disk_unit *ldisk = NULL, *aux = NULL, *aux2 = NULL;
    for (char letra = 'A'; letra <= 'Z'; letra++) {
        diskunit_init(&aux, (char) letra);
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
    diskunit_init(&aux, (char) 'A');
    diskunit_insert(&ldisk, &aux);

    printf("\n");

    for (aux = ldisk; aux != NULL; aux2 = aux, aux = aux->bottom) {
        printf("unidade %c:\n", aux->unidade);
    }

    printf("\n");
    printf("Deletando toda a lista \n");
    diskunit_delete_all(&ldisk);

    if (!ldisk)
        printf("Lista vazia\n");

    for (aux = ldisk; aux != NULL; aux2 = aux, aux = aux->bottom) {
        printf("unidade %c:\n", aux->unidade);
    }

    printf("\n\nInserindo de forma reversa e ordenando automaticamente");
    for (char letra = 'Z'; letra >= 'A'; letra--) {
        diskunit_init(&aux, (char) letra);
        diskunit_insert(&ldisk, &aux);
    }

    printf("\n\n");

    for (aux = ldisk; aux != NULL; aux2 = aux, aux = aux->bottom) {
        printf("unidade %c:\n", aux->unidade);
    }

    printf("\n");
    printf("Deletando toda a de forma reversa \n");
    diskunit_delete_all_reverse(&ldisk);

    if (!ldisk)
        printf("Lista vazia\n");

};

//função para teste da funções relacionadas a diretorios

void dir_test(void) {

    Dir_header *test_C, *aux, *aux2;


    dir_insert_diretorio(&test_C, aux);

}
#endif /* TESTES_H */

