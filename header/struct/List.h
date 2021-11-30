//
// Created by lain on 30/11/2021.
//

#ifndef SAE1_2_LINUX_LIST_H
#define SAE1_2_LINUX_LIST_H
#include "Record.h"
typedef struct List {
    RECORD **content;
    int length;
} LIST ;

LIST* linit();
void lpush(LIST*, RECORD*);
void lpop(LIST*);
void lpop_i(LIST*, int);
void lpop_i_resize(LIST*, int);
void lfree(LIST*);

#endif //SAE1_2_LINUX_LIST_H
