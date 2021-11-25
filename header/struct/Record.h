//
// Created by julie on 13/11/2021.
//

#ifndef SAE1_2_RECORD_H
#define SAE1_2_RECORD_H

#include <stdio.h>

typedef struct Record {
    char **data;
} RECORD;

RECORD* rinit(char **data);
void rdisplay(RECORD *r);
void rfree(RECORD *r);

#endif //SAE1_2_RECORD_H
