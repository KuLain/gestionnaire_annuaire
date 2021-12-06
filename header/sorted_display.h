//
// Created by julie on 28/11/2021.
//

#ifndef SAE_1_2_SORTED_DISPLAY_H
#define SAE_1_2_SORTED_DISPLAY_H
#include "struct/Record.h"
#include "struct/AssociativeArray.h"
void sorted_records(AARRAY *array);
void aarray_list(AARRAY*, LIST*);
void quick_sort(LIST*, int);
void merge_sort(LIST*, int);
void display_sorted_records(LIST*);
#endif //SAE_1_2_SORTED_DISPLAY_H
