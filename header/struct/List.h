//
// Created by julie on 13/11/2021.
//

#ifndef SAE1_2_LIST_H
#define SAE1_2_LIST_H
#include "Record.h"
typedef struct List {
    void **content;
    int length;
} LIST ;

LIST* linit();
void lpush(LIST*, void*);
void lpop(LIST*);
void lpop_i(LIST*, int);
void lpop_i_record(LIST*, int);
void l_pop_i_resize(LIST*, int);
void lfree(LIST*);
void lfree_record(LIST*);
#endif //SAE1_2_LIST_H
