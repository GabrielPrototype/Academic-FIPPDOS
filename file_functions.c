/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   file_functions.c
 * Author: titan
 *
 * Created on 10 de Abril de 2017, 19:39
 */

#include <stdio.h>
#include <stdlib.h>
#include "headers/errors_codes.h"
#include "headers/file_structs.h"
#include "headers/dir_structs.h"
#include "headers/disk_structs.h"
/*
 * 
 */
void init_file_content_letter(File_content_letter **ptrLetra, char *letra) {
    (*ptrLetra) = (File_content_letter*) malloc(sizeof (File_content_letter));
    (*ptrLetra)->ant = NULL;
    (*ptrLetra)->prox = NULL;
    (*ptrLetra)->letra = letra;
};

void init_file_content_line(File_content_line **ptrLinha, int *numletras) {
    (*ptrLinha) = (File_content_letter*) malloc(sizeof (File_content_letter));
    (*ptrLinha)->top = NULL;
    (*ptrLinha)->bottom = NULL;
    (*ptrLinha)->letras = numletras;
};

void init_file_header(File_header **PtrFile, char nome, char* data, char *hora) {

    (*PtrFile) = (File_header*) malloc(sizeof (File_header));
    strncpy((*PtrFile)->NomeArq, nome, 254);
    strncpy((*PtrFile)->data, data, 9);
    strncpy((*PtrFile)->hora, hora, 5);
    (*PtrFile)->prox = NULL;
};

char file_insert_in_dir(Dir_header **dir_top, File_header **file_h) {

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

    file_delete_string_line(&(*lista)->letras);
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

char file_Delete_byname(File_header **lista_arq, char file_name[]) {

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

