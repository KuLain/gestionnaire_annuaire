#include "gui/tree_display.h"
#include "../header/affichage/filtered_display.h"
#include "../header/affichage/sorted_display.h"
#include "../header/affichage/empty_display.h"

/**
 * Remplis le model avec les informations des abonnés de l'arbre
 * @param arbre : Pointeur vers ABR
 * @param store : Pointeur vers GtkListStore
 * @param iter : Pointeur vers GtkTreeIter
 */
void fill_model(ABR *arbre, GtkListStore *store, GtkTreeIter *iter) {
    if (!abr_est_vide(arbre)) {
        fill_model(arbre->fils_gauche, store, iter);
        for (int i = 0; i < arbre->nb_abonnes; i++) {
            RECORD tmp = *(arbre->abonnes[i]);

            gtk_list_store_append(store, iter);
            gtk_list_store_set(store, iter,
                               COL_PRENOM, CONVERT_UTF8(tmp.data[PRENOM]),
                               COL_NOM, CONVERT_UTF8(tmp.data[NOM]),
                               COL_VILLE, CONVERT_UTF8(tmp.data[VILLE]),
                               COL_CP, CONVERT_UTF8(tmp.data[CP]),
                               COL_TELEPHONE, CONVERT_UTF8(tmp.data[TELEPHONE]),
                               COL_MAIL, CONVERT_UTF8(tmp.data[MAIL]),
                               COL_PROFESSION, CONVERT_UTF8(tmp.data[PROFESSION]),
                               -1);
        }
        fill_model(arbre->fils_droit, store, iter);
    }
}

/**
 * Crée et remplis un model avec les informations de l'arbre
 * @param arbre : Pointeur vers ABR contenant les informations des abonés
 * @return Modèle créé
 */
GtkTreeModel *create_and_fill_model(ABR *arbre) {
    GtkListStore *store = gtk_list_store_new(7,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING);

    /* Append a row and fill in some data. */
    GtkTreeIter iter;
    fill_model(arbre, store, &iter);

    return GTK_TREE_MODEL (store);
}

/**
 * Crée et remplis un model avec les informations de l'arbre avec un tri ou filtre
 * @param arbre : Pointeur vers l'ABR contenant les informations
 * @param colonne : 0 <= colonne < 7 : Colonne à trier ou filtrer
 * @param filtre : Chaine de caractère contenant le filtre à appliquer sur la colonne
 * @param temps : Pointeur vers un timespec pour avoir le temps d'exécution
 * @param choix : 1 si le modèle doit être trié, 2 si il doit être filtré et 3 si il doit afficher les abonnés ayant une information manquante
 * @param nb_elt : Pointeur vers un int qui contiendra le nombre d'abonnés ayant une information manquante
 * @return Modèle créé
 */
GtkTreeModel *create_and_fill_model_tab(ABR *arbre, int colonne, char *filtre, double *temps, int choix, int *nb_elt) {
    GtkListStore *store = gtk_list_store_new(7,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING);

    /* Append a row and fill in some data. */
    GtkTreeIter iter;
    int const n = abr_taille(arbre);
    int i = 0;
    struct timespec debut, fin;

    clock_gettime(CLOCK_REALTIME, &debut);
    if (choix == 1) {
        RECORD *tab[n];
        ABR_list(arbre, tab, &i);
        merge_sort(tab, n, colonne, store, &iter);
    } else if (choix == 2) {
        matching_filter(arbre, colonne, filtre, store, &iter);
    } else {
        missing_record(arbre, store, &iter, nb_elt);
    }
    clock_gettime(CLOCK_REALTIME, &fin);
    if (temps != NULL) *temps = (fin.tv_nsec - debut.tv_nsec) * 0.000001;
    return GTK_TREE_MODEL (store);
}

/**
 * Remplis la view à partir de l'arbre
 * @param view : Pointeur vers le GtkTreeView qui affichera le modèle
 * @param proprietes : Pointeur vers GLOBAL_P contenant les informations du fichier
 * @param i : Indice de la view dans GLOBAL_P->first_call_display
 * @param arbre : Pointeur vers l'ABR
 */
