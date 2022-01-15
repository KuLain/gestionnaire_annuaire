//
// Created by julie on 14/01/2022.
//

#include "gui/tree_display.h"
#include "../header/affichage/filtered_display.h"
#include "../header/affichage/sorted_display.h"
#include "../header/affichage/empty_display.h"

void fill_model(ABR *arbre, GtkListStore *store, GtkTreeIter *iter) {
    if (!abr_est_vide(arbre)) {
        fill_model(arbre->fils_gauche, store, iter);
        for (int i = 0; i < arbre->nb_abonnes; i++) {
            RECORD tmp = *(arbre->abonnes[i]);

            gtk_list_store_append (store, iter);
            gtk_list_store_set (store, iter,
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

GtkTreeModel *create_and_fill_model (ABR *arbre)
{
    GtkListStore *store = gtk_list_store_new (7,
                                              G_TYPE_STRING,
                                              G_TYPE_STRING,
                                              G_TYPE_STRING,
                                              G_TYPE_STRING,
                                              G_TYPE_STRING,
                                              G_TYPE_STRING,
                                              G_TYPE_STRING);

    /* Append a row and fill in some data. */
    GtkTreeIter iter;
    g_print("Ready to print guys");
    fill_model(arbre, store, &iter);

    return GTK_TREE_MODEL (store);
}

GtkTreeModel *create_and_fill_model_tab(ABR *arbre, int colonne, char *filtre, double *temps, int choix, int *nb_elt) {
    GtkListStore *store = gtk_list_store_new (7,
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
        quick_sort(tab, n, colonne, store, &iter);
    } else if (choix == 2){
        matching_filter(arbre, colonne, filtre, store, &iter);
    } else {
        missing_record(arbre, store, &iter, nb_elt);
    }
    clock_gettime(CLOCK_REALTIME, &fin);
    if (temps != NULL) *temps = (fin.tv_nsec-debut.tv_nsec)*0.000001;
    return GTK_TREE_MODEL (store);
}

GtkWidget *create_view_and_model (ABR *arbre)
{
    GtkWidget *view = gtk_tree_view_new ();
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new ();

    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "Prenom",
                                                 renderer,
                                                 "text", COL_PRENOM,
                                                 NULL);

    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "Nom",
                                                 renderer,
                                                 "text", COL_NOM,
                                                 NULL);

    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "Ville",
                                                 renderer,
                                                 "text", COL_VILLE,
                                                 NULL);

    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "Code postal",
                                                 renderer,
                                                 "text", COL_CP,
                                                 NULL);

    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "Téléphone",
                                                 renderer,
                                                 "text", COL_TELEPHONE,
                                                 NULL);

    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "Mail",
                                                 renderer,
                                                 "text", COL_MAIL,
                                                 NULL);

    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "Profession",
                                                 renderer,
                                                 "text", COL_PROFESSION,
                                                 NULL);

    GtkTreeModel *model = create_and_fill_model (arbre);

    gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

    g_object_unref (model);

    return view;
}

void fill_view(GtkTreeView *view, GLOBAL_P* proprietes, int i, ABR *arbre) {
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

void fill_view_sorted(GtkTreeView *view, GLOBAL_P* proprietes,int i, ABR *arbre, int colonne, double *temps, int choix, int *nb_elt) {
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

    GtkTreeModel * model;
    if (choix == 1) {
        model = create_and_fill_model_tab(arbre, colonne, NULL, temps, 1, NULL);
    } else {
        model = create_and_fill_model_tab(arbre, -1, NULL, temps, 3, nb_elt);
    }

    gtk_tree_view_set_model(GTK_TREE_VIEW (view), model);

    g_object_unref(model);
}

void fill_view_filtered(GtkTreeView *view, GLOBAL_P* proprietes, int i, ABR *arbre, int colonne, char *filtre, double *temps) {
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

