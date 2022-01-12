#include <stdio.h>
#include <string.h>
#include <gtk-3.0/gtk/gtk.h>
#include "gui/main_menu_gui.h"
#include "header/struct/ArbreBinaireRecherche.h"
#include "header/file_processing.h"
#include "header/gui/main_menu_gui.h"
#include <time.h>

#define NB_TREE 5

#define TREE_DISPLAY 0
#define TREE_DEL 1
#define TREE_SORTED 2
#define TREE_FILTERED 3
#define TREE_MISSING 5

enum {
    COL_PRENOM = 0,
    COL_NOM,
    COL_VILLE,
    COL_CP,
    COL_TELEPHONE,
    COL_MAIL,
    COL_PROFESSION,
};

GtkBuilder *builder;
ABR *base_data;
char *path;
char delim;
RECORD *change_current;
int first_call_display[NB_TREE];

void fill_view(GtkTreeView *view, int i, ABR *arbre){
    gtk_tree_view_set_model(view, NULL);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

    if (first_call_display[i] == 0) {
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

        first_call_display[i] = 1;
    }

    GtkTreeModel *model = create_and_fill_model(arbre);

    gtk_tree_view_set_model(GTK_TREE_VIEW (view), model);

    g_object_unref(model);
}

void fill_view_sorted(GtkTreeView *view,int i, ABR *arbre, int colonne, double *temps, int choix, int *nb_elt) {
    gtk_tree_view_set_model(view, NULL);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

    if (first_call_display[i] == 0) {
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

        first_call_display[i] = 1;
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

void fill_view_filtered(GtkTreeView *view, int i, ABR *arbre, int colonne, char *filtre, double *temps) {
    gtk_tree_view_set_model(view, NULL);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

    if (first_call_display[2] == 0) {
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

        first_call_display[2] = 1;
    }


    GtkTreeModel *model = create_and_fill_model_tab(arbre, colonne, filtre, temps, 2, NULL);

    gtk_tree_view_set_model(GTK_TREE_VIEW (view), model);

    g_object_unref(model);
}

void OnDestroy(GtkWidget *pWidget, gpointer pData) {
    abr_free(base_data);
    gtk_main_quit();
}

void path_valider_button_clicked_cb(GtkButton *home_valider_button, GtkBox *home_container) {
    GtkFileChooser *fileChooser = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "home_path"));
    GtkEntry *delimEntry = GTK_ENTRY(gtk_builder_get_object(builder, "home_delim"));
    path = (char *) gtk_file_chooser_get_filename(fileChooser);
    delim = ((char *) gtk_entry_get_text(delimEntry))[0];
    if (path != NULL) {
        base_data = abr_init();
        parse_csv(&base_data, path, delim);
        abr_display(base_data);
    }

}

void add_button_pressed(GtkButton *button, GtkBox *data) {
    char **infos = malloc(sizeof(char *) * 7);
    RECORD *tmp;
    char labels[7][150] = {"add_prenom_entry", "add_nom_entry", "add_ville_entry", "add_cp_entry", "add_phone_entry",
                           "add_mail_entry", "add_job_entry"};
    int i;
    for (i = 0; i < 7; i++)
        infos[i] = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, labels[i])));
    tmp = rinit(infos);
    abr_inserer(&base_data, tmp->data[0], tmp->data[1], tmp);
    abr_csv(base_data, path, delim);
    free(infos);
}

void change_button_pressed(GtkButton *button, GtkBox *data) {
    int i;
    char entrees_labels[7][150] = {"change_prenom_entry", "change_nom_entry", "change_ville_entry", "change_cp_entry",
                                   "change_phone_entry", "change_mail_entry", "change_job_entry"};
    char *prenom_cherche = (char *) gtk_entry_get_text(
            GTK_ENTRY(gtk_builder_get_object(builder, "change_prenom_cherche")));
    char *nom_cherche = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "change_nom_cherche")));
    char *filtre_cherche = (char *) gtk_entry_get_text(
            GTK_ENTRY(gtk_builder_get_object(builder, "change_filter_cherche")));
    GtkRadioButton *email_toggle = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "change_mail"));

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(email_toggle))) {
        change_current = abr_valeur(base_data, prenom_cherche, nom_cherche, MAIL, filtre_cherche);
    } else {
        change_current = abr_valeur(base_data, prenom_cherche, nom_cherche, TELEPHONE, filtre_cherche);
    }
    if (change_current == NULL) {
        return;
    }
    rdisplay(change_current);
    for (i = 0; i < 7; i++) {
        gtk_entry_set_placeholder_text(GTK_ENTRY(gtk_builder_get_object(builder, entrees_labels[i])),
                                       change_current->data[i]);
    }
}

