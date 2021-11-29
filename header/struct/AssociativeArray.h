//
// Created by julie on 23/11/2021.
//

#ifndef SAE_1_2_ASSOCIATIVEARRAY_H
#define SAE_1_2_ASSOCIATIVEARRAY_H

#include "List.h"
typedef struct AssociativeArray {
    LIST **content;
    int size;
    int length;
} AARRAY;

AARRAY* aainit(int);
void aapush(AARRAY* array, char prenom[], char nom[], RECORD* elt);
RECORD* aavalue_mail(AARRAY* array, char prenom[], char nom[], char mail[]);
RECORD* aavalue_phone(AARRAY* array, char prenom[], char nom[], char phone[]);
void aapop(AARRAY* array, char prenom[], char nom[], char mail[], char telephone[]);
void aapop_resize(AARRAY* array, char prenom[], char nom[], char mail[], char telephone[]);
void aadisplay(AARRAY* array);
void aafree(AARRAY*);

#endif //SAE_1_2_ASSOCIATIVEARRAY_H
