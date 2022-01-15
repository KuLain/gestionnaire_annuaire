//
// Created by julie on 29/11/2021.
//

#ifndef SAE_1_2_FILTERED_DISPLAY_H
#define SAE_1_2_FILTERED_DISPLAY_H
#include "../struct/ArbreBinaireRecherche.h"
#include <gtk-3.0/gtk/gtk.h>
void filtered_records(ABR*);
void matching_filter(ABR* arbre, int column, char *filter, GtkListStore* store, GtkTreeIter *iter);
#endif //SAE_1_2_FILTERED_DISPLAY_H
