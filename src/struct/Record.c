//
// Created by julie on 13/11/2021.
//

#include "../../header/struct/Record.h"
#include <stdlib.h>
#include <string.h>

#define N 7

RECORD* rinit(char **data)
{
    RECORD* tmp = malloc(sizeof(RECORD));
    tmp->data = malloc(sizeof(char*)*N);
    int i;
    for (i = 0; i < N; i++)
    {
        tmp->data[i] = data[i];
    }
    return tmp;
}

void rdisplay(RECORD *r)
{
    int i;
    printf("%s %s\n", r->data[0], r->data[1]);
    for (i = 2; i < 6; i++) {
        printf("\t| %s\n", r->data[i]);
    }
    printf("\t| %s", r->data[6]);
}

/**
 * Free all dynamic allocation of the RECORD and inside the RECORD
 * @param r : Pointer to RECORD
 */
void rfree(RECORD *r)
{
    int i;
    for (i = 0; i < N; i++)
    {
        free(r->data[i]);
    }
    free(r);
}