#include <stdlib.h>
#include <time.h>
#include <gtk-3.0/gtk/gtk.h>
#include "../../header/guibuttons_event.h"
#include "../../header/guimain_menu_gui.h"
#include "../../header/guitree_display.h"
#include "../../header/guicall_dialogs.h"
#include "../../header/file_processing.h"

/**
 * Fonction appelé lorsque le bouton valider de l'accueil est pressé
 * Affecte les entrées dans pass et crée un ABR avec les lignes du CSV, affiche une fenêtre d'erreur sinon
 * @param bouton : Pointeur vers le bouton appelant la fonction
 * @param pass : Pointeur vers un GLOBAL_P à caster
 */
void path_valider_button_clicked_cb(GtkButton *bouton, gpointer *pass) {
    GLOBAL_P *proprietes = (GLOBAL_P *) pass;

    GtkFileChooser *fileChooser = GTK_FILE_CHOOSER(gtk_builder_get_object(proprietes->builder, "home_path"));
    GtkEntry *delimEntry = GTK_ENTRY(gtk_builder_get_object(proprietes->builder, "home_delim"));
    proprietes->path = (char *) gtk_file_chooser_get_filename(fileChooser);
    proprietes->delim = ((char *) gtk_entry_get_text(delimEntry))[0];
    if (proprietes->path != NULL && proprietes->delim != 0) {
        if (proprietes->base_data == NULL) proprietes->base_data = abr_init();
        if (parse_csv(&proprietes->base_data, proprietes->path, proprietes->delim, proprietes) != EXIT_FAILURE) {
            proprietes->file_modified = 0;
            call_dialog(0, "Votre fichier a correctement été ouvert", proprietes);
        }
    } else {
        call_dialog(1, "Sélectionnez un fichier et entrez un caractère délimiteur", proprietes);
    }
}

/**
 * Fonction appelé lorsque le bouton ajouter est pressé
 * Ajoute les données de l'abonnée entrée dans l'ABR
 * @param bouton : Pointeur vers le bouton appelant la fonction
 * @param pass : Pointeur vers un GLOBAL_P à caster
 */
void add_button_pressed(GtkButton *button, gpointer *pass) {
    GLOBAL_P *proprietes = (GLOBAL_P *) pass;
    FILE *fp;
    char **infos = (char **) malloc(sizeof(char *) * 7);
    RECORD *tmp;
    char labels[7][150] = {"add_prenom_entry", "add_nom_entry", "add_ville_entry", "add_cp_entry", "add_phone_entry",
                           "add_mail_entry", "add_job_entry"};
    int i;
    for (i = 0; i < 7; i++)
        infos[i] = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(proprietes->builder, labels[i])));
    tmp = rinit(infos);
    abr_inserer(&proprietes->base_data, tmp->data[0], tmp->data[1], tmp);
    proprietes->file_modified = 1;
    call_dialog(0, "L'abonné a bien été ajouté", proprietes);
    free(infos);
}

/**
 * Fonction appelé lorsque le bouton valider du menu Modification est pressé
 * Remplis les champs avec les informations de l'abonnée, affiche une fenêtre d'erreur sinon
 * @param bouton : Pointeur vers le bouton appelant la fonction
 * @param pass : Pointeur vers un GLOBAL_P à caster
 */
