#ifndef SAE_1_2_SORTED_DISPLAY_H
#define SAE_1_2_SORTED_DISPLAY_H

#include "struct/Record.h"
#include "struct/ArbreBinaireRecherche.h"

void sorted_records(ABR *arbre);

void ABR_list(ABR *arbre, RECORD *tab[], int *i);

void quick_sort(RECORD *tab[], const int taille, int filter);

void merge_sort(RECORD *tab[], const int taille, int filter);

void display_sorted_records(RECORD *tab[], const int taille);

#endif //SAE_1_2_SORTED_DISPLAY_H
