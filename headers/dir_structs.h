/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dir_structs.h
 * Author: titan
 *
 * Created on 12 de Março de 2017, 15:53
 */

#ifndef DIR_STRUCTS_H
#define DIR_STRUCTS_H

#include <stddef.h>
#include <string.h>
#include "file_structs.h"

struct dir_header {
    File_header *ListaArq;
    struct dir_header *Head, *PtrPai, *Tail; //subdiretorio,ponteiropai,ponteiroirmao
    char NomeDir[255];
    char data[9];
    char hora[5];

};

typedef struct dir_header Dir_header;

void init_dir_header(Dir_header **PtrDir, char nomeDir, char* data, char *hora) {

    (*PtrDir) = (Dir_header*) malloc(sizeof (Dir_header));
    (*PtrDir)->Head = NULL;
    (*PtrDir)->Tail = NULL;
    (*PtrDir)->ListaArq = NULL;
    (*PtrDir)->PtrPai = NULL;
    strncpy((*PtrDir)->NomeDir, nomeDir, 254);
    (*PtrDir)->data[0] = data;
    (*PtrDir)->hora[0] = hora;
};

//dir_header *Cons(Dir_header **Construcao) {
//
//}

void dir_insert_diretorio(Dir_header **Dir_top, Dir_header **Dir) {
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
            if (strcmp(ant->NomeDir, (*Dir)->NomeDir) == 0 || strcmp(aux->NomeDir, (*Dir)->NomeDir) == 0) {
                return -1; // não é possivel inserir diretorios duplicados
            }
            if (aux == NULL) { // insere no fim
                ant->Tail = Dir;
                (*Dir)->PtrPai = (*Dir_top);
            } else { //insere no meio
                ant->Tail = (*Dir);
                (*Dir)->Tail = aux;
                (*Dir)->PtrPai = (*Dir_top);
            }
        }
    }
}

Dir_header **dir_find_dir(Dir_header **Dir_top, char Dir_name[]) {

    Dir_header *aux = *Dir_top;

    while (aux->Tail != NULL && strcmp(aux->NomeDir, Dir_name) > 0);
    {
        aux = aux->Tail;
    }

    if (strcmp(aux->NomeDir, Dir_name) == 0)
        return &aux;
    return NULL;
}

char dir_Delete(Dir_header **Dir_top, char Dir_name[]) {
    Dir_header *dir,*aux;
    dir = dir_find_dir(*Dir_top, Dir_name);
    if (Dir_top->Head==dir) {//primeiro
        //repetiçao para deletar arquivos
        while (dir_num_arquivo > 0) {
            //recebe primeiro arquivo
            //deleta o arquivo
        }
        aux=dir->Tail;
        Dir_top=aux;
        free(dir);
    }
}
#endif /* DIR_STRUCTS_H */

