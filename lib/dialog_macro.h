//
// Created by abdo on 5/1/2022.
//

#ifndef MAIN_C_DIALOG_MACRO_H
#define MAIN_C_DIALOG_MACRO_H
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



gboolean macro_confirmationDialog(gchar* msg) {
    GtkBuilder *builder = getBuilder();
    GtkWidget *parent_window = GTK_WIDGET(gtk_builder_get_object(builder, BUILDER_ID_MAIN_WINDOW));
    GtkWidget *ask = gtk_message_dialog_new(GTK_WINDOW(parent_window),
                                            GTK_DIALOG_MODAL,
                                            GTK_MESSAGE_QUESTION,
                                            GTK_BUTTONS_YES_NO,
                                            "%s", msg);

    /*   answer */
    switch (gtk_dialog_run(GTK_DIALOG(ask))) {
        case GTK_RESPONSE_YES:
            gtk_widget_destroy(ask);
            return TRUE;
        case GTK_RESPONSE_NO:
            gtk_widget_destroy(ask);
            return FALSE;
    }
}

#endif //MAIN_C_DIALOG_MACRO_H
