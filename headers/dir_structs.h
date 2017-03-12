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

struct dir_header{
    File_header *ListaArq;
    struct dir_header *Head, *PtrPai, *Tail;
    char NomeDir[255];
    char data[9];
    char hora[5];
    
};

typedef dir_header Dir_header;
#endif /* DIR_STRUCTS_H */

