//
// Created by abdo on 4/28/2022.
//

#ifndef MAIN_C_INIT_ENV_MACRO_H
#define MAIN_C_INIT_ENV_MACRO_H

#include "UI_individu_macros.h"
#include "contaminate_utils.h"
#include "Statistics.h"
#include "save_status.h"


typedef struct {
    gint baselinerow;           /*The row to align the to the baseline
                                    when valign is GTK_ALIGN_BASELINE.Default value: 0*/
    gboolean columnhomogeneous; /*If TRUE, the columns are all the same width.
                                        Default value:FALSE*/
    gint columnspacing;         /*The amount of space between two consecutive columns.*/
    gboolean rowhomogeneous;   ///If TRUE, the rows are all the same height.
    gint rowspacing;       ///he amount of space between two consecutive rows.

} GridProps;

GridProps set_grid_props(gboolean colhomo, gboolean rowhomo, gint colspace, gint rowspace) {
    GridProps props;
    props.columnhomogeneous = colhomo;
    props.rowhomogeneous = rowhomo;
    props.columnspacing = colspace;
    props.rowspacing = rowspace;

    return props;
}


/**********************************
*initialiser les propriétés du Grid.
*@param Grid utilise
*@param props propriétés du Grid
*******************************/
void macro_applyGrid(GtkGrid *Grid, GridProps props) {
    if (props.rowspacing)
        gtk_grid_set_row_spacing(Grid, props.rowspacing);
    if (props.columnhomogeneous)
        gtk_grid_set_column_homogeneous(Grid, props.columnhomogeneous);
    if (props.rowhomogeneous)
        gtk_grid_set_row_homogeneous(Grid, props.rowhomogeneous);
    if (props.columnspacing)
        gtk_grid_set_column_spacing(Grid, props.columnspacing);
    if (props.baselinerow)
        gtk_grid_set_baseline_row(Grid, props.baselinerow);


}
/**********************************
*Creer un  grid widget
*@param props propriétés du Grid
*******************************/
///create new grid widget
GtkWidget *macro_createGrid(GridProps props) {
    GtkWidget *Grid;
    Grid = gtk_grid_new();
    macro_applyGrid(GTK_GRID(Grid), props);
    return ((GtkWidget *) Grid);
}

/**
        Added by ismail
**/

GtkWidget *choixImage(Individu *indiv) {
    GtkWidget *image;
    if (indiv->gender == GENRE_MALE) {
        if (indiv->categorie == AGE_OLD)
            image = gtk_image_new_from_file("../pic/haj2.png");
        else if(indiv->categorie == AGE_KIDS)
            image = gtk_image_new_from_file("../pic/babyB3.png");
        else
            image = gtk_image_new_from_file("../pic/nta2.png");
    } else {

            if(indiv->categorie == AGE_OLD)
                image = gtk_image_new_from_file("../pic/haja2.png");
            else if(indiv->categorie == AGE_KIDS)
                image = gtk_image_new_from_file("../pic/littleG.png");
            else
                image = gtk_image_new_from_file("../pic/nti2.png");
    }
    return (GtkWidget *) image;

}

//Individu * get_Individu_from_Interface(GtkEventBox * eventBox)
//{
//    GtkWidget * image = gtk_bin_get_child(GTK_BIN(eventBox));
//    return ((Individu *) g_object_get_data(G_OBJECT(image),DATA_KEY_INDIVIDU));
//}
//
//gboolean show_Individu (GtkWidget *eventBox, GdkEvent *event, gpointer builder)
//{
//    //afficher_individu(get_Individu_from_Interface(GTK_EVENT_BOX(eventBox)));
//    gchar msg[100];
//    Individu * individu = get_Individu_from_Interface(GTK_EVENT_BOX(eventBox));
//    g_strdup_printf(msg,"individu gender = %d\nindividu genetic = %d\n",individu->gender,individu->health.genetic);
//    macro_dialog(msg);
//    return TRUE;
//}








