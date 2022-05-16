#include <stdlib.h>
#include "lib/UI_individu_macros.h"
#include "lib/init_env_macro.h"
#include "lib/tool.h"


int main(int argc, char *argv[]) {
    /** Declarations **/
    GtkWidget *fenetre_principale = NULL;
    GtkWidget *button = NULL;


    GtkBuilder *builder = NULL;

    GError *error = NULL;
    gchar *filename = NULL;
    //added
    GtkWidget *playButton = NULL;
    GtkWidget *pauseButton = NULL;
    GtkWidget *AboutButton = NULL;
    GtkWidget *decButton = NULL;
    GtkWidget *incButton = NULL;
    GtkWidget *quit = NULL;
    GtkWidget *restBtn = NULL;
    GtkWidget *msgEntry = NULL;


    /** Initialisation de la librairie Gtk. */
    gtk_init(&argc, &argv);

    /**Ouverture du fichier Glade de la fenêtre principale */
    builder = getBuilder();

    /** Création du chemin complet pour accéder au fichier test.glade. */
    /** g_build_filename(); construit le chemin complet en fonction du système */
    /** d'exploitation. ( / pour Linux et \ pour Windows) */
    filename = g_build_filename("../Interface21.glade", NULL);

    /** Chargement du fichier test.glade. */
    gtk_builder_add_from_file(builder, filename, &error);
    g_free(filename);
    if (error) {
        gint code = error->code;
        g_printerr("%s\n", error->message);
        g_error_free(error);
        return code;
    }

    /** init and save stats to builder  **/
    init_save_Stats(builder);

    /** Récupération du pointeur de la fenêtre principale */
    fenetre_principale = GTK_WIDGET(gtk_builder_get_object(builder, BUILDER_ID_MAIN_WINDOW));

    /** The widget that contains the grid **/
    GtkWidget *ViewPort2 = GTK_WIDGET(gtk_builder_get_object(builder, "ViewPort2"));
    /** button for signal **/
    button = GTK_WIDGET(gtk_builder_get_object(builder, "subutton"));

    /** toolbar btn */
    playButton = GTK_WIDGET(gtk_builder_get_object(builder, "play"));
    pauseButton = GTK_WIDGET(gtk_builder_get_object(builder, "pause"));
    decButton = GTK_WIDGET(gtk_builder_get_object(builder, "decreaseVT"));
    incButton = GTK_WIDGET(gtk_builder_get_object(builder, "increaseVT"));

    AboutButton = GTK_WIDGET(gtk_builder_get_object(builder, "about"));
    g_signal_connect (GTK_TOOL_BUTTON(AboutButton), "clicked", (GCallback) about_game, NULL);

    restBtn = GTK_WIDGET(gtk_builder_get_object(builder, "restart"));
    g_signal_connect (GTK_TOOL_BUTTON(restBtn), "clicked", (GCallback) macro_restartEnv, NULL);

    quit = GTK_WIDGET(gtk_builder_get_object(builder, "quit"));
    g_signal_connect (GTK_TOOL_BUTTON(quit), "clicked", (GCallback) quit_game, NULL);
    mvToolBar(playButton, pauseButton, decButton, incButton);


    set_css(builder);


    g_printerr("\nReached me\n");

    /** create and add the grid to the ViewPort **/
    init_background(ViewPort2, builder);


    /** Affectation du signal "destroy" à la fonction gtk_main_quit(); pour la */
    /** fermeture de la fenêtre. */
    g_signal_connect (G_OBJECT(fenetre_principale), "destroy", (GCallback) gtk_main_quit, NULL);

    /** signal to get added virus **/
    g_signal_connect (GTK_BUTTON(button), "clicked", (GCallback) enregistrer_virus, builder);

    /** Signal destroy virus added message **/
    msgEntry = GTK_WIDGET(gtk_builder_get_object(builder, "entryNomVirus"));
    g_signal_connect (msgEntry, "button-press-event", (GCallback) destroy_message, builder);

    /** Affichage de la fenêtre principale. */
    gtk_widget_show_all(fenetre_principale);

    /// RUN ENV MOVEMENTS
    g_timeout_add(PLAY_SPEED, iterateIndividusList, builder);

    gtk_main();


    return 0;
}

