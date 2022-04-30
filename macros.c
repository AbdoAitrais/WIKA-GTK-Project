
//
// Created by abdo on 3/8/2022.
//


#include "constants.h"
#include "by Abderrahman/structures.h"


/*********** project functions ****************/

void loadCSS(GtkWidget *window)
{
    GFile *css_gFile = g_file_new_for_path("style.css");
    GtkCssProvider *cssProvider = gtk_css_provider_new();

    gtk_css_provider_load_from_file(cssProvider, css_gFile, 0);

    gtk_style_context_add_provider_for_screen(gtk_widget_get_screen(window),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void set_css(gpointer builder)
{
    GtkWidget *fenetre_principale = NULL;
    GtkWidget *menu = NULL;
    GtkWidget *stack = NULL;
    GtkWidget *switcher = NULL;
    GtkWidget *comboBox1 = NULL;
    GtkWidget *comboBox2 = NULL;
    GtkWidget *comboBox3 = NULL;
    GtkWidget *comboBox4 = NULL;
    GtkWidget *comboBox5 = NULL;

    GtkWidget *textView1 = NULL;

    GtkWidget *scale1 = NULL;
    GtkWidget *scale2 = NULL;
    GtkWidget *button = NULL;


    fenetre_principale = GTK_WIDGET(gtk_builder_get_object (builder, "MainWindow"));
    menu = GTK_WIDGET(gtk_builder_get_object (builder, "MenuBar"));

    button = GTK_WIDGET(gtk_builder_get_object (builder, "subutton"));
    stack = GTK_WIDGET(gtk_builder_get_object (builder, "stack"));
    switcher = GTK_WIDGET(gtk_builder_get_object (builder, "switch"));
    comboBox1 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxGenitiques"));
    comboBox2 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxTension"));
    comboBox3 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxDiabete"));
    comboBox4 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxCardiaque"));
    comboBox5 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxPoumons"));
    scale1 = GTK_WIDGET(gtk_builder_get_object (builder, "scale1"));
    scale2 = GTK_WIDGET(gtk_builder_get_object (builder, "scale2"));
    textView1 = GTK_WIDGET(gtk_builder_get_object (builder, "TextView"));



    loadCSS(fenetre_principale);

    gtk_style_context_add_class(gtk_widget_get_style_context(fenetre_principale), "class1");
    gtk_style_context_add_class(gtk_widget_get_style_context(menu), "menu");
    gtk_style_context_add_class(gtk_widget_get_style_context(stack), "stack");
    gtk_style_context_add_class(gtk_widget_get_style_context(switcher), "switch");
    gtk_style_context_add_class(gtk_widget_get_style_context(comboBox1), "comboBox");
    gtk_style_context_add_class(gtk_widget_get_style_context(comboBox2), "comboBox");
    gtk_style_context_add_class(gtk_widget_get_style_context(comboBox3), "comboBox");
    gtk_style_context_add_class(gtk_widget_get_style_context(comboBox4), "comboBox");
    gtk_style_context_add_class(gtk_widget_get_style_context(comboBox5), "comboBox");

    gtk_style_context_add_class(gtk_widget_get_style_context(scale1), "scale");
    gtk_style_context_add_class(gtk_widget_get_style_context(scale2), "scale");
    gtk_style_context_add_class(gtk_widget_get_style_context(textView1), "textView");

    gtk_style_context_add_class(gtk_widget_get_style_context(button), "button2");
}


gboolean macro_moveGrid(gpointer image) {

    gboolean returnVal = TRUE;

    GtkEventBox *boxSrc = GTK_EVENT_BOX (gtk_widget_get_parent(image));
    gint top, left;

    gtk_container_child_get(GTK_CONTAINER (gtk_widget_get_parent(GTK_WIDGET(boxSrc))),
                            GTK_WIDGET (boxSrc), "left-attach",
                            &left, "top-attach", &top, NULL)    ;


    g_assert(GTK_IS_EVENT_BOX(boxSrc));

    GtkWidget *child = gtk_bin_get_child(GTK_BIN(boxSrc));
    if (!child) {
        g_printerr("child does not exist");
        return returnVal;
    }
    gint pas = g_random_int_range(0, 4);
    GtkWidget *boxDst;


    /*
				    0
				    ^
               1 <     > 3
				    v
				    2
    */

    switch (pas) {
        case 0: {
            if ((top - 1) >= 0) {
                top--;
                break;
            }
        }
        case 1: {
            if ((left - 1) >= 0) {
                left--;
                break;
            }
        }
        case 2: {
            if ((top + 1) < DEFAULT_MAX_ROWS) {
                top++;
                break;
            }
        }
        case 3: {
            if ((left + 1) < DEFAULT_MAX_COLS) {
                left++;
                break;
            } else
                return returnVal;
        }
        default:
            return returnVal;
    }

    boxDst = gtk_grid_get_child_at(
            GTK_GRID(gtk_widget_get_parent(GTK_WIDGET(boxSrc))), left, top);
    g_assert(GTK_IS_EVENT_BOX(boxDst));

    /// si la case ne contient pas bnadem on ajoute
    if (boxDst && !(gtk_bin_get_child(GTK_BIN(boxDst)))) {
        g_object_ref(child);
        gtk_container_remove(GTK_CONTAINER(boxSrc), child);
        gtk_container_add(GTK_CONTAINER(boxDst), child);
        g_object_unref(child);
    }
    return returnVal;

}




Individu *lire_Indiv(gpointer builder);



void iterateSingleIndividu(gpointer data, gpointer user_data) {

                        /**     modified by me   **/
    int i,j;
    Coord pos;
    if (PLAY_MODE)
        macro_moveGrid(data);

                                        /**PARCOURT TOUT LE GRID  **/
                                        /** FAIRE LA CONTAMINATION VIRUS PAR VIRUS **/

    for(i=0;    i<DEFAULT_MAX_ROWS; i++)
    {
        pos.x = i;
        for(j=0;    j<DEFAULT_MAX_COLS; j++)
        {
            pos.y = j;
            GtkWidget *box = (GtkWidget*)gtk_grid_get_child_at(grid,i,j);
            GtkWidget *image = ((GtkWidget*)gtk_bin_get_child(box));
            if(image)
            {
                Individu* individu = (Individu*)g_object_get_data(G_OBJECT(image),DATA_KEY_INDIVIDU);
                GList *liste = individu->VirusList;
                Virus *virus = liste->data;
                /// pour la liste des virus de cet individu tanque il y a des virus à traiter
                while(virus)
                {
                    contaminationDesIndividus((GtkGrid*)grid,individu->pos,*virus);/// on faire la contamination par cette fonction
                    /// passer à le virus suivant
                    liste = liste->next;
                    virus = liste->data;
                }
            }
        }
    }
}

gboolean iterateIndividusList(gpointer data) {
    GTK_IS_WIDGET(data);

    GList *pers = g_object_get_data(data, DATA_KEY_LIST_INDIVIDU);

    g_list_foreach(pers, iterateSingleIndividu, NULL);

/*
    if (PLAY_MODE)
        g_timeout_add(600, iterateIndividusList, data);

    return FALSE;
    */
}


