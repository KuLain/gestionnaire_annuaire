//
// Created by julie on 13/11/2021.
//

#ifndef SAE1_2_RECORD_H
#define SAE1_2_RECORD_H

#include "FixedString.h"
#include <stdio.h>

typedef struct Record {
    FSTRING *content;
} RECORD;

RECORD* rinit(char **infos);
void rdisplay(RECORD *r);
void rfree(RECORD *r);

#endif //SAE1_2_RECORD_H
