//
// Created by julie on 13/11/2021.
//

#ifndef SAE1_2_RECORD_H
#define SAE1_2_RECORD_H

#include <stdio.h>

typedef struct Record {
    fpos_t start;
    char *mail;
    char *phone;
} RECORD;

RECORD* rinit(fpos_t beginning, char mail[], char telephone[]);
void rdisplay(FILE *fp, RECORD *r);
void rfree(RECORD *r);

#endif //SAE1_2_RECORD_H
