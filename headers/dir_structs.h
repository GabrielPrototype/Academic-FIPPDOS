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
    strncpy((*PtrDir)->NomeDir, nomeDir,254);
    (*PtrDir)->data[0] = data;
    (*PtrDir)->hora[0] = hora;
};

//dir_header *Cons(Dir_header **Construcao) {
//
//}

void dir_insert_diretorio(Dir_header **Pai, Dir_header **Diretorio) {
    Dir_header *aux, *ant;
    //verificar se e a unica pasta dentro do pai se nao inserir ordenado
    if ((*Pai)->Head == NULL) {
        (*Pai)->Head = (*Diretorio);
        (*Diretorio)->PtrPai = (*Pai);
    } else {
        if (strcmp((*Diretorio)->NomeDir, (*Pai)->Head->NomeDir) < 0) {
            (*Diretorio)->Tail = (*Pai)->Head;
            (*Pai)->Head = (*Diretorio);
            (*Diretorio)->PtrPai = (*Pai);
        } else {
            aux = (*Pai)->Head;
            while (aux != NULL && strcmp(aux->NomeDir, (*Diretorio)->NomeDir) < 0) {
                ant = aux;
                aux = aux->Tail;
            }
            if (strcmp(ant->NomeDir, (*Diretorio)->NomeDir) == 0 || strcmp(aux->NomeDir, (*Diretorio)->NomeDir) == 0) {
                return -1; // não é possivel inserir diretorios duplicados
            }
            if (aux == NULL) {  // insere no fim
                ant->Tail = Diretorio;
                (*Diretorio)->PtrPai = (*Pai);
            } else {                        //insere no meio
                ant->Tail = (*Diretorio);
                (*Diretorio)->Tail = aux;
                (*Diretorio)->PtrPai = (*Pai);
            }
        }
    }
}

Dir_header procurar_pasta(Dir_header **Pai, char *nomePasta) {

}
#endif /* DIR_STRUCTS_H */

