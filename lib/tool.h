#ifndef MAIN_C_TOOL_H
#define MAIN_C_TOOL_H

#include "../macros.c"
#include "init_env_macro.h"
void macro_restartEnv();

void pause_game(GtkWidget *btn, gpointer user_data) {
    PLAY_MODE = FALSE;

}

void start_game(GtkWidget *btn, gpointer user_data) {
    PLAY_MODE = TRUE;
}

void about_game(GtkWidget *btn, gpointer data) {

    GtkWidget *content_area, *dialog = ((GtkWidget *) gtk_dialog_new_with_buttons("About", NULL, GTK_DIALOG_MODAL,  "gtk-ok",
                                                                   GTK_RESPONSE_OK, NULL));
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *image_about = gtk_image_new_from_file("../pic/about.png");
    gtk_widget_set_size_request(dialog, 300, 300);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_container_add(GTK_CONTAINER(content_area), image_about);
    gtk_widget_show_all(dialog);
    gint reponse = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

//    macro_loadAndSave_envIntoFile("test.wika");
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

void quit_game() {

    /*   answer */
    if (macro_confirmationDialog(" Do you really want\ndrop the game ?"))
        gtk_main_quit();
}


void macro_saveAsButton() {
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    gint res;

    GtkBuilder *builder = getBuilder();
    GtkWidget *parent_window = GTK_WIDGET(gtk_builder_get_object(builder, BUILDER_ID_MAIN_WINDOW));


    dialog = gtk_file_chooser_dialog_new("Save File",
                                         GTK_WINDOW(parent_window),
                                         GTK_FILE_CHOOSER_ACTION_SAVE,
                                         "_Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "_Save",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);
    chooser = GTK_FILE_CHOOSER (dialog);

    gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);


    gtk_file_chooser_set_current_name(chooser,
                                      DEFAULT_SAVE_FILE_NAME);


    res = gtk_dialog_run(GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;

        filename = gtk_file_chooser_get_filename(chooser);
        macro_loadAndSave_envIntoFile(filename);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

static void Add_Mode (GtkToggleButton *source, gpointer user_data) {
    if ( ADD_INDIVIDU_MODE)
        ADD_INDIVIDU_MODE= FALSE;
    else ADD_INDIVIDU_MODE =TRUE;

}
void macro_saveButton() {
    if (CURRENT_SAVE_FILE)
        macro_loadAndSave_envIntoFile(CURRENT_SAVE_FILE);
    else
        macro_saveAsButton();
}

void iterate_removeContainerChildren(GtkWidget *child, GtkContainer *container) {
    gtk_container_remove(container, child);
}

void macro_resetInterfaceEnv() {
    GtkBuilder *builder = getBuilder();
    GtkWidget *parent_window = GTK_WIDGET(gtk_builder_get_object(builder, BUILDER_ID_MAIN_WINDOW));
    GList *indivs = g_object_get_data(G_OBJECT(parent_window),DATA_KEY_LIST_INDIVIDU);

    g_list_foreach(indivs, (GFunc) gtk_widget_destroy, NULL);
    g_list_free(indivs);

    g_object_set_data(G_OBJECT(parent_window), DATA_KEY_LIST_INDIVIDU, NULL);
    GtkWidget *buttonBox = GTK_WIDGET(gtk_builder_get_object(builder, "ButtonBoxVirus"));

    GList *virussBtns = gtk_container_get_children(GTK_CONTAINER(buttonBox));
    g_list_foreach(virussBtns, (GFunc) iterate_removeContainerChildren, buttonBox);

}


void macro_restartEnv() {
    switch (macro_confirmationDialog("do you wanna save before restart!")) {
        case TRUE:
            macro_saveButton();
        case FALSE:
            macro_resetInterfaceEnv();
    }
}


#endif

