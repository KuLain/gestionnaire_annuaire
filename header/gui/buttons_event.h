#ifndef SAE_1_2_BUTTONS_EVENT_H
#define SAE_1_2_BUTTONS_EVENT_H

#include <gtk-3.0/gtk/gtk.h>
#include "main_menu_gui.h"

void path_valider_button_clicked_cb(GtkButton *, gpointer *);

void add_button_pressed(GtkButton *, gpointer *);

void change_button_pressed(GtkButton *, gpointer *);

void change_validate_button_pressed(GtkButton *, gpointer *);

void actualise_display_button_pressed(GtkButton *, gpointer *);

void actualise_del_button_pressed(GtkButton *, gpointer *);

void suppr_del_button_pressed(GtkButton *, gpointer *);

void access_button_pressed(GtkButton *, gpointer *);

void sorted_button_pressed(GtkButton *, gpointer *);

void filtered_button_pressed(GtkButton *, gpointer *);

void missing_button_pressed(GtkButton *, gpointer *);

void object_connect(GLOBAL_P *);

#endif //SAE_1_2_BUTTONS_EVENT_H
