//
// Created by abdo on 5/1/2022.
//

#ifndef MAIN_C_DIALOG_MACRO_H
#define MAIN_C_DIALOG_MACRO_H
#include <gtk/gtk.h>

void macro_dialog(gchar * msg)
{
    GtkWidget *limit;
    gpointer data=NULL;
    limit = gtk_message_dialog_new (GTK_WINDOW(data),
                                    GTK_DIALOG_MODAL,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_CLOSE,
                                    "%s", msg);

    /* Affichage de la boite de message */
    gtk_dialog_run(GTK_DIALOG(limit));

    /* Destruction de la boite de message */
    gtk_widget_destroy(limit);
}

#endif //MAIN_C_DIALOG_MACRO_H
