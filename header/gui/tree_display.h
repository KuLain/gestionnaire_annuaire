//
// Created by julie on 14/01/2022.
//

#ifndef SAE_1_2_TREE_DISPLAY_H
#define SAE_1_2_TREE_DISPLAY_H

#include <gtk-3.0/gtk/gtk.h>
#include "../struct/ArbreBinaireRecherche.h"
#include "main_menu_gui.h"

#define CONVERT_UTF8(chaine) g_locale_from_utf8(chaine, -1, NULL, NULL, NULL)

void fill_model(ABR *arbre, GtkListStore *store, GtkTreeIter *iter);

GtkTreeModel *create_and_fill_model(ABR *arbre);

GtkTreeModel *create_and_fill_model_tab(ABR *, int, char *, double *, int, int *);

void fill_view(GtkTreeView *, GLOBAL_P *, int, ABR *);

void fill_view_sorted(GtkTreeView *, GLOBAL_P *, int, ABR *, int, double *, int, int *);

void fill_view_filtered(GtkTreeView *, GLOBAL_P *, int, ABR *, int, char *, double *);

#endif //SAE_1_2_TREE_DISPLAY_H