void change_button_pressed(GtkButton *button, gpointer *pass) {
    int i;
    GLOBAL_P *proprietes = (GLOBAL_P *) pass;
    char entrees_labels[7][150] = {"change_prenom_entry", "change_nom_entry", "change_ville_entry", "change_cp_entry",
                                   "change_phone_entry", "change_mail_entry", "change_job_entry"};
    char *prenom_cherche = (char *) gtk_entry_get_text(
            GTK_ENTRY(gtk_builder_get_object(proprietes->builder, "change_prenom_cherche")));
    char *nom_cherche = (char *) gtk_entry_get_text(
            GTK_ENTRY(gtk_builder_get_object(proprietes->builder, "change_nom_cherche")));
    char *filtre_cherche = (char *) gtk_entry_get_text(
            GTK_ENTRY(gtk_builder_get_object(proprietes->builder, "change_filter_cherche")));
    GtkRadioButton *email_toggle = GTK_RADIO_BUTTON(gtk_builder_get_object(proprietes->builder, "change_mail"));

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(email_toggle))) {
        proprietes->change_current = abr_valeur(proprietes->base_data, prenom_cherche, nom_cherche, MAIL,
                                                filtre_cherche);
    } else {
        proprietes->change_current = abr_valeur(proprietes->base_data, prenom_cherche, nom_cherche, TELEPHONE,
                                                filtre_cherche);
    }
    if (proprietes->change_current == NULL) {
        return;
    }
    for (i = 0; i < 7; i++) {
        gtk_entry_set_placeholder_text(GTK_ENTRY(gtk_builder_get_object(proprietes->builder, entrees_labels[i])),
                                       proprietes->change_current->data[i]);
    }
}

/**
 * Fonction appelé lorsque le bouton appliquer du menu modification est pressé
 * Modifie les données de l'abonné
 * @param bouton : Pointeur vers le bouton appelant la fonction
 * @param pass : Pointeur vers un GLOBAL_P à caster
 */
void change_validate_button_pressed(GtkButton *button, gpointer *pass) {
    int i, changed, success;
    GLOBAL_P *proprietes = (GLOBAL_P *) pass;
    RECORD *swap;
    char *tmp;
    char entrees_labels[7][150] = {"change_prenom_entry", "change_nom_entry", "change_ville_entry", "change_cp_entry",
                                   "change_phone_entry", "change_mail_entry", "change_job_entry"};

    if (proprietes->change_current == NULL) {
        call_dialog(1, "Aucun abonné ne correspond à ces informations", proprietes);
        return;
    }
    for (i = 0; i < 7; i++) {
        tmp = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(proprietes->builder, entrees_labels[i])));
        if (strcmp(tmp, "") != 0) {
            changed = 1;
            if (i < 2) {
                swap = r_copy(proprietes->change_current);
                success = abr_supprimer(&proprietes->base_data, proprietes->change_current->data[0],
                              proprietes->change_current->data[1], MAIL,
                              proprietes->change_current->data[MAIL], proprietes);
                if (!success) return;
                swap->data[i] = realloc(swap->data[i], sizeof(char) * 150);
                strcpy(swap->data[i], tmp);
                swap->data[i] = realloc(swap->data[i], sizeof(char) * (strlen(swap->data[i]) + 1));
                abr_inserer(&proprietes->base_data, swap->data[PRENOM], swap->data[NOM], swap);
                proprietes->change_current = swap;
            } else {
                proprietes->change_current->data[i] = realloc(proprietes->change_current->data[i], sizeof(char) * 150);
                strcpy(proprietes->change_current->data[i], tmp);
                proprietes->change_current->data[i] = realloc(proprietes->change_current->data[i],
                                                              sizeof(char) *
                                                              (strlen(proprietes->change_current->data[i]) + 1));
            }
        }
    }
    if (changed) {
        proprietes->file_modified = 1;
        call_dialog(0, "Les informations de l'abonné ont bien été modifiés", proprietes);
    }
}

/**
 * Fonction appelé lorsque le bouton actualiser du menu afficher est pressé
 * Affiche les abonnés contenus dans l'arbre
 * @param bouton : Pointeur vers le bouton appelant la fonction
 * @param pass : Pointeur vers un GLOBAL_P à caster
 */
void actualise_display_button_pressed(GtkButton *button, gpointer *pass) {
    GLOBAL_P *proprietes = (GLOBAL_P *) pass;
    GtkTreeView *view = GTK_TREE_VIEW(gtk_builder_get_object(proprietes->builder, "display_tree_view"));
    fill_view(view, proprietes, 0, proprietes->base_data);
}

/**
 * Fonction appelé lorsque le bouton actualiser du menu supprimer est pressé
 * Affiche les abonnés contenus dans l'arbre
 * @param bouton : Pointeur vers le bouton appelant la fonction
 * @param pass : Pointeur vers un GLOBAL_P à caster
 */
