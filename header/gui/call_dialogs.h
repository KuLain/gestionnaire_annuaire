#ifndef SAE_1_2_CALL_DIALOGS_H
#define SAE_1_2_CALL_DIALOGS_H

#include <gtk-3.0/gtk/gtk.h>
#include "main_menu_gui.h"
typedef struct window_call {
    GtkWindow *main_window;
    char message[150];
} WIN_CALL;

void call_dialog(int, char[], GLOBAL_P*);

void call_window_info(GtkWidget*, gpointer*);

void call_window_error(GtkWidget *widget, gpointer *pass);

#endif //SAE_1_2_CALL_DIALOGS_H
