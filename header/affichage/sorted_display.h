//
// Created by julie on 28/11/2021.
//

#ifndef SAE_1_2_SORTED_DISPLAY_H
#define SAE_1_2_SORTED_DISPLAY_H
#include "../struct/Record.h"
#include "../struct/ArbreBinaireRecherche.h"
#include <gtk-3.0/gtk/gtk.h>
void sorted_records(ABR* arbre);
void ABR_list(ABR* arbre, RECORD* tab[], int* i);
void quick_sort(RECORD* tab[],const int taille, int filter, GtkListStore *store, GtkTreeIter *iter);
void merge_sort(RECORD* tab[],const int taille, int filter, GtkListStore *store, GtkTreeIter *iter);
void fill_model_tab(RECORD *tab[], int taille, GtkListStore *store, GtkTreeIter *iter);
#endif //SAE_1_2_SORTED_DISPLAY_H
