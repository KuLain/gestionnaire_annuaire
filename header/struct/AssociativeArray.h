//
// Created by lain on 30/11/2021.
//

#ifndef SAE1_2_LINUX_ASSOCIATIVEARRAY_H
#define SAE1_2_LINUX_ASSOCIATIVEARRAY_H

#include "List.h"
typedef struct AssociativeArray {
    LIST **content;
    int size;
    int length;
} AARRAY;

AARRAY* aainit(int);
int hash(char*, char*, int);
void aapush(AARRAY* array, char prenom[], char nom[], RECORD* elt);
RECORD* aavalue_mail(AARRAY* array, char prenom[], char nom[], char mail[]);
RECORD* aavalue_phone(AARRAY* array, char prenom[], char nom[], char phone[]);
void aapop(AARRAY* array, char prenom[], char nom[], char mail[], char telephone[]);
void aapop_resize(AARRAY* array, char prenom[], char nom[], char mail[], char telephone[]);
void aadisplay(AARRAY* array);
void aafree(AARRAY*);


#endif //SAE1_2_LINUX_ASSOCIATIVEARRAY_H
