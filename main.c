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
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "headers/disk_structs.h"
#include "headers/dir_structs.h"
#include "headers/teste_detect_os.h"
#include "headers/errors_codes.h"
/*
 * 
 */
#define CONST_COMMAND_SIZE 255
#define CONST_FALSE 0

char interpretador2(char linha_commando[], Disk_unit **lista_discos, Disk_unit **disco_atual, Dir_header **diretorio_atual);
//int interpretador(char *comando, Disk_unit *raiz, Disk_unit *diskatual, Dir_header *diratual);
//char SeparadordeComando();

int main(int argc, char** argv) {
    char linha_commando[CONST_COMMAND_SIZE];
    int execute;

    Disk_unit *diskselec;
    Disk_unit *raiz;
    Dir_header *dirselec;
    
    printf("F.I.P.P. DOS");


    do {
        //exibe os atuais
        fippdos_fflush();
        fippdos_fgets(linha_commando);

        //execute = interpretador(linha_commando, raiz, diskselec, dirselec);

    } while (execute > 0);

    return (EXIT_SUCCESS);
};

char interpretador2(char linha_commando[], Disk_unit **lista_discos, Disk_unit **disco_atual, Dir_header **diretorio_atual){

    char l_commando_aux[CONST_COMMAND_SIZE];
    char **parametros;
    char validador = CONST_FALSE;
    
    strncpy(l_commando_aux,linha_commando,CONST_COMMAND_SIZE);
    str_removespaces_from_start(l_commando_aux); //limpa espaços no inicio da string
    parametros = str_split(parametros, ' '); //separa os parametros por espaços
    
    
    return ERROR_UNKNOWN;
};


//char * SeparadordeComando(char *com, int *pos) {
//    int i = 0;
//    //Ignora "espaços" antes do inicio do comando
//    while (com[pos] == ' ')
//        pos++;
//    //localiza comando
//    while (com[pos] != '\0' && com[pos] != ' ') {
//        com[i] = com[pos];
//        i++;
//        pos++;
//    }
//    com[i] = '\0';
//    strcpy(com, strupr(com));
//    return com;
//}

//int interpretador(char* comando, Disk_unit *raiz, Disk_unit *diskatual, Dir_header *diratual) {
//    int posicao = 0, i = 0;
//    char comand[15], endereco[100];
//
//    strcpy(comand,SeparadordeComando(comando,&posicao));
//
//    if (strcmp(comand, "EXIT") == 0) {
//        printf("\n\nEXIT");
//        return 0;
//    } else if (strcmp(comand, "DIR") == 0) {
//        strcpy(endereco,SeparadordeComando(comando,&posicao));
//        command_DIR(endereco, raiz, &(*diskatual), &(*diratual));
//    } else if (strcmp(comand, "CLS") == 0) {
//        command_CLS();
//    } else if (strcmp(comand, "CD") == 0) {
//        strcpy(endereco,SeparadordeComando(comando,&posicao));
//        command_CD(endereco, raiz, &(*diskatual), &(*diratual));
//    } else if (strcmp(comand, "MD") == 0) {
//    } else if (strcmp(comand, "RD") == 0) {
//    } else if (strcmp(comand, "COPY CON") == 0) {
//    } else if (strcmp(comand, "COPY") == 0) {
//    } else if (strcmp(comand, "DEL") == 0) {
//    } else if (strcmp(comand, "TYPE") == 0) {
//    } else if (strcmp(comand, "FIND") == 0) {
//    } else if (strcmp(comand, "FC") == 0) {
//    }
//    return 1;
//}