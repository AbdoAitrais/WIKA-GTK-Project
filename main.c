#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>

#include "macros.c"
#include "by Abderrahman/UI_individu_macros.h"
#include "by Abderrahman/init_env_macro.h"









void set_default_visruses(gpointer builder)
{
    /**COVID-19
     * prctcontam 6.28% (i did the calculations ..) 496M out of 7.9B
     * tauxmortal 1.24% (i did the calculations ..) 6.17M out of 496M
     * cerclecontam 1 à 2 metres ( not sure )
     * */

}

int main(int argc, char *argv [])
{
    /** Declarations **/
    GtkWidget *fenetre_principale = NULL;
    GtkWidget *button = NULL;


    GtkBuilder *builder = NULL;
    GError *error = NULL;
    gchar *filename = NULL;



    /** Initialisation de la librairie Gtk. */
    gtk_init(&argc, &argv);

    /**Ouverture du fichier Glade de la fenêtre principale */
    builder = gtk_builder_new();

    /** Création du chemin complet pour accéder au fichier test.glade. */
    /** g_build_filename(); construit le chemin complet en fonction du système */
    /** d'exploitation. ( / pour Linux et \ pour Windows) */
    filename =  g_build_filename ("Interface2.glade", NULL);

    /** Chargement du fichier test.glade. */
    gtk_builder_add_from_file (builder, filename, &error);
    g_free (filename);
    if (error)
    {
        gint code = error->code;
        g_printerr("%s\n", error->message);
        g_error_free (error);
        return code;
    }

    /** Récupération du pointeur de la fenêtre principale */
    fenetre_principale = GTK_WIDGET(gtk_builder_get_object (builder, "MainWindow"));

    /** The widget that contains the grid **/
    GtkWidget *ViewPort2 = GTK_WIDGET(gtk_builder_get_object (builder, "ViewPort2"));
    /** button for signal **/
    button = GTK_WIDGET(gtk_builder_get_object (builder, "subutton"));


    set_css(builder);



    g_printerr("\nReached me\n");

    /** create and add the grid to the ViewPort **/
    init_background(ViewPort2,builder);


    /** Affectation du signal "destroy" à la fonction gtk_main_quit(); pour la */
    /** fermeture de la fenêtre. */
    g_signal_connect (G_OBJECT(fenetre_principale), "destroy", (GCallback)gtk_main_quit, NULL);

    /** signal to get added virus **/
    g_signal_connect (GTK_BUTTON(button), "clicked", (GCallback)enregistrer_virus, builder);


    /** Affichage de la fenêtre principale. */
    gtk_widget_show_all (fenetre_principale);

    /// RUN ENV MOVEMENTS
    g_timeout_add(1000, iterateIndividusList, fenetre_principale);

    gtk_main();



    return 0;
}

