//
// Created by lain on 30/11/2021.
//

#ifndef SAE1_2_EMPTY_DISPLAY_H
#define SAE1_2_EMPTY_DISPLAY_H

#include "../struct/ArbreBinaireRecherche.h"
#include "gtk-3.0/gtk/gtk.h"

void missing_record(ABR *arbre, GtkListStore *store, GtkTreeIter *iter, int *nb_abo);

#endif //SAE1_2_EMPTY_DISPLAY_H