void actualise_del_button_pressed(GtkButton *button, gpointer *pass) {
    GLOBAL_P *proprietes = (GLOBAL_P *) pass;
    GtkTreeView *view = GTK_TREE_VIEW(gtk_builder_get_object(proprietes->builder, "del_tree_view"));
    fill_view(view, proprietes, 1, proprietes->base_data);
}

/**
 * Fonction appelé lorsque le bouton Valider du menu Supprimer est pressé
 * Supprime l'abonnée correspondant, affiche une fenêtre d'erreur sinon
 * @param bouton : Pointeur vers le bouton appelant la fonction
 * @param pass : Pointeur vers un GLOBAL_P à caster
 */
void suppr_del_button_pressed(GtkButton *button, gpointer *pass) {
    GLOBAL_P *proprietes = (GLOBAL_P *) pass;
    char *prenom = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(proprietes->builder, "del_prenom")));
    char *nom = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(proprietes->builder, "del_nom")));
    char *filtre = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(proprietes->builder, "del_filter")));
    GtkRadioButton *toggleButton = GTK_RADIO_BUTTON(gtk_builder_get_object(proprietes->builder, "del_mail"));

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggleButton))) {
        abr_supprimer(&proprietes->base_data, prenom, nom, MAIL, filtre, proprietes);
    } else {
        abr_supprimer(&proprietes->base_data, prenom, nom, TELEPHONE, filtre, proprietes);
    }
    actualise_del_button_pressed(NULL, pass);
    proprietes->file_modified = 1;
    call_dialog(0, "L'abonné a été supprimé", proprietes);
}

/**
 * Fonction appelé lorsque le bouton Valider du menu afficher est pressé
 * Affiche l'abonné correspondant aux informations, affiche une fenêtre d'erreur sinon
 * @param bouton : Pointeur vers le bouton appelant la fonction
 * @param pass : Pointeur vers un GLOBAL_P à caster
 */
void access_button_pressed(GtkButton *button, gpointer *pass) {
    GLOBAL_P *proprietes = (GLOBAL_P *) pass;
    char *prenom = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(proprietes->builder, "search_prenom")));
    char *nom = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(proprietes->builder, "search_nom")));
    char *filtre = (char *) gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(proprietes->builder, "search_filter")));
    GtkRadioButton *toggleButton = GTK_RADIO_BUTTON(gtk_builder_get_object(proprietes->builder, "search_mail"));
    GtkTreeView *view = GTK_TREE_VIEW(gtk_builder_get_object(proprietes->builder, "display_tree_view"));
    GtkLabel *time_result = GTK_LABEL(gtk_builder_get_object(proprietes->builder, "search_time_result"));
    RECORD *abonne, *copie_abonne;
    ABR *tmp;
    struct timespec debut, fin;
    char float_time[50];

    clock_gettime(CLOCK_REALTIME, &debut);
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggleButton))) {
        abonne = abr_valeur(proprietes->base_data, prenom, nom, MAIL, filtre);
    } else {
        abonne = abr_valeur(proprietes->base_data, prenom, nom, TELEPHONE, filtre);
    }
    clock_gettime(CLOCK_REALTIME, &fin);
    gcvt((fin.tv_nsec - debut.tv_nsec) * 0.000001, 6, float_time);
    strcat(float_time, " ms");
    gtk_label_set_text(time_result, float_time);
    if (abonne == NULL) return;

    gtk_tree_view_set_model(view, NULL);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    if (proprietes->first_call_display[TREE_DISPLAY] == 0) {
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

        proprietes->first_call_display[TREE_DISPLAY] = 1;
    }
    copie_abonne = r_copy(abonne);
    tmp = abr_init();
    abr_inserer(&tmp, copie_abonne->data[PRENOM], copie_abonne->data[NOM], copie_abonne);
    fill_view(view, proprietes, 0, tmp);
    abr_free(tmp);
}