void change_validate_button_pressed(GtkButton *button, GtkBox *data) {
    int i;
    RECORD *swap;
    char *tmp;
    char entrees_labels[7][150] = {"change_prenom_entry", "change_nom_entry", "change_ville_entry", "change_cp_entry",
                                   "change_phone_entry", "change_mail_entry", "change_job_entry"};

    if (change_current == NULL) return;
    for (i = 0; i < 7; i++) {
        tmp = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, entrees_labels[i])));
        if (strcmp(tmp, "") != 0) {
            if (i < 2) {
                swap = r_copy(change_current);
                abr_supprimer(&base_data, change_current->data[0], change_current->data[1], MAIL,
                              change_current->data[MAIL]);
                swap->data[i] = realloc(swap->data[i], sizeof(char) * 150);
                strcpy(swap->data[i], tmp);
                swap->data[i] = realloc(swap->data[i], sizeof(char) * (strlen(swap->data[i]) + 1));
                abr_inserer(&base_data, swap->data[PRENOM], swap->data[NOM], swap);
                change_current = swap;
            } else {
                change_current->data[i] = realloc(change_current->data[i], sizeof(char) * 150);
                strcpy(change_current->data[i], tmp);
                change_current->data[i] = realloc(change_current->data[i],
                                                  sizeof(char) * (strlen(change_current->data[i]) + 1));
            }
        }
    }
}

void actualise_display_button_pressed(GtkButton *button, GtkBox *data) {
    GtkTreeView *view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "display_tree_view"));
    fill_view(view, 0, base_data);
}

void actualise_del_button_pressed(GtkButton *button, GtkBox *data) {
    GtkTreeView *view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "del_tree_view"));
    fill_view(view, 1, base_data);
}

void suppr_del_button_pressed(GtkButton *button) {
    char *prenom = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "del_prenom")));
    char *nom = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "del_nom")));
    char *filtre = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "del_filter")));
    GtkRadioButton *toggleButton = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "del_mail"));

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggleButton))) {
        abr_supprimer(&base_data, prenom, nom, MAIL, filtre);
    } else {
        abr_supprimer(&base_data, prenom, nom, TELEPHONE, filtre);
    }
    abr_csv(base_data, path, delim);
    actualise_del_button_pressed(NULL, NULL);
}

void access_button_pressed(GtkButton *button) {
    char *prenom = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "search_prenom")));
    char *nom = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "search_nom")));
    char *filtre = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "search_filter")));
    GtkRadioButton *toggleButton = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "search_mail"));
    GtkTreeView *view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "display_tree_view"));
    GtkLabel *time_result = GTK_LABEL(gtk_builder_get_object(builder, "search_time_result"));
    RECORD *abonne, *copie_abonne;
    ABR *tmp;
    struct timespec debut, fin;
    char float_time[50];

    clock_gettime(CLOCK_REALTIME, &debut);
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggleButton))) {
        abonne = abr_valeur(base_data, prenom, nom, MAIL, filtre);
    } else {
        abonne = abr_valeur(base_data, prenom, nom, TELEPHONE, filtre);
    }
    clock_gettime(CLOCK_REALTIME, &fin);
    gcvt((fin.tv_nsec - debut.tv_nsec)*0.000001, 6, float_time);
    strcat(float_time, " ms");
    gtk_label_set_text(time_result, float_time);
    if (abonne == NULL) return;

    gtk_tree_view_set_model(view, NULL);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    if (first_call_display[0] == 0) {
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

        first_call_display[0] = 1;
    }
    copie_abonne = r_copy(abonne);
    tmp = abr_init();
    abr_inserer(&tmp, copie_abonne->data[PRENOM], copie_abonne->data[NOM], copie_abonne);
    fill_view(view, 0, tmp);
    abr_free(tmp);
}

void sorted_button_pressed (GtkButton *bouton) {
    GtkRadioButton *filtres[4];
    double temps = 0;
    filtres[0] = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "sort_prenom"));
    filtres[1] = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "sort_nom"));
    filtres[2] = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "sort_cp"));
    filtres[3] = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "sort_prof"));
    GtkTreeView *view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "sorted_tree_view"));
    GtkLabel *temps_label = GTK_LABEL(gtk_builder_get_object(builder, "sort_time_result"));
    char float_time[50];

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(filtres[0]))) {
        fill_view(view, TREE_SORTED, base_data);
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(filtres[1]))) {
        fill_view_sorted(view, TREE_SORTED, base_data, NOM,&temps, 1, NULL);
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(filtres[2]))) {
        fill_view_sorted(view, TREE_SORTED,base_data, CP,&temps, 1, NULL);
    } else {
        fill_view_sorted(view, TREE_SORTED, base_data, PROFESSION,&temps, 1, NULL);
    }

    gcvt(temps, 6, float_time);
    strcat(float_time, " ms");
    gtk_label_set_text(temps_label, float_time);
}

