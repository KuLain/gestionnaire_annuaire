#include <stdlib.h>
#include <gtk-3.0/gtk/gtk.h>
#include "header/gui/main_menu_gui.h"
#include "header/struct/ArbreBinaireRecherche.h"
#include "header/file_processing.h"
#include "header/gui/buttons_event.h"

/**
 * Fonction appelé lors de la fermeture de la fenêtre
 * @param pWidget : Pointeur vers le Widget appelant la fonction
 * @param pData : Pointeur vers un GLOBAL_P à caster
 */
void OnDestroy(GtkWidget *pWidget, gpointer pData) {
    GLOBAL_P *proprietes = (GLOBAL_P*) pData;
    gint reponse;
    GtkWidget *dialog = gtk_message_dialog_new(proprietes->main_window,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_QUESTION,
                                               GTK_BUTTONS_YES_NO,
                                               "Voulez vous sauvegarder le fichier ?");
    gtk_window_set_title(GTK_WINDOW(dialog), "Attention");
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    if (proprietes->path != NULL && proprietes->file_modified) {
        reponse = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        if (reponse == -8) {
            abr_csv(proprietes->base_data, proprietes->path, proprietes->delim);
        }
    }
    abr_free(proprietes->base_data);
    gtk_main_quit();
}


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GLOBAL_P *proprietes = (GLOBAL_P*) malloc(sizeof(GLOBAL_P));
    GtkWidget *pWindow;

    proprietes->base_data = abr_init();
    proprietes->change_current = NULL;
    proprietes->delim = 0;
    proprietes->path = NULL;

    for (int i = 0; i < NB_TREE; i++) proprietes->first_call_display[i] = 0;
    proprietes->builder = gtk_builder_new_from_file("ressources/sae_window.glade");
    pWindow = GTK_WIDGET(gtk_builder_get_object(proprietes->builder, "main_window"));
    proprietes->main_window = (GtkWindow*) pWindow;

    object_connect(proprietes);

    g_signal_connect(pWindow, "destroy", G_CALLBACK(OnDestroy), proprietes);
    gtk_widget_show(pWindow);

    gtk_main();

    free(proprietes);

    return 0;
}
