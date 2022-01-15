//
// Created by lain on 30/11/2021.
//
#include "../../header/struct/Record.h"
#include <stdlib.h>
#include <string.h>

#define N 7

/**
 * Initialise les variables et alloue la mémoire du RECORD
 * @param tab : Tableau contenant des pointeurs des vers chaines de caractères allouées dynamiquement
 * @return : Pointeur vers le RECORD
 */
RECORD* rinit(char **tab)
{
    RECORD* tmp = malloc(sizeof(RECORD));
    tmp->data = (char**) malloc(sizeof(char*)*N);
    int i, j, n;
    for (i = 0; i < N; i++)
    {
        n = strlen(tab[i]);
        tmp->data[i] = malloc(sizeof(char)*(n+1));
        for (j = 0; j <= n; j++) tmp->data[i][j] = tab[i][j];
    }
    return tmp;
}

RECORD* r_copy(RECORD *r) {
    RECORD *tmp = malloc(sizeof(RECORD));
    tmp->data = (char**) malloc(sizeof(char*)*N);

    int i, j, n;
    for (i = 0; i < N; i++)
    {
        n = strlen(r->data[i]);
        tmp->data[i] = malloc(sizeof(char)*(n+1));
        for (j = 0; j <= n; j++) tmp->data[i][j] = r->data[i][j];
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
        printf("%-25s%-30s%-25s%-15s%-20s%-50s%-30s\n", r->data[0], r->data[1], r->data[2], r->data[3], r->data[4], r->data[5], r->data[6]);
        // printf("%s %s %s %s %s %s %s\n", r->data[0], r->data[1], r->data[2], r->data[3], r->data[4], r->data[5], r->data[6]);
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

