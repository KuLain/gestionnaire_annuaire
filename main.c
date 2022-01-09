#include <stdio.h>
#include <string.h>
#include <gtk-3.0/gtk/gtk.h>
#include "gui/main_menu_gui.h"
#include "header/struct/ArbreBinaireRecherche.h"
#include "header/file_processing.h"

void OnDestroy(GtkWidget *pWidget, gpointer pData)
{
    /* Arret de la boucle évènementielle */
    gtk_main_quit();
}

int main(int argc, char* argv[]){
    ABR* base = abr_init();
    parse_csv(&base, "../files/annuaire5000.csv", ',');
    GtkWidget *pWindow;
    gtk_init(&argc,&argv);

    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Gestionnaire d'annuaire");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    fill_display_widget(pWindow, base);

    gtk_widget_show_all(pWindow);
    gtk_main();
    return 0;
}
