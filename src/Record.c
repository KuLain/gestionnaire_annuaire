//
// Created by julie on 13/11/2021.
//

#include "../header/Record.h"
#include <stdlib.h>

#define N 7

/**
 * Initialise all variable of a RECORD
 * @param infos : Array of 7 strings matching [name, surname, city, postal code, phone, mail, job]
 * @return : pointer to the created RECORD with an array of 7 initialised FSTRING
 */
RECORD* rinit(char **infos)
{
    RECORD* tmp = malloc(sizeof(RECORD));
    int i;

    tmp->content = malloc(sizeof(FSTRING)*N);
    for (i = 0; i < N; i++)
    {
        tmp->content[i] = fsinit(infos[i]);
    }
    return tmp;
}

/**
 * Display 7 strings of the RECORD
 * @param r : pointer to RECORD
 */
void rdisplay(RECORD *r)
{
    int i;
    printf("%s\t", r->content[0].string);
    for (i = 1; i < N-1; i++)
    {
        printf("%s\t", r->content[i].string);
    }
    printf("%s", r->content[N-1].string);
}

/**
 * Free all dynamic allocation of the RECORD and inside the RECORD
 * @param r : Pointer to RECORD
 */
void rfree(RECORD *r)
{
    int i;
    for (i = 0; i < N-1; i++)
    {
        fsfree(r->content[i]);
    }
    free(r->content);
    free(r);
}