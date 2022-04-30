
//
// Created by abdo on 3/8/2022.
//


#include "constants.h"
#include "by Abderrahman/structures.h"


/*********** project functions ****************/

void loadCSS(GtkWidget *window) {
    GFile *css_gFile = g_file_new_for_path("style.css");
    GtkCssProvider *cssProvider = gtk_css_provider_new();

    gtk_css_provider_load_from_file(cssProvider, css_gFile, 0);

    gtk_style_context_add_provider_for_screen(gtk_widget_get_screen(window),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void set_css(gpointer builder) {
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


    fenetre_principale = GTK_WIDGET(gtk_builder_get_object(builder, "MainWindow"));
    menu = GTK_WIDGET(gtk_builder_get_object(builder, "MenuBar"));

    button = GTK_WIDGET(gtk_builder_get_object(builder, "subutton"));
    stack = GTK_WIDGET(gtk_builder_get_object(builder, "stack"));
    switcher = GTK_WIDGET(gtk_builder_get_object(builder, "switch"));
    comboBox1 = GTK_WIDGET(gtk_builder_get_object(builder, "comboBoxGenitiques"));
    comboBox2 = GTK_WIDGET(gtk_builder_get_object(builder, "comboBoxTension"));
    comboBox3 = GTK_WIDGET(gtk_builder_get_object(builder, "comboBoxDiabete"));
    comboBox4 = GTK_WIDGET(gtk_builder_get_object(builder, "comboBoxCardiaque"));
    comboBox5 = GTK_WIDGET(gtk_builder_get_object(builder, "comboBoxPoumons"));
    scale1 = GTK_WIDGET(gtk_builder_get_object(builder, "scale1"));
    scale2 = GTK_WIDGET(gtk_builder_get_object(builder, "scale2"));
    textView1 = GTK_WIDGET(gtk_builder_get_object(builder, "TextView"));


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


gboolean macro_moveGrid(GtkImage *image) {

    gboolean returnVal = TRUE;

    GtkEventBox *boxSrc = GTK_EVENT_BOX (gtk_widget_get_parent(image));
    gint top, left;

    gtk_container_child_get(GTK_CONTAINER (gtk_widget_get_parent(GTK_WIDGET(boxSrc))),
                            GTK_WIDGET (boxSrc), "left-attach",
                            &left, "top-attach", &top, NULL);


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


static void macro_contaminateSingleIndiv(Individu *individu, Virus *virus) {
    gint result = g_list_index(individu->virusList, virus);
    if (result > -1) {
        individu->virusList = g_list_append(individu->virusList, virus);
        ///TODO :: Update abc value
        individu->abc += virus->damage;
    }
}

static void contaminate_indivCercleSingleVrs(gpointer *virus, gpointer *img) {
    guint i, j;
    guint left, top;
    GtkWidget *imgBox = gtk_widget_get_parent(GTK_WIDGET(img)),
            *grid = gtk_widget_get_parent(GTK_WIDGET(imgBox));

    gtk_container_child_get(GTK_CONTAINER(grid),
                            GTK_WIDGET(imgBox), "left-attach",
                            &left, "top-attach", &top, NULL);

    guint leftBorder = left - (((Virus *) virus)->cercleDeContam),
            rightBorder, topBorder, bottomBorder;
    {
        if (leftBorder < 0)
            leftBorder = 0;
        if (rightBorder > DEFAULT_MAX_ROWS)
            rightBorder = DEFAULT_MAX_ROWS;
        if (topBorder > 0)
            topBorder = 0;
        if (bottomBorder > DEFAULT_MAX_COLS)
            bottomBorder = DEFAULT_MAX_COLS;
    }

    for (i = leftBorder; i < rightBorder; i++) {
        for (j = topBorder; j < bottomBorder; j++) {
            if (i == left && j == top)
                continue;
            GtkWidget *box = (GtkWidget *) gtk_grid_get_child_at(GTK_GRID(grid), i, j);
            GtkWidget *image = ((GtkWidget *) gtk_bin_get_child(GTK_BIN(box)));
            if (image) {
                Individu *individu = (Individu *) g_object_get_data(G_OBJECT(image), DATA_KEY_INDIVIDU);

                macro_contaminateSingleIndiv(individu, (Virus *) virus);

            }
        }
    }
}


void iterateSingleIndividu(gpointer data, gpointer user_data) {

    G_STATIC_ASSERT_EXPR(GTK_IS_IMAGE(data));

   if (PLAY_MODE){


    Individu *individu = (Individu *) g_object_get_data(G_OBJECT(data), DATA_KEY_INDIVIDU);
    g_list_foreach(individu->virusList, (GFunc) contaminate_indivCercleSingleVrs, data);
    macro_moveGrid(data);
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


