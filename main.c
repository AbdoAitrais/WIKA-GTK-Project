#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>

#include "macros.c"






typedef struct {
    gint	 baselinerow;	       /*The row to align the to the baseline
                                    when valign is GTK_ALIGN_BASELINE.Default value: 0*/

    gboolean columnhomogeneous	; /*If TRUE, the columns are all the same width.
                                        Default value:FALSE*/
    gint	 columnspacing	;         /*The amount of space between two consecutive columns.*/

    gboolean rowhomogeneous	 ;   ///If TRUE, the rows are all the same height.
    gint	 rowspacing  ;       ///he amount of space between two consecutive rows.

}GridProps;

GridProps set_grid_props(gboolean colhomo,gboolean rowhomo,gint colspace,gint rowspace)
{
    GridProps props;
    props.columnhomogeneous = colhomo;
    props.rowhomogeneous = rowhomo;
    props.columnspacing = colspace;
    props.rowspacing = rowspace;


    return props;
}



typedef struct {
    gint	height;	     ///The number of rows that a child spans.
    gint	left;	 ///The column number to attach the left side of the child to.
    gint	top;	 ///The row number to attach the top side of a child widget to.
    gint	width;       ///The number of columns that a child spans.
    GtkPositionType side; ///the side of sibling that child is positioned next to(macro_add_nextto_Grid())
}Tchildprops;

Tchildprops set_child_props()
{
    Tchildprops props;
    props.height = 1;
    props.left = 0;
    props.top = 0;
    props.width = 1;
    props.side = GTK_POS_TOP;


    return props;
}

/**********************************
*initialiser les propriétés du Grid.
*@param Grid utilise
*@param props propriétés du Grid
*******************************/

void macro_applyGrid(GtkGrid *Grid,GridProps props){
    if( props.rowspacing)
        gtk_grid_set_row_spacing ( Grid, props.rowspacing);
    if(props.columnhomogeneous)
        gtk_grid_set_column_homogeneous (Grid, props.columnhomogeneous);
    if(props.rowhomogeneous)
        gtk_grid_set_row_homogeneous(Grid, props.rowhomogeneous);
    if(props.columnspacing)
        gtk_grid_set_column_spacing(Grid, props.columnspacing);
    if(props.baselinerow)
        gtk_grid_set_baseline_row(Grid, props.baselinerow);


}
/**********************************
*Creer un  grid widget
*@param props propriétés du Grid
*******************************/
///create new grid widget
GtkWidget *macro_createGrid(GridProps props){
    GtkWidget *Grid;
    Grid=gtk_grid_new ();
    macro_applyGrid(GTK_GRID(Grid),props);
    return((GtkWidget *)Grid);
}



gint compare_virus(gpointer virus,gpointer nom)
{
    gchar * name = nom;
    Virus * v = virus;
    return g_strcmp0(v->nom,name);
}

Virus * get_virus_fromString(const gchar *nom,gpointer builder)
{
    GList * elem = g_list_find_custom(
            g_object_get_data(builder,DATA_KEY_LIST_VIRUS),nom,(GCompareFunc)compare_virus
    );

    return elem?((Virus *)elem->data):NULL;
}

void add_checkbutton_with_label_toBox(GtkWidget *box,Virus * virus)
{
    GtkWidget * checkButton = gtk_check_button_new_with_label(virus->nom);
    gtk_box_pack_start(GTK_BOX(box), checkButton, TRUE, TRUE, 0);
    gtk_widget_show(checkButton);
}

void inserer_virus(gpointer builder,Virus *virus)
{
    GtkWidget *buttonBox = GTK_WIDGET(gtk_builder_get_object (builder, "ButtonBoxVirus"));
    if(!get_virus_fromString(virus->nom,builder))
    {
        g_print("\nVirus from input : \n");
        afficher_virus(virus);
        inserer_data_GObject(builder,DATA_KEY_LIST_VIRUS,virus);
        add_checkbutton_with_label_toBox(buttonBox,virus);
    }
}

