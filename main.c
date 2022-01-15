#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk-3.0/gtk/gtk.h>
#include "gui/main_menu_gui.h"
#include "header/struct/ArbreBinaireRecherche.h"
#include "header/gui/main_menu_gui.h"
#include "header/gui/buttons_event.h"

void OnDestroy(GtkWidget *pWidget, gpointer pData) {
    GLOBAL_P *proprietes = (GLOBAL_P*) pData;
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
    for (int i = 0; i < NB_TREE; i++) proprietes->first_call_display[i] = 0;
    proprietes->builder = gtk_builder_new_from_file("../sae_window.glade");
    pWindow = GTK_WIDGET(gtk_builder_get_object(proprietes->builder, "main_window"));
    proprietes->main_window = (GtkWindow*) pWindow;

    object_connect(proprietes);

    g_signal_connect(pWindow, "destroy", G_CALLBACK(OnDestroy), proprietes);
    gtk_widget_show(pWindow);

    gtk_main();

    free(proprietes);

    return 0;
}
