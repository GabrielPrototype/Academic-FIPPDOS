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

#include "headers/disk_structs.h"
#include "headers/dir_structs.h"
#include "headers/teste_detect_os.h"

/*
 * 
 */
int interpretador(char comando[], Disk_unit *raiz, Disk_unit *diskatual, Dir_header *diratual);

int main(int argc, char** argv) {
    char linhac[255];
    int execute;
    time_t t = time(NULL);
    struct tm *tempo = localtime(&t);
    struct tm tempo2 = *tempo;
    Disk_unit *diskselec;
    Disk_unit *raiz;
    Dir_header *dirselec;

    printf("F.I.P.P. DOS");




    printf("\nnow: %d-%d-%d %d:%d:%d\n", tempo2.tm_year + 1900, tempo2.tm_mon + 1, tempo2.tm_mday, tempo2.tm_hour, tempo2.tm_min, tempo2.tm_sec);

//    //printf("\n\nMah oi, qual o sistema patricia?\n");
//    //qualosistemapatricia();
//    //diskunit_test();
//    printf("\n");
//    char info = 'a';
//    char *L1;
//    char *L2;
//
//    L2 = NULL;
//
//    if (!((L1 == NULL) && (L2 == NULL))) {
//        printf("Diferentes");
//    }
//    getchar();
//    return (EXIT_SUCCESS);
    do {
        //exibe os atuais
        fflush(stdin);
        gets(linhac);

        execute = interpretador(char linhac[], Disk_unit *raiz, Disk_unit *diskselec, Dir_header * dirselec);

    } while (execute > 0);

}


//função para teste da funções relacionadas a unidade de disco

void diskunit_test(void) {

    Disk_unit *ldisk = NULL, *aux = NULL, *aux2 = NULL;
    for (char letra = 'A'; letra <= 'Z'; letra++) {
        diskunit_init(&aux, (char) letra);
        diskunit_insert(&ldisk, &aux);
    }

    printf("\n\n");

    for (aux = ldisk; aux != NULL; aux2 = aux, aux = aux->bottom) {
        printf("unidade %c:\n", aux->unidade);
    }

    printf("\n");

    for (aux2; aux2 != NULL; aux2 = aux2->top) {
        printf("unidade %c:\n", aux2->unidade);
    }

    printf("\n");
    printf("Procurando a unidade A: \n");
    aux = diskunit_find(ldisk, 'A');
    printf("Unidade encontrada = %c:\n", aux->unidade);
    printf("Deletando a Unidade A:");
    diskunit_delete(&ldisk, &aux);

    printf("\n\n");

    for (aux = ldisk; aux != NULL; aux2 = aux, aux = aux->bottom) {
        printf("unidade %c:\n", aux->unidade);
    }

    printf("\n");
    aux = NULL;
    diskunit_init(&aux, (char) 'A');
    diskunit_insert(&ldisk, &aux);

    printf("\n");

    for (aux = ldisk; aux != NULL; aux2 = aux, aux = aux->bottom) {
        printf("unidade %c:\n", aux->unidade);
    }

    printf("\n");
    printf("Deletando toda a lista \n");
    diskunit_delete_all(&ldisk);

    if (!ldisk)
        printf("Lista vazia\n");

    for (aux = ldisk; aux != NULL; aux2 = aux, aux = aux->bottom) {
        printf("unidade %c:\n", aux->unidade);
    }

    printf("\n\nInserindo de forma reversa e ordenando automaticamente");
    for (char letra = 'Z'; letra >= 'A'; letra--) {
        diskunit_init(&aux, (char) letra);
        diskunit_insert(&ldisk, &aux);
    }

    printf("\n\n");

    for (aux = ldisk; aux != NULL; aux2 = aux, aux = aux->bottom) {
        printf("unidade %c:\n", aux->unidade);
    }

    printf("\n");
    printf("Deletando toda a de forma reversa \n");
    diskunit_delete_all_reverse(&ldisk);

    if (!ldisk)
        printf("Lista vazia\n");

};

//função para teste da funções relacionadas a diretorios

void dir_test(void) {

    Dir_header *test_C, *aux, *aux2;


    dir_insert_diretorio(&test_C, aux);

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

void DIR(char endereco[], Disk_unit *raiz, Disk_unit **unidadeSelec, Dir_header **pastaSelec) {
    Disk_unit *uAUX = NULL;
    Dir_header *pAUX = NULL, *pAUX2;
    File_header *aAUX = NULL;

    char data[9], hora[5];
    SetData(data);
    SetHora(hora);
    if (endereco[0] == '\0') { //DIR VAZIO - exibe diretorio atual, subpasta(s) e arquivo(s)
        pAUX = (*pastaSelec)->Head;

        printf("\n%s  %s    <DIR>          .", data, hora);
        printf("\n%s  %s    <DIR>          ..", data, hora);
        dir_show(pAUX);
        if ((*pastaSelec)->ListaArq != NULL)//pasta possui arquivos
        {
            aAUX = (*pastaSelec)->ListaArq;
            dir_show(aAUX);
        }
    } else if (endereco[1] == ':' && endereco[2] == '\\') { //DIR - procura o disco, depois procura o diretorio, exibe
        uAUX = diskunit_find(unidadeSelec, endereco[0]);
        if (uAUX != NULL) {
            pAUX = uAUX->iniDir->Head;
            pAUX = separaeprocuraPasta(endereco[], pAUX);
            if (pAUX == NULL) {
                printf("\nErro, pasta nao encontrada.");
            } else {
                pAUX2 = pAUX->Head;
                printf("\n%s  %s    <DIR>          .", data, hora);
                printf("\n%s  %s    <DIR>          ..", data, hora);
                dir_show(pAUX2);
                if (pAUX->ListaArq != NULL) {
                    aAUX = pAUX->ListaArq;
                    file_show(aAUX);
                }
            }
        } else {
            printf("\nErro, unidade nao encontrada.");
        }

    } else {//DIR  - procura uma sub pasta partindo da pasta atual e exibe seu conteudo
        pAUX = (*pastaSelec)->Head;
        pAUX = separaeprocuraPasta(endereco[], pAUX);
        if (pAUX == NULL) {
            printf("\nErro, pasta nao encontrada.");
        } else {
            pAUX2 = pAUX->Head;
            printf("\n%s  %s    <DIR>          .", data, hora);
            printf("\n%s  %s    <DIR>          ..", data, hora);
            dir_show(pAUX2);
            if (pAUX->ListaArq != NULL) {
                aAUX = pAUX->ListaArq;
                file_show(aAUX);
            }
        }
    }
}

int interpretador(char comando[], Disk_unit *raiz, Disk_unit *diskatual, Dir_header *diratual) {
    int posicao = 0, i = 0;
    char comando[15], endereco[100];

    comando = SeparadordeComando(char &comando[], int &posicao);

    if (strcmp(comando, "EXIT") == 0) {
        printf("\n\nEXIT");
        return 0;
    } else if (strcmp(comando, "DIR") == 0) {
        endereco = SeparadordeComando(char &endereco[], int &posicao);
        DIR(endereco, raiz, &(*diskatual), &(*diratual));
    } else if (strcmp(comando, "CLS") == 0) {
        system("cls");
        printf("\n");
    } else if (strcmp(comando, "CD") == 0) {
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