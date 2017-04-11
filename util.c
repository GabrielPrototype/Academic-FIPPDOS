/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   util.c
 * Author: titan
 *
 * Created on 10 de Abril de 2017, 21:08
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "headers/constants.h"
/*
 * 
 */
void str_toupper(char s[]) {
    int i;
    for(i = 0; i < CONST_COMMAND_SIZE && s[i] != '\0'; i++){
        
        s[i] = toupper(s[i]);
    }
}

void str_removespaces_from_start(char str[]) {

    char *aux;
    int j, i = 0;

    for (i = 0; str[0] == ' ' && str[0] != '\0'; i++) {

        for (j = i; str[j] != '\0'; j++) {
            str[j] = str[j + 1];
        }
    }
};

char** str_split(char* a_str, const char a_delim) {
    char** result = 0;
    size_t count = 0;
    char* tmp = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp) {
        if (a_delim == *tmp) {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof (char*) * count);

    if (result) {
        size_t idx = 0;
        char* token = strtok(a_str, delim);

        while (token) {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}




