//
// Created by lain on 30/11/2021.
//

#include "../header/empty_display.h"
#include "../header/struct/AssociativeArray.h"
#include "string.h"
#define N 7

/**
 * Affiche les RECORD ayant un attribut vide et leur nombre
 * @param array : Pointeur vers AARRAY
 */
void missing_record(AARRAY *array) {
    int cmpt = 0;
    int i, j, k;
    for (i = 0; i < array->size; i++) {
        if (array->content[i] != NULL) {
            for (j = 0; j < array->content[i]->length; j++) {
                k = 0;
                while (k < N && strcmp(array->content[i]->content[j]->data[k], "") != 0) k++;
                if (k < N) {
                    cmpt++;
                    rdisplay(array->content[i]->content[j]);
                    printf("\n");
                }
            }
        }
    }
    printf("Il y a %d abonnées avec une information manquante.", cmpt);
    printf("\n");
}