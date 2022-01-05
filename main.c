#include <stdio.h>
#include <gtk-3.0/gtk/gtk.h>

#define PATH "../files/gang.csv"
#define DELIM ','

void OnDestroy(GtkWidget *pWidget, gpointer pData)
{
    /* Arret de la boucle évènementielle */
    gtk_main_quit();
}

int main(int argc, char* argv[]){
    GtkWidget *pWindow;
    GtkWidget *pTitle;
    GtkWidget *pVBox;
    GtkWidget *pHBox, *pHBox2;
    GtkWidget *pButton[6];

    gtk_init(&argc,&argv);

    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Gestionnaire d'annuaire");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    /* Création de la GtkBox verticale */
    pVBox = gtk_vbox_new(TRUE, 0);
    pHBox = gtk_hbox_new(TRUE, 0);
    pHBox2 = gtk_hbox_new(TRUE, 0);

    /* Ajout de la GtkVBox dans la fenêtre */
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

    pTitle = gtk_label_new("Gestionnaire d'annuaire");
    gtk_box_pack_start(GTK_BOX(pVBox), pTitle, TRUE, TRUE, 10);

    /* Creation des boutons */
    pButton[0] = gtk_button_new_with_label("Ajouter");
    pButton[1] = gtk_button_new_with_label("Supprimer");
    pButton[2] = gtk_button_new_with_label("Modifier");
    pButton[3] = gtk_button_new_with_label("Afficher");
    pButton[4] = gtk_button_new_with_label("Trier");
    pButton[5] = gtk_button_new_with_label("Filtrer");

    gtk_box_pack_start(GTK_BOX(pVBox), pHBox, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(pVBox), pHBox2, TRUE, TRUE, 10);

    gtk_box_pack_start(GTK_BOX(pHBox), pButton[0], TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(pHBox), pButton[1], TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(pHBox), pButton[2], TRUE, TRUE, 10);

    gtk_box_pack_start(GTK_BOX(pHBox2), pButton[3], TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(pHBox2), pButton[4], TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(pHBox2), pButton[5], TRUE, TRUE, 10);

    gtk_widget_show_all(pWindow);

    gtk_main();
    return 0;
}