void fill_view(GtkTreeView *view, GLOBAL_P *proprietes, int i, ABR *arbre) {
    gtk_tree_view_set_model(view, NULL);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

    if (proprietes->first_call_display[i] == 0) {
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Prenom",
                                                    renderer,
                                                    "text", COL_PRENOM,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Nom",
                                                    renderer,
                                                    "text", COL_NOM,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Ville",
                                                    renderer,
                                                    "text", COL_VILLE,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Code postal",
                                                    renderer,
                                                    "text", COL_CP,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Téléphone",
                                                    renderer,
                                                    "text", COL_TELEPHONE,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Mail",
                                                    renderer,
                                                    "text", COL_MAIL,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Profession",
                                                    renderer,
                                                    "text", COL_PROFESSION,
                                                    NULL);

        proprietes->first_call_display[i] = 1;
    }

    GtkTreeModel *model = create_and_fill_model(arbre);

    gtk_tree_view_set_model(GTK_TREE_VIEW (view), model);

    g_object_unref(model);
}

/**
 * Remplis la view à partir de l'arbre avec un tri ou à partir des abonnés ayant une information manquante
 * @param view : Pointeur vers le GtkTreeView qui affichera le modèle
 * @param proprietes : Pointeur vers GLOBAL_P contenant les informations du fichier
 * @param i : Indice de la view dans GLOBAL_P->first_call_display
 * @param arbre : Pointeur vers l'ABR
 * @param colonne : 0 <= colonne < 7 : Colonne à trier
 * @param temps : Pointeur vers un timespec pour avoir le temps d'exécution
 * @param choix : 1 si le modèle doit être trié et 2 si il doit afficher les abonnés ayant une information manquante
 * @param nb_elt : Pointeur vers un int qui contiendra le nombre d'abonnés ayant une information manquante
 */
void fill_view_sorted(GtkTreeView *view, GLOBAL_P *proprietes, int i, ABR *arbre, int colonne, double *temps, int choix,
                      int *nb_elt) {
    gtk_tree_view_set_model(view, NULL);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

    if (proprietes->first_call_display[i] == 0) {
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Prenom",
                                                    renderer,
                                                    "text", COL_PRENOM,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Nom",
                                                    renderer,
                                                    "text", COL_NOM,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Ville",
                                                    renderer,
                                                    "text", COL_VILLE,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Code postal",
                                                    renderer,
                                                    "text", COL_CP,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Téléphone",
                                                    renderer,
                                                    "text", COL_TELEPHONE,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Mail",
                                                    renderer,
                                                    "text", COL_MAIL,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Profession",
                                                    renderer,
                                                    "text", COL_PROFESSION,
                                                    NULL);

        proprietes->first_call_display[i] = 1;
    }

    GtkTreeModel *model;
    if (choix == 1) {
        model = create_and_fill_model_tab(arbre, colonne, NULL, temps, 1, NULL);
    } else {
        model = create_and_fill_model_tab(arbre, -1, NULL, temps, 3, nb_elt);
    }

    gtk_tree_view_set_model(GTK_TREE_VIEW (view), model);

    g_object_unref(model);
}

/**
 * Remplis la view à partir de l'arbre filtré
 * @param view : Pointeur vers le GtkTreeView qui affichera le modèle
 * @param proprietes : Pointeur vers GLOBAL_P contenant les informations du fichier
 * @param i : Indice de la view dans GLOBAL_P->first_call_display
 * @param arbre : Pointeur vers l'ABR
 * @param colonne : 0 <= colonne < 7 : Colonne sur laquelle appliquer le filtre
 * @param filtre : Chaine de caractère contenant le filtre à appliquer
 * @param temps : Pointeur vers un timespec pour avoir le temps d'exécution
 */
void fill_view_filtered(GtkTreeView *view, GLOBAL_P *proprietes, int i, ABR *arbre, int colonne, char *filtre,
                        double *temps) {
    gtk_tree_view_set_model(view, NULL);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

    if (proprietes->first_call_display[i] == 0) {
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Prenom",
                                                    renderer,
                                                    "text", COL_PRENOM,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Nom",
                                                    renderer,
                                                    "text", COL_NOM,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Ville",
                                                    renderer,
                                                    "text", COL_VILLE,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Code postal",
                                                    renderer,
                                                    "text", COL_CP,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Téléphone",
                                                    renderer,
                                                    "text", COL_TELEPHONE,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Mail",
                                                    renderer,
                                                    "text", COL_MAIL,
                                                    NULL);

        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                    -1,
                                                    "Profession",
                                                    renderer,
                                                    "text", COL_PROFESSION,
                                                    NULL);

        proprietes->first_call_display[TREE_FILTERED] = 1;
    }


    GtkTreeModel *model = create_and_fill_model_tab(arbre, colonne, filtre, temps, 2, NULL);

    gtk_tree_view_set_model(GTK_TREE_VIEW (view), model);

    g_object_unref(model);
}

