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

typedef struct file_content_letter File_content_letter;
typedef struct file_content_line File_content_line;
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

    File_header *aux = *dir_top;

    while (aux->prox != NULL && strcmp(aux->NomeArq, file_name) > 0);
    {
        aux = aux->prox;
    }

    if (strcmp(aux->NomeArq, file_name) == 0)
        return aux;

    return NULL;

};

void file_delete_letter(File_content_letter **lista, File_content_letter **letra) {
    
    if (*lista == *letra) {
        *lista = (*letra)->prox;
        if ((*letra)->prox)
            (*lista)->ant = NULL;
    } else {
        if ((*letra)->ant != NULL)
            (*letra)->ant->prox = (*letra)->prox;

        if ((*letra)->prox != NULL)
            (*letra)->prox->ant = (*letra)->ant;
    }
    free((*letra));
};

void file_delete_string_line(File_content_letter **lista) {
    Disk_unit *aux;
    while ((*lista)) {
        aux = *lista;
        file_delete_letter(&(*lista), &aux);
    }
};

void file_delete_line(File_content_line **lista, File_content_line **linha) {

    if (*lista == *linha) {
        *lista = (*linha)->bottom;
        if ((*linha)->bottom)
            (*lista)->top = NULL;
    } else {
        if ((*linha)->top != NULL)
            (*linha)->top->bottom = (*linha)->bottom;

        if ((*linha)->bottom != NULL)
            (*linha)->bottom->top = (*linha)->top;
    }

    file_delete_string_line(&(lista)->letras)
    free((*linha));

};

void file_delete_all_lines(File_content_line **lista) {
    Disk_unit *aux;
    while ((*lista)) {
        aux = *lista;
        file_delete_line(&(*lista), &aux);
    }
};

void file_delete(File_header **lista_arq, File_header **file) {
    File_header *aux;

    file_delete_all_lines(&(*file)->ConteudoArq);
    free(*file);
};

void file_Delete_byname(File_header **lista_arq, char file_name[]) {

    File_header *file, *file_ant, *aux;

    file_ant = *lista_arq;
    file = *lista_arq;

    while (file->prox != NULL && strcmp(file->NomeArq, file_name) > 0);
    {
        file_ant = file;
        file = file->prox;
    }

    if (strcmp(file->NomeArq, file_name) != 0) // arquivo não encontrado
        return ERROR_FILE_NOT_FOUND;


    { // Bloco para remoção do Dir da lista.

        if (lista_arq == file && file->prox == NULL) {//primeiro e unico

            lista_arq = NULL;

        } else if (lista_arq == file) { //primeiro, mas com vizinhos a direita.

            aux = file->prox;
            *lista_arq = aux;

        } else { // no meio ou no final

            aux = file->prox;
            file_ant = aux;
            //free(dir);
        }
    }

    file_delete(&(*lista_arq), &file); // deleta o diretorio
};

/*novos codigos aqui, antes do FILE_STRUCTS_H*/

#endif /* FILE_STRUCTS_H */


