/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   commands.c
 * Author: titan
 *
 * Created on 10 de Abril de 2017, 19:53
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "headers/disk_structs.h"
#include "headers/dir_structs.h"
#include "headers/file_structs.h"
#include "headers/crossplatform_fuctions.h"

/*
 * 
 */

int calculaTamanhoArquivo(File_header *arq);

void SetHora(char hora[]) {
    hora[0] = __TIME__[0];
    hora[1] = __TIME__[1];
    hora[2] = __TIME__[2];
    hora[3] = __TIME__[3];
    hora[4] = __TIME__[4];
}

void SetData(char data[]) {
    //    char aux[2];
    //    _strdate(data);
    //
    //    aux[0] = data[0];
    //    aux[1] = data[1];
    //    data[0] = data[3];
    //    data[1] = data[4];
    //    data[3] = aux[0];
    //    data[4] = aux[1];
    //
    //    data[9] = data[7];
    //    data[8] = data[6];
    //    data[6] = '2';
    //    data[7] = '0';
    //
    //    data[10] = '\0';
}

void print_dir_url(Dir_header *diretorio) {

    print_dir_url(diretorio->PtrPai);
    if (diretorio) {
        printf("\\%s", diretorio->NomeDir);
    }
};

void print_prompt(Disk_unit *unidade_atual, Dir_header *diretorio_atual) {

    printf("\n");
    if (unidade_atual) {
        printf("%c:", unidade_atual->unidade);

        if (diretorio_atual) {
            print_dir_url(diretorio_atual);
        } else {
            printf("\\");
        }

        printf(">");
    }
};

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
    File_header *aux = file_top;
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

void dir_show(Dir_header *dir) {

    while (dir != NULL);
    {
        printf("\n%s  %s    <DIR>          %s", dir->data, dir->hora, dir->NomeDir);
        dir = dir->Tail;
    }
}

int calculaTamanhoArquivo(File_header *arq) {
    int tamanho = 0;
    File_content_line *laux;
    laux = arq->ConteudoArq;
    while (laux != NULL) {
        tamanho += laux->letras;
        laux = laux->bottom;
    }
    return tamanho;
}

void command_MD(Disk_unit **unidade_dest, Dir_header **dir_dest, char nome[]) {

    char data[11];
    char hora[6];
    Dir_header *dir_novo;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(hora, "%d:%d", tm.tm_hour, tm.tm_min);
    sprintf(data, "%d/%d/%d", 1900 + tm.tm_year, tm.tm_mon, tm.tm_mday);
    dir_init_header(&dir_novo, nome, data, hora);

    if (*dir_dest) {
        dir_insert_diretorio(&(*dir_dest), &dir_novo);
    } else if (*unidade_dest) {
        dir_insert_diretorio(&(*unidade_dest)->iniDir, &dir_novo);
    }

}

void command_DIR(Disk_unit *unidade, Dir_header *dir){

    Dir_header *aux;
    char flag = CONST_FALSE;
    if(dir){
        aux = dir;
        flag = !flag;
    }else if (unidade){
        aux = unidade->iniDir->Head;
        flag = !flag;
    }
    if(flag){
        dir_show(aux);
    }
    
}

//char SeparadordeComando(char commando[], int *pos) {
//    int i = 0;
//    //Ignora "espaços" antes do inicio do comando
//    while (commando[pos] == ' ')
//        pos++;
//    //localiza comando
//    while (commando[pos] != '\0' && commando[pos] != ' ') {
//        commando[i] = commando[pos];
//        i++;
//        pos++;
//    }
//    commando[i] = '\0';
//    strcpy(commando, strupr(commando));
//    return commando;
//}

//Dir_header *separaeprocuraPasta(char *com, Dir_header *pasta) {
//    char nomep[30];
//    int i = 3, pos = 0;
//    Dir_header *p = NULL;
//
//    while (com[i] != '\0' && pasta != NULL) {
//        if (com[i] != '\\') {
//            nomep[pos] = com[i];
//            pos++;
//        }
//        if (com[i] == '\\' || com[i + 1] == '\0') {
//            nomep[pos] = '\0';
//
//            p = dir_find_dir(pasta, nomep);
//
//            //desce para uma subpasta se houver
//            if (p != NULL && com[i] == '\\' && com[i + 1] != '\0' && com[i + 1] != ' ') {
//                p = p->Head;
//            }
//            pos = 0;
//        }
//        i++;
//    }
//    return p;
//}

