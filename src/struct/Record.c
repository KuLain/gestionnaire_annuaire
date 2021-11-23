//
// Created by julie on 13/11/2021.
//

#include "../../header/struct/Record.h"
#include <stdlib.h>

#define N 7

RECORD* rinit(fpos_t beginning, FSTRING mail, FSTRING telephone)
{
    RECORD* tmp = malloc(sizeof(RECORD));
    tmp->start = beginning;
    tmp->mail = mail;
    tmp->phone = telephone;
    return tmp;
}

void rdisplay(FILE *fp,RECORD *r)
{
    char buffer[N][50];
    fsetpos(fp, &r->start);
    fscanf(fp, "%s;%s;%s;%s;%s;%s;%s", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5],buffer[6]);
    printf("Prenom : %s\n", buffer[0]);
    printf("Nom : %s\n", buffer[1]);
    printf("Mail : %s\n", r->mail);
    printf("Téléphone : %s", r->phone);
}

/**
 * Free all dynamic allocation of the RECORD and inside the RECORD
 * @param r : Pointer to RECORD
 */
void rfree(RECORD *r)
{
    fsfree(r->phone);
    fsfree(r->mail);
    free(r);
}