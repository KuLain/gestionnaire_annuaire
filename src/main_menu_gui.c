//
// Created by lain on 09/01/2022.
//

#include "main_menu_gui.h"
#include "../header/struct/ArbreBinaireRecherche.h"

#define CONVERT_UTF8(chaine) g_locale_from_utf8(chaine, -1, NULL, NULL, NULL)

enum
{
    COL_PRENOM = 0,
    COL_NOM,
    COL_VILLE,
    COL_CP,
    COL_TELEPHONE,
    COL_MAIL,
    COL_PROFESSION,
} ;


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

static GtkTreeModel *
create_and_fill_model (ABR *arbre)
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
    fill_model(arbre, store, &iter);

    return GTK_TREE_MODEL (store);
}


static GtkWidget *
create_view_and_model (ABR *arbre)
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

void fill_display_widget (GtkWidget *main_window, ABR *arbre) {
    GtkWidget  *pScrollWindow;
    GtkWidget *view = create_view_and_model (arbre);
    pScrollWindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(pScrollWindow), view);
    gtk_container_add (GTK_CONTAINER (main_window), pScrollWindow);
}

void fill_menu_widget(GtkWidget *main_window) {
    int i;
    GtkWidget *pVBox, *pHBox, *pHBox2, *pTitle, *pButton[6];
    char noms_fonctions[6][50] = {"Ajouter", "Modifier","Supprimer", "Afficher", "Trier", "Filtrer"};

    /* Création de la GtkBox verticale */
    pVBox = gtk_vbox_new(TRUE, 0);
    pHBox = gtk_hbox_new(TRUE, 0);
    pHBox2 = gtk_hbox_new(TRUE, 0);

/* Ajout de la GtkVBox dans la fenêtre */
    gtk_container_add(GTK_CONTAINER(main_window), pVBox);

    pTitle = gtk_label_new("Gestionnaire d'annuaire");
    gtk_box_pack_start(GTK_BOX(pVBox), pTitle, TRUE, TRUE, 10);

    gtk_box_pack_start(GTK_BOX(pVBox), pHBox, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(pVBox), pHBox2, TRUE, TRUE, 10);

    for (i = 0; i < 3; i++) {
        pButton[i] = gtk_button_new_with_label(noms_fonctions[i]);
        gtk_box_pack_start(GTK_BOX(pHBox), pButton[i], TRUE, TRUE, 10);
    }

    for (i = 3; i < 6; i++) {
        pButton[i] = gtk_button_new_with_label(noms_fonctions[i]);
        gtk_box_pack_start(GTK_BOX(pHBox2), pButton[i], TRUE, TRUE, 10);
    }
}