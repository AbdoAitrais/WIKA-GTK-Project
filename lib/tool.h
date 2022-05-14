#ifndef MAIN_C_TOOL_H
#define MAIN_C_TOOL_H

#include "../macros.c"


//struct struct used for some elements of toolbar

typedef struct {
    gint check;// if check=1 play btn is on
    gint speed;//
    guint id;// id of g_timeout_add

} maStr;


void pause_game(GtkWidget *btn, maStr *info) {
    if (info->check == 0) {
//        PLAY_MODE = FALSE;
//        g_source_remove(info->id);
//        info->check = 1;

        //gtk_widget_set_sensitive(btn,FALSE);
    }
    PLAY_MODE = FALSE;
}

void start_game(GtkWidget *btn, maStr *info) {
    PLAY_MODE = TRUE;
}

void about_game(GtkWidget *btn, gpointer data) {
    GtkWidget *content_area, *dialog = gtk_dialog_new_with_buttons("About", NULL, GTK_DIALOG_MODAL, GTK_STOCK_OK,
                                                                   GTK_RESPONSE_OK, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *image_about = gtk_image_new_from_file("About.png");
    gtk_widget_set_size_request(dialog, 300, 300);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_container_add(GTK_CONTAINER(content_area), image_about);
    gtk_widget_show_all(dialog);
    gint reponse = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void limit_speed() {
    GtkWidget *limit;
    gpointer data = NULL;
    limit = gtk_message_dialog_new(GTK_WINDOW(data),
                                   GTK_DIALOG_MODAL,
                                   GTK_MESSAGE_INFO,
                                   GTK_BUTTONS_CLOSE,
                                   "limit of speed \n  please decrease Speed ");

    /* Affichage de la boite de message */
    gtk_dialog_run(GTK_DIALOG(limit));

    /* Destruction de la boite de message */
    gtk_widget_destroy(limit);

}

void decreaseSpeed(GtkWidget *btn, maStr *info) {

    gtk_widget_set_sensitive(btn, TRUE);
    if (/*info->speed*/PLAY_SPEED > 0) {
        info->speed = (info->speed - ((gint) 100));

        PLAY_SPEED -= 100;
//        pause_game(btn, info);
//        start_game(btn, info);
    } else {
        limit_speed();
        g_print("\n limit of speed\n");

    }
}

void increaseSpeed(GtkWidget *btn, maStr *info) {
//    info->speed = (info->speed + ((gint) 100));
//    pause_game(btn, info);
//    start_game(btn, info);
    PLAY_SPEED += 100;
}


void mvToolBar(GtkWidget *btn1, GtkWidget *btn3, GtkWidget *btn4, GtkWidget *btn5, maStr *info) {


    g_signal_connect (GTK_TOOL_BUTTON(btn3), "clicked", (GCallback) pause_game, info);
    g_signal_connect (GTK_TOOL_BUTTON(btn1), "clicked", (GCallback) start_game, info);
    g_signal_connect (GTK_TOOL_BUTTON(btn4), "clicked", (GCallback) increaseSpeed, info);
    g_signal_connect (GTK_TOOL_BUTTON(btn5), "clicked", (GCallback) decreaseSpeed, info);
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

    return;
}

void restart(GtkWidget *widget) {
}

#endif
