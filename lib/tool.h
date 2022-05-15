#ifndef MAIN_C_TOOL_H
#define MAIN_C_TOOL_H

#include "../macros.c"



void pause_game(GtkWidget *btn, gpointer user_data) {
    PLAY_MODE = FALSE;
}

void start_game(GtkWidget *btn, gpointer user_data) {
    PLAY_MODE = TRUE;
}

void about_game(GtkWidget *btn, gpointer data) {
    GtkWidget *content_area, *dialog = gtk_dialog_new_with_buttons("About", NULL, GTK_DIALOG_MODAL, GTK_STOCK_OK,
                                                                   GTK_RESPONSE_OK, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *image_about = gtk_image_new_from_file("../pic/about.png");
    gtk_widget_set_size_request(dialog, 300, 300);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_container_add(GTK_CONTAINER(content_area), image_about);
    gtk_widget_show_all(dialog);
    gint reponse = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    save_envIntoFile(NULL);
}

void limit_speed(gchar *msg) {
    GtkWidget *limit;
    gpointer data = NULL;
    limit = gtk_message_dialog_new(GTK_WINDOW(data),
                                   GTK_DIALOG_MODAL,
                                   GTK_MESSAGE_INFO,
                                   GTK_BUTTONS_CLOSE,
                                   "%s", msg);

    /* Affichage de la boite de message */
    gtk_dialog_run(GTK_DIALOG(limit));

    /* Destruction de la boite de message */
    gtk_widget_destroy(limit);

}

void decreaseSpeed(GtkWidget *btn, gpointer user_data) {

    gtk_widget_set_sensitive(btn, TRUE);
    if (PLAY_SPEED <= 1400) {
        PLAY_SPEED += 100;
    } else {
        limit_speed("Minimum Speed reached");
        g_print("\n min limit of speed %d\n", PLAY_SPEED);
    }
}

void increaseSpeed(GtkWidget *btn, gpointer user_data) {
    if (PLAY_SPEED >= 200) {
        PLAY_SPEED -= 100;
    } else {
        limit_speed("Maximum speed reached");
        g_print("\n max limit of speed %d\n", PLAY_SPEED);
    }
}


void mvToolBar(GtkWidget *btn1, GtkWidget *btn3, GtkWidget *btn4, GtkWidget *btn5) {
    g_signal_connect (GTK_TOOL_BUTTON(btn3), "clicked", (GCallback) pause_game, NULL);
    g_signal_connect (GTK_TOOL_BUTTON(btn1), "clicked", (GCallback) start_game, NULL);
    g_signal_connect (GTK_TOOL_BUTTON(btn5), "clicked", (GCallback) increaseSpeed, NULL);
    g_signal_connect (GTK_TOOL_BUTTON(btn4), "clicked", (GCallback) decreaseSpeed, NULL);
}

void quit_game(GtkWidget *widget) {

    gpointer data = NULL;
    GtkWidget *ask = gtk_message_dialog_new(GTK_WINDOW(data),
                                            GTK_DIALOG_MODAL,
                                            GTK_MESSAGE_QUESTION,
                                            GTK_BUTTONS_YES_NO,
                                            " Do you really want\ndrop the game ?");

    /*   answer */
    switch (gtk_dialog_run(GTK_DIALOG(ask))) {
        case GTK_RESPONSE_YES:
            /* yes ->   quit application */
            gtk_main_quit();
            break;
        case GTK_RESPONSE_NO:
            /* no -> on destroy dialog */
            gtk_widget_destroy(ask);
            break;
    }

}

void restart(GtkWidget *widget) {
}

#endif
