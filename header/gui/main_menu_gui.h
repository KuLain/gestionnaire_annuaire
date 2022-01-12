//
// Created by lain on 09/01/2022.
//

#ifndef SAE_1_2_MAIN_MENU_GUI_H
#define SAE_1_2_MAIN_MENU_GUI_H
#include <gtk-3.0/gtk/gtk.h>
#include "struct/ArbreBinaireRecherche.h"

GtkTreeModel *create_and_fill_model (ABR *arbre);
GtkTreeModel *create_and_fill_model_tab(ABR *arbre, int colonne, char *filtre, double *temps, int, int*);
#endif //SAE_1_2_MAIN_MENU_GUI_H
