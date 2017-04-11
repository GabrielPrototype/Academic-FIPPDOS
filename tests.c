/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tests.c
 * Author: titan
 *
 * Created on 10 de Abril de 2017, 21:18
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int test_split()
{
    char months[] = "JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC";
    char** tokens;

    printf("months=[%s]\n\n", months);

    tokens = str_split(months, ',');

    if (tokens)
    {
        int i;
        for (i = 0; *(tokens + i); i++)
        {
            printf("month=[%s]\n", *(tokens + i));
            //free(*(tokens + i));
        }
        printf("\n");
        free(tokens);
    }

    return 0;
}
