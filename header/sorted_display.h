//
// Created by julie on 28/11/2021.
//

#ifndef SAE_1_2_SORTED_DISPLAY_H
#define SAE_1_2_SORTED_DISPLAY_H
#include "struct/Record.h"
#include "struct/AssociativeArray.h"
void sorted_records(AARRAY *array);
void aarray_list(AARRAY*, LIST*, int);
void bubble_sort(AARRAY*, int filter);
void quick_sort(AARRAY*, int filter);
void display_sorted_records(LIST *liste);
#endif //SAE_1_2_SORTED_DISPLAY_H
