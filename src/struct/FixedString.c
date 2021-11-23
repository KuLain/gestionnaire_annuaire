//
// Created by julie on 13/11/2021.
//
#include <stdlib.h>
#include <string.h>

#include "../../header/struct/FixedString.h"
/**
 * Initialise FixedString struct
 * @param string : String to put in FixedString
 * @return FixedString : Struct with initialised variables
 */
FSTRING fsinit(const char *string)
{
    int i;
    int n = strlen(string);
    FSTRING tmp;

    tmp.string = malloc(sizeof(char)*(n+1));
    tmp.length = n;


    for (i = 0; i < n; i++)
    {
        tmp.string[i] = string[i];
    }
    tmp.string[n] = '\0';

    return tmp;
}

FSTRING fscat(FSTRING s1, FSTRING s2)
{
    FSTRING tmp;
    int i, j;

    tmp.length = s1.length + s2.length;
    tmp.string = malloc(sizeof(char)*(tmp.length+1));

    for (i = 0; i < s1.length; i++) tmp.string[i] = s1.string[i];
    for (j = 0; j < s2 .length; j++, i++) tmp.string[i] = s2.string[j];

    return tmp;
}

/**
 * Free all dynamic allocation in tmp
 * @param tmp
 */
void fsfree(FSTRING tmp)
{
    free(tmp.string);
}