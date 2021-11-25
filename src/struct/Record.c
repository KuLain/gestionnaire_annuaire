//
// Created by julie on 13/11/2021.
//

#include "../../header/struct/Record.h"
#include <stdlib.h>

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
    // TODO
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