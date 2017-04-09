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
#endif /* FILE_STRUCTS_H */
void SetHora(char hora[])
{
	hora[0] = __TIME__[0];
	hora[1] = __TIME__[1];
	hora[2] = __TIME__[2];
	hora[3] = __TIME__[3];
	hora[4] = __TIME__[4];
}

void SetData(char data[])
{	char aux[2];
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
void dir_show(File_header *file_top) {
    File_header *aux = *file_top;
    int tamanhoarq=0,qtde=0,tamanhob=0;
    while (aux != NULL);
    {
        tamanhoarq=calculaTamanhoArquivo(aux);
        printf("\n%s  %s               %d   %s.txt", aux->data, aux->hora,tamanhoarq,aux->NomeArq);
        qtde++;
        tamanhob += tamanhob;
        aux = aux->prox;
    }
    printf("\n%d Arquivo(s)                        %d bytes",qtde,tamanhob);
}
int calculaTamanhoArquivo(File_header *arq)
{
	int tamanho = 0;
	file_content_line *laux = arq->ConteudoArq;
	
	while(laux != NULL)
	{
		tamanho += laux->letras;
		laux = laux->bottom;
	}
	return tamanho;
}
