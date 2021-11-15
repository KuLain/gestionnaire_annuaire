//
// Created by julie on 13/11/2021.
//
#include <stdlib.h>
#include <string.h>

#include "../header/FixedString.h"

FSTRING fsinit(const char *chaine)
{
    int i;
    int n = strlen(chaine);
    FSTRING tmp;

    tmp.chaine = malloc(sizeof(char)*(n+1));
    tmp.length = n;


    for (i = 0; i < n; i++)
    {
        tmp.chaine[i] = chaine[i];
    }
    tmp.chaine[n] = '\0';

    return tmp;
}

void fsdelete(FSTRING chaine)
{
    free(chaine.chaine);
}