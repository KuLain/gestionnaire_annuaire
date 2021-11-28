//
// Created by julie on 28/11/2021.
//

#include "../header/sorted_display.h"
#include <stdlib.h>
#include <string.h>

void aarray_list(AARRAY* array, LIST* liste, int filter) {
    int i,j;
    for (i = 0; i < array->size; i++) {
        if (array->content[i] != NULL) {
            for (j = 0; j < array->content[i]->length; j++) {
                lpush(liste, (RECORD*)array->content[i]->content[j]);
            }
        }
    }
}

void bubble_sort(AARRAY* array, int filter) {
    LIST *liste = linit();
    RECORD *tmp;
    int fin_non_triee;
    int est_triee = 0;
    int i;

    aarray_list(array, liste, filter);
    fin_non_triee = liste->length - 1;

    while (fin_non_triee > 0 && est_triee != 1) {
        est_triee = 1;
        for (i = 0; i < fin_non_triee; i++) {
            if (strcmp(((RECORD*)liste->content[i])->data[filter], ((RECORD*)liste->content[i+1])->data[filter]) > 0) {
                tmp = liste->content[i];
                liste->content[i] = liste->content[i+1];
                liste->content[i+1] = tmp;

                est_triee = 0;
            }
        }
        fin_non_triee--;
    }

    for (i = 0; i < liste->length; i++) {
        rdisplay(((RECORD*)liste->content[i]));
        printf("\n");
    }
    free(liste->content);
    free(liste);
}

int partition(LIST *liste, int gauche, int droite, int filter) {
    char *clef;
    RECORD *tmp;
    int i, j;

    clef = ((RECORD*)liste->content[droite])->data[filter];
    i = gauche-1;
    j = droite;
    while (i <= j) {
        while ((++i < droite) && (strcmp(((RECORD*)liste->content[i])->data[filter],clef) < 0));
        while ((--j > (gauche-1)) && (strcmp(((RECORD*)liste->content[j])->data[filter],clef) > 0));
        if (i < j) {
            tmp = liste->content[i];
            liste->content[i] = liste->content[j];
            liste->content[j] = tmp;
        }
    }
    tmp = liste->content[i];
    liste->content[i] = liste->content[droite];
    liste->content[droite] = tmp;
    return i;
}

void quick_sort_rec(LIST *liste, int gauche, int droite, int filter) {
    int pivot;
    if (gauche < droite) {
        pivot = partition(liste, gauche, droite, filter);
        quick_sort_rec(liste, gauche, pivot-1,filter);
        quick_sort_rec(liste, pivot+1, droite,filter);
    }
}

void quick_sort(AARRAY *array, int filter) {
    LIST *liste = linit();
    int i;

    aarray_list(array, liste, filter);
    quick_sort_rec(liste, 0, liste->length-1, filter);

    for (i = 0; i < liste->length; i++) {
        printf("%s", ((RECORD*)liste->content[i])->data[0]);
        printf("\n");
    }
    free(liste->content);
    free(liste);
}