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
#include "headers/commands.h"
/*
 * 
 */
int interpretador(char comando[], Disk_unit *raiz, Disk_unit *diskatual, Dir_header *diratual);

int main(int argc, char** argv) {
    char linhac[255];
    int execute;

    Disk_unit *diskselec;
    Disk_unit *raiz;
    Dir_header *dirselec;

    printf("F.I.P.P. DOS");


    do {
        //exibe os atuais
        fflush(stdin);
        gets(linhac);

        execute = interpretador(char linhac[], Disk_unit *raiz, Disk_unit *diskselec, Dir_header * dirselec);

    } while (execute > 0);

    return (EXIT_SUCCESS);
}

char SeparadordeComando(char *com[], int *pos) {
    int i = 0;
    //Ignora "espaços" antes do inicio do comando
    while (com[pos] == ' ')
        pos++;
    //localiza comando
    while (com[pos] != '\0' && com[pos] != ' ') {
        com[i] = com[pos];
        i++;
        pos++;
    }
    com[i] = '\0';
    strcpy(com, strupr(com));
    return com;
}

Dir_header separaeprocuraPasta(char *com[], Dir_header *pasta) {
    char nomep[30];
    int i = 3, pos = 0;
    Dir_header *p = NULL;

    while (com[i] != '\0' && pasta != NULL) {
        if (com[i] != '\\') {
            nomep[pos] = com[i];
            pos++;
        }
        if (com[i] == '\\' || com[i + 1] == '\0') {
            nomep[pos] = '\0';

            p = dir_find_dir(pasta, nomep[]);

            //desce para uma subpasta se houver
            if (p != NULL && com[i] == '\\' && com[i + 1] != '\0' && com[i + 1] != ' ') {
                p = p->Head;
            }
            pos = 0;
        }
        i++;
    }
    return p;
}

int interpretador(char comando[], Disk_unit *raiz, Disk_unit *diskatual, Dir_header *diratual) {
    int posicao = 0, i = 0;
    char comando[15], endereco[100];

    comando = SeparadordeComando(&comando[],&posicao[]);

    if (strcmp(comando, "EXIT") == 0) {
        printf("\n\nEXIT");
        return 0;
    } else if (strcmp(comando, "DIR") == 0) {
        endereco = SeparadordeComando(&endereco[],&posicao[]);
        command_DIR(endereco, raiz, &(*diskatual), &(*diratual));
    } else if (strcmp(comando, "CLS") == 0) {
        command_CLS();
    } else if (strcmp(comando, "CD") == 0) {
        endereco = SeparadordeComando(&endereco[],&posicao[]);
        command_CD(endereco, raiz, &(*diskatual), &(*diratual));
    } else if (strcmp(comando, "MD") == 0) {
    } else if (strcmp(comando, "RD") == 0) {
    } else if (strcmp(comando, "COPY CON") == 0) {
    } else if (strcmp(comando, "COPY") == 0) {
    } else if (strcmp(comando, "DEL") == 0) {
    } else if (strcmp(comando, "TYPE") == 0) {
    } else if (strcmp(comando, "FIND") == 0) {
    } else if (strcmp(comando, "FC") == 0) {
    }
    return 1;
}