/**
 * Fonction appelé lorsque le bouton Appliquer du menu Affichage trié est pressé
 * Affiche la liste des abonné trié selon un critère choisi
 * @param bouton : Pointeur vers le bouton appelant la fonction
 * @param pass : Pointeur vers un GLOBAL_P à caster
 */
void sorted_button_pressed(GtkButton *bouton, gpointer *pass) {
    GLOBAL_P *proprietes = (GLOBAL_P *) pass;
    GtkRadioButton *filtres[4];
    double temps = 0;
    filtres[0] = GTK_RADIO_BUTTON(gtk_builder_get_object(proprietes->builder, "sort_prenom"));
    filtres[1] = GTK_RADIO_BUTTON(gtk_builder_get_object(proprietes->builder, "sort_nom"));
    filtres[2] = GTK_RADIO_BUTTON(gtk_builder_get_object(proprietes->builder, "sort_cp"));
    filtres[3] = GTK_RADIO_BUTTON(gtk_builder_get_object(proprietes->builder, "sort_prof"));
    GtkTreeView *view = GTK_TREE_VIEW(gtk_builder_get_object(proprietes->builder, "sorted_tree_view"));
    GtkLabel *temps_label = GTK_LABEL(gtk_builder_get_object(proprietes->builder, "sort_time_result"));
    char float_time[50];

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(filtres[0]))) {
        fill_view(view, proprietes, TREE_SORTED, proprietes->base_data);
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(filtres[1]))) {
        fill_view_sorted(view, proprietes, TREE_SORTED, proprietes->base_data, NOM, &temps, 1, NULL);
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(filtres[2]))) {
        fill_view_sorted(view, proprietes, TREE_SORTED, proprietes->base_data, CP, &temps, 1, NULL);
    } else {
        fill_view_sorted(view, proprietes, TREE_SORTED, proprietes->base_data, PROFESSION, &temps, 1, NULL);
    }

    gcvt(temps, 6, float_time);
    strcat(float_time, " ms");
    gtk_label_set_text(temps_label, float_time);
}

/**
 * Fonction appelé lorsque le bouton Appliquer du menu Affichage filtré est pressé
 * Affiche les abonnés filtré selon un critère
 * @param bouton : Pointeur vers le bouton appelant la fonction
 * @param pass : Pointeur vers un GLOBAL_P à caster
 */
void filtered_button_pressed(GtkButton *bouton, gpointer *pass) {
    GLOBAL_P *proprietes = (GLOBAL_P *) pass;
    GtkRadioButton *radios[4];
    double temps;
    char float_time[50];
    GtkEntry *filtre;
    int col;
    GtkTreeView *view = GTK_TREE_VIEW(gtk_builder_get_object(proprietes->builder, "filter_tree_view"));
    GtkLabel *titre = GTK_LABEL(gtk_builder_get_object(proprietes->builder, "filter_time_result"));

    radios[0] = GTK_RADIO_BUTTON(gtk_builder_get_object(proprietes->builder, "filter_prenom"));
    radios[1] = GTK_RADIO_BUTTON(gtk_builder_get_object(proprietes->builder, "filter_nom"));
    radios[2] = GTK_RADIO_BUTTON(gtk_builder_get_object(proprietes->builder, "filter_cp"));
    radios[3] = GTK_RADIO_BUTTON(gtk_builder_get_object(proprietes->builder, "filter_prof"));

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radios[0]))) {
        filtre = GTK_ENTRY(gtk_builder_get_object(proprietes->builder, "filter_prenom_entry"));
        col = PRENOM;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radios[1]))) {
        filtre = GTK_ENTRY(gtk_builder_get_object(proprietes->builder, "filter_nom_entry"));
        col = NOM;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radios[2]))) {
        filtre = GTK_ENTRY(gtk_builder_get_object(proprietes->builder, "filter_cp_entry"));
        col = CP;
    } else {
        filtre = GTK_ENTRY(gtk_builder_get_object(proprietes->builder, "filter_prof_entry"));
        col = PROFESSION;
    }
    fill_view_filtered(view, proprietes, TREE_FILTERED, proprietes->base_data, col, (char *) gtk_entry_get_text(filtre),
                       &temps);

    gcvt(temps, 6, float_time);
    strcat(float_time, " ms");
    gtk_label_set_text(titre, float_time);
}

