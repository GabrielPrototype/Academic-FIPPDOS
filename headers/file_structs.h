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

void file_insert_in_dir(void) {
    
};

void *file_find_in_dir(Dir_header **Dir_top, char file_name[]) {
    
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


