//
// Created by lain on 30/11/2021.
//
#include "../../header/struct/Record.h"
#include <stdlib.h>
#include <string.h>

#define N 7

/**
 * Initialise les variables et alloue la mémoire du RECORD
 * @param data : Tableau contenant des pointeurs des vers chaines de caractères allouées dynamiquement
 * @return : Pointeur vers le RECORD
 */
RECORD* rinit(char **data)
{
    RECORD* tmp = malloc(sizeof(RECORD));
    tmp->data = (char**) malloc(sizeof(char*)*N);
    int i;
    for (i = 0; i < N; i++)
    {
        tmp->data[i] = data[i];
    }
    return tmp;
}

/**
 * Affiche le RECORD
 * @param r : Pointeur vers le RECORD
 */
void rdisplay(RECORD *r)
{
    if (r != NULL) {
        int i;
        printf("%s %s\n", r->data[0], r->data[1]);
        for (i = 2; i < 6; i++) {
            printf("\t| %s\n", r->data[i]);
        }
        printf("\t| %s", r->data[6]);
    } else {
        printf("");
    }
}

/**
 * Libère toutes les allocations dynamiques du RECORD
 * @param r : Pointeur vers le RECORD
 */
void rfree(RECORD *r)
{
    int i;
    for (i = 0; i < N; i++)
    {
        free(r->data[i]);
        r->data[i] = NULL;
    }
    free(r->data);
    r->data = NULL;
    free(r);
    r = NULL;
}

