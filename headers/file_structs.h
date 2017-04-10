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

#include "dir_structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "errors_codes.h"

struct file_content_letter {
    struct file_content_letter *ant, *prox;
    char letra;
};

struct file_content_line {
    struct file_content_line *top, *bottom;
    int letras;
    struct file_content_letter *linha;
};

struct file_header {
    struct file_header *prox;
    char NomeArq[255];
    char data[9];
    char hora[5];
    struct file_content_line *ConteudoArq;
};

typedef struct file_header File_header;

void init_file_header(File_header **PtrFile, char nome, char* data, char *hora) {

    (*PtrFile) = (File_header*) malloc(sizeof (Dir_header));
    strncpy((*PtrFile)->NomeArq, nome, 254);
    strncpy((*PtrFile)->data, data, 9);
    strncpy((*PtrFile)->hora, hora, 5);
    *PtrFile->prox = NULL;
};

void file_insert_in_dir(Dir_header **dir_top, File_header **file_h) {

    File_header *aux, *ant;
    //verificar se e a unica pasta dentro do pai se nao inserir ordenado
    if ((*dir_top)->ListaArq == NULL) {
        (*dir_top)->ListaArq = (*file_h);
    } else {
        if (strcmp((*file_h)->NomeArq, (*dir_top)->ListaArq->NomeArq) < 0) {
            (*file_h)->prox = (*dir_top)->ListaArq;
            (*dir_top)->ListaArq = (*file_h);
        } else {
            aux = (*dir_top)->ListaArq;
            while (aux != NULL && strcmp(aux->NomeArq, (*file_h)->NomeArq) < 0) {
                ant = aux;
                aux = aux->prox;
            }
            if (strcmp(ant->NomeArq, (*file_h)->NomeArq) == 0 || strcmp(aux->NomeArq, (*file_h)->NomeArq) == 0) {
                return ERROR_DUPLICATED_FILE; // não é possivel inserir diretorios duplicados
            }
            if (aux == NULL) { // insere no fim
                ant->prox = *file_h;
            } else { //insere no meio
                ant->prox = (*file_h);
                (*file_h)->prox = aux;
            }
        }
    }
};

void *file_find_in_dir(Dir_header **dir_top, char file_name[]) {

};

void file_delete_dinamicstring_line(void) {

};

void file_delete_all_lines(void) {

};

void file_delete(Dir_header **Dir_top, File_header **file) {

};

void file_Delete_byname(Dir_header **Dir_top, char file_name[]) {

};

/*novos codigos aqui, antes do FILE_STRUCTS_H*/

#endif /* FILE_STRUCTS_H */


