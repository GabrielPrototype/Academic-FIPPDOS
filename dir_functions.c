/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dir_functions.c
 * Author: titan
 *
 * Created on 10 de Abril de 2017, 19:41
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/errors_codes.h"
#include "headers/dir_structs.h"
#include "headers/disk_structs.h"
#include "headers/constants.h"
/*
 * 
 */
void dir_init_header(Dir_header **PtrDir, char nomeDir[], char data[], char hora[]) {

    (*PtrDir) = (Dir_header*) malloc(sizeof (Dir_header));
    (*PtrDir)->Head = NULL;
    (*PtrDir)->Tail = NULL;
    (*PtrDir)->ListaArq = NULL;
    (*PtrDir)->PtrPai = NULL;
    strncpy((*PtrDir)->NomeDir, nomeDir, CONST_DIR_SIZE);
    strncpy((*PtrDir)->data, data, CONST_DATA_SIZE);
    strncpy((*PtrDir)->hora, hora, CONST_HORA_SIZE);
};

//dir_header *Cons(Dir_header **Construcao) {
//
//}

char dir_insert_diretorio(Dir_header **Dir_top, Dir_header **Dir) {
    Dir_header *aux, *ant;
    //verificar se e a unica pasta dentro do pai se nao inserir ordenado
    if ((*Dir_top)->Head == NULL) {
        (*Dir_top)->Head = (*Dir);
        (*Dir)->PtrPai = (*Dir_top);
    } else {
        if (strcmp((*Dir)->NomeDir, (*Dir_top)->Head->NomeDir) < 0) {
            (*Dir)->Tail = (*Dir_top)->Head;
            (*Dir_top)->Head = (*Dir);
            (*Dir)->PtrPai = (*Dir_top);
        } else {
            aux = (*Dir_top)->Head;
            while (aux != NULL && strcmp(aux->NomeDir, (*Dir)->NomeDir) < 0) {
                ant = aux;
                aux = aux->Tail;
            }
            if (strcmp(ant->NomeDir, (*Dir)->NomeDir) == 0) {
                return ERROR_DUPLICATED_DIR; // não é possivel inserir diretorios duplicados
            }
            if (aux == NULL) { // insere no fim
                ant->Tail = *Dir;
                (*Dir)->PtrPai = (*Dir_top);
            } else { //insere no meio
                ant->Tail = (*Dir);
                (*Dir)->Tail = aux;
                (*Dir)->PtrPai = (*Dir_top);
            }
        }
    }
}

Dir_header *dir_find_dir(Dir_header **Dir_top, char Dir_name[]) {

    Dir_header *aux = *Dir_top;

    while (aux->Tail != NULL && strcmp(aux->NomeDir, Dir_name) > 0);
    {
        aux = aux->Tail;
    }

    if (strcmp(aux->NomeDir, Dir_name) == 0)
        return aux;
    return NULL;
}

char dir_delete_allfiles(Dir_header *Dir) {

    //repetiçao para deletar arquivos
    while (Dir->ListaArq != NULL) {
        //recebe primeiro arquivo
        //deleta o arquivo
    }
};

char dir_delete_rec(Dir_header **Dir_top, Dir_header **Dir) {

    Dir_header *aux;
    while ((*Dir)->Head != NULL) {
        aux = (*Dir)->Head;
        (*Dir)->Head = aux->Tail;
        dir_delete_rec(&(*Dir), &aux);

    }
    (*Dir)->Head = NULL;
    dir_delete_allfiles(*Dir);
    free(*Dir);
};

char dir_Delete_byname(Dir_header **Dir_top, char Dir_name[]) { //deleção de diretorios recursivamente

    Dir_header *dir, *dir_ant, *aux;

    dir_ant = *Dir_top;
    dir = *Dir_top;

    while (dir->Tail != NULL && strcmp(dir->NomeDir, Dir_name) > 0);
    {
        dir_ant = dir;
        dir = dir->Tail;
    }

    if (strcmp(dir->NomeDir, Dir_name) != 0) // Diretorio não encontrado
        return ERROR_DIR_NOT_FOUND;


    { // Bloco para remoção do Dir da lista.

        if ((*Dir_top)->Head == dir && dir->Tail == NULL) {//primeiro e unico

            (*Dir_top)->Head = NULL;

        } else if ((*Dir_top)->Head == dir) { //primeiro, mas com vizinhos a direita.

            aux = dir->Tail;
            *Dir_top = aux;

        } else { // no meio ou no final

            aux = dir->Tail;
            dir_ant = aux;
            //free(dir);
        }
    }

    dir_delete_rec(&(*Dir_top), &dir); // deleta o diretorio
}
