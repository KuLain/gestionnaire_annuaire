#include <stdlib.h>
#include "gui/call_dialogs.h"

/**
 * Affiche un pop-up d'information ou d'erreur
 * @param is_error : 1 si le pop-up affiche une erreur, 0 sinon
 * @param message : Message à afficher
 * @param proprietes : Pointeur vers un GLOBAL_P
 */
void call_dialog(int is_error, char message[], GLOBAL_P *proprietes) {
    WIN_CALL *infos = (WIN_CALL*) malloc(sizeof(WIN_CALL));
    infos->main_window = proprietes->main_window;
    strcpy(infos->message, message);
    if (is_error) {
        call_window_error(NULL, (gpointer) infos);
    } else {
        call_window_info(NULL, (gpointer) infos);
    }
    free(infos);
}

/**
 * Affiche un pop-up d'information
 * @param widget : Widget appelant la fonction
 * @param pass : Pointeur vers un GLOBAL_P à caster
 */
void call_window_info(GtkWidget *widget, gpointer *pass) {
    WIN_CALL *parametres = (WIN_CALL*) pass;
    GtkWidget *dialog = gtk_message_dialog_new(parametres->main_window,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "%s", parametres->message);
    gtk_window_set_title(GTK_WINDOW(dialog), "Success");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

/**
 * Affiche un pop-up d'erreur
 * @param widget : Widget appelant la fonction
 * @param pass : Pointeur vers un GLOBAL_P à caster
 */
void call_window_error(GtkWidget *widget, gpointer *pass) {
    WIN_CALL *parametres = (WIN_CALL*) pass;
    GtkWidget *dialog = gtk_message_dialog_new(parametres->main_window,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_OK,
                                               "%s", parametres->message);
    gtk_window_set_title(GTK_WINDOW(dialog), "Error");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}