gboolean add_individu(GtkWidget *widget, GdkEvent *event, gpointer builder) {
    if (!ADD_INDIVIDU_MODE)
        return FALSE;

    GtkWidget *img;
    if ((img = gtk_bin_get_child((GTK_BIN(widget))))) {

        Individu *individu = (Individu *) g_object_get_data(G_OBJECT(img), DATA_KEY_INDIVIDU);
        //afficher_individu(individu);
        show_Individu_to_Interface(individu);



        return TRUE;
    }

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "MainWindow"));
    /** added by ismail **/
    Individu *indiv = lire_Indiv(builder);
    indiv->hp = calculerHPdeIndividu(*indiv);

    calculate_damageTaken_per_Individu(indiv);
    //getting the right image for each type of person

    GtkWidget *image = ((GtkWidget *) choixImage(indiv));
    gtk_container_add(GTK_CONTAINER (widget), image);
    gtk_widget_show(image);
    gint left, top;
    gtk_container_child_get(GTK_CONTAINER(gtk_widget_get_parent(GTK_WIDGET(widget))),
                            GTK_WIDGET(widget), "left-attach",
                            &left, "top-attach", &top, NULL);
    g_print("\nadded image  top = %d, left = %d.\n", top, left);



    g_object_set_data((GObject *) image, DATA_KEY_INDIVIDU, indiv);
    inserer_data_GObject(G_OBJECT(window), DATA_KEY_LIST_INDIVIDU, image);
    // afficher_individu(indiv);// juste pour savoir est-ce que les calcules sont bien fait

    Stats *stat = ((Stats *) g_object_get_data(builder, DATA_KEY_STATS));
    calculate_Stats_Individu(g_object_get_data(G_OBJECT(window), DATA_KEY_LIST_INDIVIDU), indiv, stat);

    afficher_Stats(stat);
    show_Stats(builder, stat);



    return FALSE;
}

void iterate_initSingleIndiv(gpointer indiv_pointer, gpointer grid_pointer) {
    Individu *individu = indiv_pointer;
    GtkWidget *grid = grid_pointer;
    g_assert(G_IS_OBJECT(grid));
    GtkWidget *window = g_object_get_data(G_OBJECT(grid), BUILDER_ID_MAIN_WINDOW);

    /// create associated image
    GtkWidget *img = choixImage(individu);
    g_object_set_data(G_OBJECT(img), DATA_KEY_INDIVIDU, individu);

    g_assert(G_IS_OBJECT(window));
    ///save new list
    inserer_data_GObject(G_OBJECT(window), DATA_KEY_LIST_INDIVIDU, img);
    g_assert(G_IS_OBJECT(img));

    /// show image in the grid
    GtkWidget *box = gtk_grid_get_child_at(GTK_GRID(grid), individu->pos.x, individu->pos.y);

    g_assert(GTK_IS_EVENT_BOX(box));


    gtk_container_add(GTK_CONTAINER(box), img);

    gtk_widget_show(img);
}

void macro_initIndivsList(GtkWidget *grid, GList *indivs, GtkWidget *window) {
    g_object_set_data(G_OBJECT(grid), BUILDER_ID_MAIN_WINDOW, window);

    g_list_foreach(indivs, iterate_initSingleIndiv, grid);

//    g_object_set_data(G_OBJECT(grid), BUILDER_ID_MAIN_WINDOW, NULL);

}

void create_backgroundBox(GtkGrid *grid, GtkBuilder *builder) {
    for (int i = 0; i < DEFAULT_MAX_ROWS; ++i) {
        for (int j = 0; j < DEFAULT_MAX_COLS; ++j) {

            GtkWidget *box = gtk_event_box_new();
            g_signal_connect (box, "button-press-event", (GCallback) add_individu, builder);
            gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(box), j, i, 1, 1);
            gtk_style_context_add_class(gtk_widget_get_style_context(box), "box");
        }
    }
}

void init_background(GtkWidget *ViewPort2,gpointer builder)
{
    GtkWidget *grid = NULL;
    GridProps gprops = set_grid_props(TRUE, TRUE, 0, 0);
    grid = macro_createGrid(gprops);
    create_backgroundBox(GTK_GRID(grid), builder);
    gtk_container_add(GTK_CONTAINER(ViewPort2), grid);

    GtkWidget *window = gtk_builder_get_object(GTK_BUILDER(builder), BUILDER_ID_MAIN_WINDOW);
    EnvInfo *envInfo = macro_parseStatus("test.wika");

    macro_initIndivsList(grid, envInfo->indivs, window);


}



#endif //MAIN_C_INIT_ENV_MACRO_H
