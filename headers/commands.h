/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   comando.h
 * Author: Aleksander
 *
 * Created on 9 de Abril de 2017, 15:44
 */

#ifndef COMMANDS_H
#define COMMANDS_H

#include <stddef.h>
#include <stdlib.h>
#include "disk_structs.h"
#include "dir_structs.h"
#include "file_structs.h"
#include "crossplatform_fuctions.h"

void SetHora(char hora[]) {
    hora[0] = __TIME__[0];
    hora[1] = __TIME__[1];
    hora[2] = __TIME__[2];
    hora[3] = __TIME__[3];
    hora[4] = __TIME__[4];
}

void SetData(char data[]) {
    char aux[2];
    _strdate(data);

    aux[0] = data[0];
    aux[1] = data[1];
    data[0] = data[3];
    data[1] = data[4];
    data[3] = aux[0];
    data[4] = aux[1];

    data[9] = data[7];
    data[8] = data[6];
    data[6] = '2';
    data[7] = '0';

    data[10] = '\0';
}

void exibirL(Disk_unit *Unit, Dir_header *pa) {
    if (pa != Unit->iniDir) {
        exibirL(Unit, pa->PtrPai);
        printf("%s\\", pa->NomeDir);
    } else
        printf("%c\\", Unit->unidade);
}

void Caminho(Disk_unit *Unit, Dir_header *pa) {
    exibirL(Unit, pa);
    printf("> ");
}

void file_show(File_header *file_top) {
    File_header *aux = *file_top;
    int tamanhoarq = 0, qtde = 0, tamanhob = 0;
    while (aux != NULL);
    {
        tamanhoarq = calculaTamanhoArquivo(aux);
        printf("\n%s  %s               %d   %s.txt", aux->data, aux->hora, tamanhoarq, aux->NomeArq);
        qtde++;
        tamanhob += tamanhob;
        aux = aux->prox;
    }
    printf("\n%d Arquivo(s)                        %d bytes", qtde, tamanhob);
}

void dir_show(Dir_header *Dir_top) {
    Dir_header *aux = Dir_top;
    while (aux != NULL);
    {
        printf("\n%s  %s    <DIR>          %s", aux->data, aux->hora, aux->NomeDir);
        aux = aux->Tail;
    }
}

int calculaTamanhoArquivo(File_header *arq) {
    int tamanho = 0;
    file_content_line *laux;
    laux = arq->ConteudoArq;
    while (laux != NULL) {
        tamanho += laux->letras;
        laux = laux->bottom;
    }
    return tamanho;
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

void command_DIR(char endereco[], Disk_unit *raiz, Disk_unit **unidadeSelec, Dir_header **pastaSelec) {
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
            pAUX = separaeprocuraPasta(endereco, pAUX);
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
        pAUX = separaeprocuraPasta(endereco, pAUX);
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

void command_CLS() {
    clear_screen_cplat();
}

void command_CD(char endereco[], Disk_unit *raiz, Disk_unit **unidadeSelec, Dir_header **pastaSelec) {
    Disk_unit *uAUX = NULL;
    Dir_header *pAUX = NULL;
    if (endereco[0] == '\0') {
        //CD VAZIO
        Caminho(*unidadeSelec, *pastaSelec);
    } else if (endereco[0] == '.' && endereco[1] == '.') {
        //CD .. - retorna a pasta pai se houver.
        if (endereco[2] == '\0') {
            if ((*pastaSelec)->PtrPai != NULL) {
                *pastaSelec = (*pastaSelec)->PtrPai;
            }
        } else
            printf("O sistema nao encontra o caminho especificado.");
    } else if (endereco[1] == ':' && endereco[2] == '\\') { // cd muda os ponteiros se possivel

        uAUX = diskunit_find(*raiz, endereco[0]);
        if (uAUX == NULL) {
            printf("O sistema nao pode encontrar o caminho especificado.");
        } else {
            pAUX = uAUX->iniDir->Head;
            pAUX = separaeprocuraPasta(endereco, pAUX);
            if (pAUX == NULL) {
                printf("\nErro, pasta nao encontrada.");
            } else {
                *unidadeSelec = uAUX;
                *pastaSelec = pAUX;
            }
        }
    } else {
        pAUX = (*pastaSelec)->Head;
        pAUX = separaeprocuraPasta(endereco, pAUX);
        if (pAUX == NULL) {
            printf("\nErro, pasta nao encontrada.");
        } else {
            *pastaSelec = pAUX;
        }
    }
    printf("\n\n");
}

void command_MD(char endereco[], Disk_unit *raiz, Disk_unit **unidadeSelec, Dir_header **pastaSelec) {
    Disk_unit *uAUX = NULL;
    Dir_header *pAUX = NULL;
    if (endereco[0] == '\0') { //MD vazio 
        printf("A sintaxe do comando esta incorreta.");
    } else if (endereco[1] == ':' && endereco[2] == '\\') {
        uAUX = diskunit_find(raiz, endereco[0]);
        if (uAUX == NULL) {
            printf("O sistema nao pode encontrar o caminho especificado.");
        }
        else
        {
            //procura pasta
            
        }
    }
}
#endif /* COMMANDS_H */