/**
 * Fonction appelé lorsque le bouton Actualiser du menu Imcomplets est pressé
 * Affiche les abonnés ayant une information manquante
 * @param bouton : Pointeur vers le bouton appelant la fonction
 * @param pass : Pointeur vers un GLOBAL_P à caster
 */
void missing_button_pressed(GtkButton *bouton, gpointer *pass) {
    GLOBAL_P *proprietes = (GLOBAL_P *) pass;
    int nb_elt;
    char nombre[10];
    GtkTreeView *view = GTK_TREE_VIEW(gtk_builder_get_object(proprietes->builder, "missing_tree_view"));
    fill_view_sorted(view, proprietes, TREE_MISSING, proprietes->base_data, -1, NULL, 3, &nb_elt);
    sprintf(nombre, "%d", nb_elt);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(proprietes->builder, "nb_missing")), nombre);
}

/**
 * Relie les actions des boutons à leur fonction
 * @param proprietes Pointeur vers un GLOBAL_P contenant les informations globales du fichier
 */
void object_connect(GLOBAL_P *proprietes) {
    GtkWidget *path_button, *add_button, *change_button, *change_validate, *actualise_display, *del_actualise,
            *del_valider, *search_valider, *sorted_valider, *filtered_valider, *missing_actualise;

    path_button = GTK_WIDGET(gtk_builder_get_object(proprietes->builder, "home_valider_button"));
    add_button = GTK_WIDGET(gtk_builder_get_object(proprietes->builder, "add_validate_button"));
    change_button = GTK_WIDGET(gtk_builder_get_object(proprietes->builder, "change_valider_cherche_button"));
    change_validate = GTK_WIDGET(gtk_builder_get_object(proprietes->builder, "change_validate_button"));
    actualise_display = GTK_WIDGET(gtk_builder_get_object(proprietes->builder, "display_actualise"));
    del_actualise = GTK_WIDGET(gtk_builder_get_object(proprietes->builder, "del_actualise"));
    del_valider = GTK_WIDGET(gtk_builder_get_object(proprietes->builder, "del_valider_button"));
    search_valider = GTK_WIDGET(gtk_builder_get_object(proprietes->builder, "search_valider_button"));
    sorted_valider = GTK_WIDGET(gtk_builder_get_object(proprietes->builder, "sorted_valider_button"));
    filtered_valider = GTK_WIDGET(gtk_builder_get_object(proprietes->builder, "filter_valider_button"));
    missing_actualise = GTK_WIDGET(gtk_builder_get_object(proprietes->builder, "actualise_missing"));

    g_signal_connect(path_button, "clicked", G_CALLBACK(path_valider_button_clicked_cb), proprietes);
    g_signal_connect(add_button, "clicked", G_CALLBACK(add_button_pressed), proprietes);
    g_signal_connect(change_button, "clicked", G_CALLBACK(change_button_pressed), proprietes);
    g_signal_connect(change_validate, "clicked", G_CALLBACK(change_validate_button_pressed), proprietes);
    g_signal_connect(actualise_display, "clicked", G_CALLBACK(actualise_display_button_pressed), proprietes);
    g_signal_connect(del_actualise, "clicked", G_CALLBACK(actualise_del_button_pressed), proprietes);
    g_signal_connect(del_valider, "clicked", G_CALLBACK(suppr_del_button_pressed), proprietes);
    g_signal_connect(search_valider, "clicked", G_CALLBACK(access_button_pressed), proprietes);
    g_signal_connect(sorted_valider, "clicked", G_CALLBACK(sorted_button_pressed), proprietes);
    g_signal_connect(filtered_valider, "clicked", G_CALLBACK(filtered_button_pressed), proprietes);
    g_signal_connect(missing_actualise, "clicked", G_CALLBACK(missing_button_pressed), proprietes);
}