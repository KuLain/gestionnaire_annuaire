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
        tmp->data[i] = realloc(data[i], strlen(data[i])+1);
    }
    return tmp;
}

void rdisplay(RECORD *r)
{
    int i;
    printf("%s `| ", r->data[0]);
    for (i = 1; i < 6; i++) {
        printf("%s `| ", r->data[i]);
    }
    printf("%s", r->data[6]);
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