//void command_DIR_old(Disk_unit *raiz, Disk_unit **unidadeSelec, Dir_header **pastaSelec, Dir_header **parametro) {
//    Disk_unit *uAUX = NULL;
//    Dir_header *pAUX = NULL, *pAUX2;
//    File_header *aAUX = NULL;
//
//    char data[9], hora[5];
//    SetData(data);
//    SetHora(hora);
//    if (endereco[0] == '\0') { //DIR VAZIO - exibe diretorio atual, subpasta(s) e arquivo(s)
//        pAUX = (*pastaSelec)->Head;
//
//        printf("\n%s  %s    <DIR>          .", data, hora);
//        printf("\n%s  %s    <DIR>          ..", data, hora);
//        dir_show(pAUX);
//        if ((*pastaSelec)->ListaArq != NULL)//pasta possui arquivos
//        {
//            aAUX = (*pastaSelec)->ListaArq;
//            file_show(aAUX);
//        }
//    } else if (endereco[1] == ':' && endereco[2] == '\\') { //DIR - procura o disco, depois procura o diretorio, exibe
//        uAUX = diskunit_find(unidadeSelec, endereco[0]);
//        if (uAUX != NULL) {
//            pAUX = uAUX->iniDir->Head;
//            pAUX = separaeprocuraPasta(endereco, pAUX);
//            if (pAUX == NULL) {
//                printf("\nErro, pasta nao encontrada.");
//            } else {
//                pAUX2 = pAUX->Head;
//                printf("\n%s  %s    <DIR>          .", data, hora);
//                printf("\n%s  %s    <DIR>          ..", data, hora);
//                dir_show(pAUX2);
//                if (pAUX->ListaArq != NULL) {
//                    aAUX = pAUX->ListaArq;
//                    file_show(aAUX);
//                }
//            }
//        } else {
//            printf("\nErro, unidade nao encontrada.");
//        }
//
//    } else {//DIR  - procura uma sub pasta partindo da pasta atual e exibe seu conteudo
//        pAUX = (*pastaSelec)->Head;
//        pAUX = separaeprocuraPasta(endereco, pAUX);
//        if (pAUX == NULL) {
//            printf("\nErro, pasta nao encontrada.");
//        } else {
//            pAUX2 = pAUX->Head;
//            printf("\n%s  %s    <DIR>          .", data, hora);
//            printf("\n%s  %s    <DIR>          ..", data, hora);
//            dir_show(pAUX2);
//            if (pAUX->ListaArq != NULL) {
//                aAUX = pAUX->ListaArq;
//                file_show(aAUX);
//            }
//        }
//    }
//}

void command_CLS(Disk_unit *unidade) {
    clear_screen_cplat();
    printf("\nFIPPDOS %c :>", unidade->unidade);
}

//void command_CD(char endereco[], Disk_unit *raiz, Disk_unit **unidadeSelec, Dir_header **pastaSelec) {
//    Disk_unit *uAUX = NULL;
//    Dir_header *pAUX = NULL;
//    if (endereco[0] == '\0') {
//        //CD VAZIO
//        Caminho(*unidadeSelec, *pastaSelec);
//    } else if (endereco[0] == '.' && endereco[1] == '.') {
//        //CD .. - retorna a pasta pai se houver.
//        if (endereco[2] == '\0') {
//            if ((*pastaSelec)->PtrPai != NULL) {
//                *pastaSelec = (*pastaSelec)->PtrPai;
//            }
//        } else
//            printf("O sistema nao encontra o caminho especificado.");
//    } else if (endereco[1] == ':' && endereco[2] == '\\') { // cd muda os ponteiros se possivel
//
//        uAUX = diskunit_find(raiz, endereco[0]);
//        if (uAUX == NULL) {
//            printf("O sistema nao pode encontrar o caminho especificado.");
//        } else {
//            pAUX = uAUX->iniDir->Head;
//            pAUX = separaeprocuraPasta(endereco, pAUX);
//            if (pAUX == NULL) {
//                printf("\nErro, pasta nao encontrada.");
//            } else {
//                *unidadeSelec = uAUX;
//                *pastaSelec = pAUX;
//            }
//        }
//    } else {
//        pAUX = (*pastaSelec)->Head;
//        pAUX = separaeprocuraPasta(endereco, pAUX);
//        if (pAUX == NULL) {
//            printf("\nErro, pasta nao encontrada.");
//        } else {
//            *pastaSelec = pAUX;
//        }
//    }
//    printf("\n\n");
//}

//void command_MD_old(char endereco[], Disk_unit *raiz, Disk_unit **unidadeSelec, Dir_header **pastaSelec) {
//    Disk_unit *uAUX = NULL;
//    Dir_header *pAUX = NULL;
//    if (endereco[0] == '\0') { //MD vazio 
//        printf("A sintaxe do comando esta incorreta.");
//    } else if (endereco[1] == ':' && endereco[2] == '\\') {
//        uAUX = diskunit_find(raiz, endereco[0]);
//        if (uAUX == NULL) {
//            printf("O sistema nao pode encontrar o caminho especificado.");
//        } else {
//            //procura pasta
//
//        }
//    }
//}