void filtered_button_pressed (GtkButton *bouton) {
    GtkRadioButton *radios[4];
    double temps;
    char float_time[50];
    GtkEntry *filtre;
    int col;
    GtkTreeView  *view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "filter_tree_view"));
    GtkLabel  *titre = GTK_LABEL(gtk_builder_get_object(builder, "filter_time_result"));

    radios[0] = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "filter_prenom"));
    radios[1] = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "filter_nom"));
    radios[2] = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "filter_cp"));
    radios[3] = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "filter_prof"));

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radios[0]))) {
        filtre = GTK_ENTRY(gtk_builder_get_object(builder, "filter_prenom_entry"));
        col = PRENOM;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radios[1]))) {
        filtre = GTK_ENTRY(gtk_builder_get_object(builder, "filter_nom_entry"));
        col = NOM;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radios[2]))) {
        filtre = GTK_ENTRY(gtk_builder_get_object(builder, "filter_cp_entry"));
        col = CP;
    } else {
        filtre = GTK_ENTRY(gtk_builder_get_object(builder, "filter_prof_entry"));
        col = PROFESSION;
    }
    fill_view_filtered(view, TREE_FILTERED, base_data, col, (char*)gtk_entry_get_text(filtre), &temps);

    gcvt(temps, 6, float_time);
    strcat(float_time, " ms");
    gtk_label_set_text(titre, float_time);
}

void missing_button_pressed (GtkButton *bouton) {
    int nb_elt;
    char nombre[10];
    GtkTreeView *view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "missing_tree_view"));
    fill_view_sorted(view, TREE_MISSING, base_data, -1, NULL, 3, &nb_elt);
    sprintf(nombre, "%d", nb_elt);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "nb_missing")), nombre);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkWidget *pWindow, *path_button, *add_button, *change_button, *change_validate, *actualise_display, *del_actualise,
    *del_valider, *search_valider, *sorted_valider, *filtered_valider, *missing_actualise;
    change_current = NULL;
    for (int i = 0; i < NB_TREE; i++) first_call_display[i] = 0;

    builder = gtk_builder_new_from_file("../files/sae_window.glade");
    pWindow = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    path_button = GTK_WIDGET(gtk_builder_get_object(builder, "home_valider_button"));
    add_button = GTK_WIDGET(gtk_builder_get_object(builder, "add_validate_button"));
    change_button = GTK_WIDGET(gtk_builder_get_object(builder, "change_valider_cherche_button"));
    change_validate = GTK_WIDGET(gtk_builder_get_object(builder, "change_validate_button"));
    actualise_display = GTK_WIDGET(gtk_builder_get_object(builder, "display_actualise"));
    del_actualise = GTK_WIDGET(gtk_builder_get_object(builder, "del_actualise"));
    del_valider = GTK_WIDGET(gtk_builder_get_object(builder, "del_valider_button"));
    search_valider = GTK_WIDGET(gtk_builder_get_object(builder, "search_valider_button"));
    sorted_valider = GTK_WIDGET(gtk_builder_get_object(builder, "sorted_valider_button"));
    filtered_valider = GTK_WIDGET(gtk_builder_get_object(builder, "filter_valider_button"));
    missing_actualise = GTK_WIDGET(gtk_builder_get_object(builder, "actualise_missing"));

    g_signal_connect(path_button, "clicked", G_CALLBACK(path_valider_button_clicked_cb), NULL);
    g_signal_connect(add_button, "clicked", G_CALLBACK(add_button_pressed), NULL);
    g_signal_connect(change_button, "clicked", G_CALLBACK(change_button_pressed), NULL);
    g_signal_connect(change_validate, "clicked", G_CALLBACK(change_validate_button_pressed), NULL);
    g_signal_connect(actualise_display, "clicked", G_CALLBACK(actualise_display_button_pressed), NULL);
    g_signal_connect(del_actualise, "clicked", G_CALLBACK(actualise_del_button_pressed), NULL);
    g_signal_connect(del_valider, "clicked", G_CALLBACK(suppr_del_button_pressed), NULL);
    g_signal_connect(search_valider, "clicked", G_CALLBACK(access_button_pressed), NULL);
    g_signal_connect(sorted_valider, "clicked", G_CALLBACK(sorted_button_pressed), NULL);
    g_signal_connect(filtered_valider, "clicked", G_CALLBACK(filtered_button_pressed), NULL);
    g_signal_connect(missing_actualise, "clicked", G_CALLBACK(missing_button_pressed), NULL);

    g_signal_connect(pWindow, "destroy", G_CALLBACK(OnDestroy), NULL);

    gtk_widget_show(pWindow);
    gtk_main();

    return 0;
}
