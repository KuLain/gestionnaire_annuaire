//
// Created by lain on 09/01/2022.
//

#ifndef SAE_1_2_MAIN_MENU_GUI_H
#define SAE_1_2_MAIN_MENU_GUI_H
#include <gtk-3.0/gtk/gtk.h>
#include "struct/ArbreBinaireRecherche.h"

#define NB_TREE 5

#define TREE_DISPLAY 0
#define TREE_DEL 1
#define TREE_SORTED 2
#define TREE_FILTERED 3
#define TREE_MISSING 5

typedef struct global_properties {
    GtkWindow *main_window;
    GtkBuilder *builder;
    ABR *base_data;
    char *path;
    char delim;
    RECORD *change_current;
    int first_call_display[NB_TREE];
    int file_modified;
} GLOBAL_P;

enum {
    COL_PRENOM = 0,
    COL_NOM,
    COL_VILLE,
    COL_CP,
    COL_TELEPHONE,
    COL_MAIL,
    COL_PROFESSION,
};

#endif //SAE_1_2_MAIN_MENU_GUI_H
