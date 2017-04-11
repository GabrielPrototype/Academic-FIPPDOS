/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>


/* 
 * File:   teste_detect_os.h
 * Author: titan
 *
 * Created on 14 de Março de 2017, 23:39
 */

//#ifndef TESTE_DETECT_OS_H
//#define TESTE_DETECT_OS_H



#ifdef _WIN64
    //define something for Windows (64-bit only)
void clear_screen_cplat(){
    system("cls");
    printf("\n");
};

char fippdos_fflush(){
    fflush(stdin)
};
#elif _WIN32
    //define something for Windows (32-bit and 64-bit, this part is common)
void clear_screen_cplat(){
    system("cls");
    printf("\n");
};

char fippdos_fflush(){
    fflush(stdin);
};

#elif __linux__
    // linux

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
};

void clear_screen_cplat(){
    system("clear");
    printf("\n");
};

char fippdos_fflush(){
    clean_stdin();
};
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#error "Unknown compiler"
#endif

//#endif /* TESTE_DETECT_OS_H */