void remplir_virus(gpointer builder,gint Id,const gchar *nom,gfloat prctContam,gfloat prctMortel,guint cercleDeContam)
{
    Virus *virus = (Virus*) malloc(sizeof(Virus));
    virus->Id = Id;
    virus->nom = g_strdup(nom);
    virus->prctContam = prctContam;
    virus->prctMortel = prctMortel;
    virus->cercleDeContam = cercleDeContam;

    inserer_virus(builder,virus);
}

int id = 0;

void enregistrer_virus(GtkButton *button, gpointer builder)
{
    Virus *v = (Virus*) malloc(sizeof(Virus));

    GtkAdjustment *adjust1 = GTK_ADJUSTMENT(gtk_builder_get_object (builder, "adjust1"));
    GtkAdjustment *adjust2 = GTK_ADJUSTMENT(gtk_builder_get_object (builder, "adjust2"));
    GtkAdjustment *adjust3 = GTK_ADJUSTMENT(gtk_builder_get_object (builder, "adjust3"));
    GtkWidget *entryNomVirus = GTK_WIDGET(gtk_builder_get_object (builder, "entryNomVirus"));

    remplir_virus(builder,++id,gtk_entry_get_text(GTK_ENTRY(entryNomVirus)),
                  ((gfloat)gtk_adjustment_get_value (GTK_ADJUSTMENT(adjust1))),
                  ((gfloat)gtk_adjustment_get_value(GTK_ADJUSTMENT(adjust2))),
                  ((gint)gtk_adjustment_get_value (GTK_ADJUSTMENT(adjust3)))
                  );


    //inserer_virus(builder,v);


    //afficher_virus_enregistre(builder);

}

void get_selected_radioButtonLabel_fromGrp(GSList * List,gchar *label)
{
    GSList *crt = List;
    while (crt)
    {
        //GtkRadioButton *radio = crt->data;
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(crt->data)))
        {
//            g_print("gender from GSList = %s\n",gtk_button_get_label(GTK_BUTTON(crt->data)));
            g_stpcpy(label,gtk_button_get_label(GTK_BUTTON(crt->data)));
            //g_print("gender from GSList = %s\n",label);
            return ;
        }
        crt = crt->next;
    }
}

Genre get_genre_fromString(gchar *genre)
{
    if(!g_strcmp0(genre,"Homme"))
        return GENRE_MALE;
    if(!g_strcmp0(genre,"Femme"))
        return GENRE_FEMALE;
    return GENRE_UNSPECIFIED;
}

Genitique get_genetic_fromString(gchar *genetic)
{
    if(!g_strcmp0(genetic,"GENETIQUEMENT_FRAGILE"))
        return GENETIQUEMENT_FRAGILE;
    if(!g_strcmp0(genetic,"GENETIQUEMENT_MOYEN"))
        return GENETIQUEMENT_MOYEN;
    if(!g_strcmp0(genetic,"GENETIQUEMENT_FORT"))
        return GENETIQUEMENT_FORT;
    return GENETIQUEMENT_FAIBLE;
}

Tension get_tension_fromString(gchar *tension)
{
    if(!g_strcmp0(tension,"ARTERIELLE_HYPERTENDU"))
        return ARTERIELLE_HYPERTENDU;
    if(!g_strcmp0(tension,"ARTERIELLE_HYPERTENSION_FORTE"))
        return ARTERIELLE_HYPERTENSION_FORTE;
    return ARTERIELLE_NORMAL;
}

Diabete get_diabete_fromString(gchar *diabete)
{
    if(!g_strcmp0(diabete,"DIABETE_MODERE"))
        return DIABETE_MODERE;
    if(!g_strcmp0(diabete,"DIABETE_AVANCE"))
        return DIABETE_AVANCE;
    return DIABETE_NORMAL;
}

Cardiaque get_cardiac_fromString(gchar *cardiac)
{
    if(!g_strcmp0(cardiac,"CARDIAQUE_MALADE"))
        return CARDIAQUE_MALADE;
    if(!g_strcmp0(cardiac,"CARDIAQUE_SEVERE"))
        return CARDIAQUE_SEVERE;
    return CARDIAQUE_NORMAL;
}

