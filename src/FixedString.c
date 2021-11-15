//
// Created by julie on 13/11/2021.
//
#include <stdlib.h>
#include <string.h>

#include "../header/FixedString.h"
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

/**
 * Free all dynamic allocated variables in tmp
 * @param tmp
 */
void fsfree(FSTRING tmp)
{
    free(tmp.string);
}