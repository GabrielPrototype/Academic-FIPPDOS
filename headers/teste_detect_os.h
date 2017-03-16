W/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   teste_detect_os.h
 * Author: titan
 *
 * Created on 14 de Março de 2017, 23:39
 */

#ifndef TESTE_DETECT_OS_H
#define TESTE_DETECT_OS_H



#ifdef _WIN64
    //define something for Windows (64-bit only)
void qualosistemapatricia(){
    printf("\n\n\nO sistema é Windows x64, Silvio");
};
#elif _WIN32
    //define something for Windows (32-bit and 64-bit, this part is common)
void qualosistemapatricia(){
    printf("\n\n\nO sistema é Windows, Silvio");
};
 
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
    // iOS Simulator
#elif TARGET_OS_IPHONE
    // iOS device
#elif TARGET_OS_MAC
    // Other kinds of Mac OS
#else
#error "Unknown Apple platform"
#endif
#elif __linux__
    // linux
void qualosistemapatricia(){
    printf("\n\n\nO sistema é linux, Silvio");
}
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#error "Unknown compiler"
#endif

#endif /* TESTE_DETECT_OS_H */