Poumons get_poumons_fromString(gchar *poumons)
{
    if(!g_strcmp0(poumons,"POUMONS_MALADE"))
        return POUMONS_MALADE;
    if(!g_strcmp0(poumons,"POUMONS_GRAVE"))
        return POUMONS_GRAVE;
    return POUMONS_SEIN;
}

Age get_age_fromString(gchar *age)
{
    if(!g_strcmp0(age,"inférieur à 12 ans"))
        return AGE_KIDS;
    if(!g_strcmp0(age,"entre 12 et 25 ans"))
        return AGE_TEENS;
    if(!g_strcmp0(age,"entre 40 et 65 ans"))
        return AGE_ADULT;
    if(!g_strcmp0(age,"plus de 65 ans"))
        return AGE_OLD;
    return AGE_YOUTH;
}





GList *get_selected_checkButtons_fromButtonList(GList * buttonList,gpointer builder)
{
    GList *crt = buttonList;
    GList *VirusList = NULL;
    while (crt)
    {
        //GtkRadioButton *radio = crt->data;
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(crt->data)))
        {
            VirusList = g_list_append(VirusList,get_virus_fromString(
                    gtk_button_get_label(GTK_BUTTON(crt->data)),builder
            ));
        }
        crt = crt->next;
    }
    return ((GList *) VirusList);
}

//GList * get_virus_list_fromCheckButtons(GtkButtonBox * buttonBox,gpointer builder)
//{
//    GList * buttonList = gtk_container_get_children(GTK_CONTAINER(buttonBox));
//    GList * VirusList = get_selected_checkButtons_fromButtonList(buttonList,builder);
//    return ((GList *) VirusList);
//}

Individu *lire_Indiv(gpointer builder)
{
    Individu *individu = (Individu*)malloc(sizeof(Individu));
    GtkRadioButton * radioButton =  GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radioButtonHomme"));
    GSList * radioGrp = gtk_radio_button_get_group(radioButton);
    gchar * genre = (gchar*)malloc(sizeof(gchar));
    GtkWidget *comboBoxGen = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxGenitiques"));
    GtkWidget *comboBoxTens = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxTension"));
    GtkWidget *comboBoxDiab = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxDiabete"));
    GtkWidget *comboBoxCard = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxCardiaque"));
    GtkWidget *comboBoxPoum = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxPoumons"));
    GtkWidget *buttonBox = GTK_WIDGET(gtk_builder_get_object (builder, "ButtonBoxVirus"));
    GtkWidget *comboBoxAge = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxAge"));


    get_selected_radioButtonLabel_fromGrp(radioGrp,genre);
    //g_print("string gender = %s\n",genre);
    individu->gender = get_genre_fromString(genre);
    individu->health.genetic = get_genetic_fromString(
            gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBoxGen))
            );
    individu->health.tension = get_tension_fromString(
            gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBoxTens))
    );
    individu->health.diabete = get_diabete_fromString(
            gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBoxDiab))
    );
    individu->health.cardiac = get_cardiac_fromString(
            gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBoxCard))
    );
    individu->health.poumons = get_poumons_fromString(
            gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBoxPoum))
    );
    individu->VirusList = get_selected_checkButtons_fromButtonList(
            gtk_container_get_children(GTK_CONTAINER(buttonBox)),builder
    );
    individu->categorie = get_age_fromString(
            gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBoxAge))
    );

    return individu;
}

void create_backgroundBox(GtkGrid *grid,GtkBuilder *builder)
{
    for (int i = 0; i < MAXrow; ++i) {
        for (int j = 0; j < MAXcol; ++j) {
            GtkWidget *box = gtk_event_box_new();
            g_signal_connect (box, "button-press-event", (GCallback)add_individu, builder);

            gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(box), j, i, 1, 1);
            gtk_style_context_add_class(gtk_widget_get_style_context(box), "box");
        }
    }
}

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
    GtkWidget *grid = NULL;

    GtkBuilder *builder = NULL;
    GError *error = NULL;
    gchar *filename = NULL;
    GridProps gprops = set_grid_props(TRUE, TRUE, 0, 0);


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
    grid = macro_createGrid(gprops);
    create_backgroundBox(GTK_GRID(grid),builder);
    gtk_container_add(GTK_CONTAINER(ViewPort2),grid);


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

