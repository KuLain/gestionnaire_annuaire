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
        printf("%-25s%-30s%-25s%-15s%-20s%-50s%-20s\n", r->data[0], r->data[1], r->data[2], r->data[3], r->data[4], r->data[5], r->data[6]);
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

