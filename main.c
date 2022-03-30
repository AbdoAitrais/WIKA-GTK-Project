#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>
#include <time.h>

#include "macros.c"

#define MAXrow 70
#define MAXcol 40





typedef struct {
    gint	 baselinerow;	       /*The row to align the to the baseline
                                    when valign is GTK_ALIGN_BASELINE.Default value: 0*/

    gboolean columnhomogeneous	; /*If TRUE, the columns are all the same width.
                                        Default value:FALSE*/
    gint	 columnspacing	;         /*The amount of space between two consecutive columns.*/

    gboolean rowhomogeneous	 ;   ///If TRUE, the rows are all the same height.
    gint	 rowspacing  ;       ///he amount of space between two consecutive rows.

}Gridprops;

Gridprops set_grid_props(gboolean colhomo,gboolean rowhomo,gint colspace,gint rowspace)
{
    Gridprops props;
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

void macro_applyGrid(GtkGrid *Grid,Gridprops props){
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
GtkWidget *macro_createGrid(Gridprops props){
    GtkWidget *Grid;
    Grid=gtk_grid_new ();
    macro_applyGrid(GTK_GRID(Grid),props);
    return((GtkWidget *)Grid);
}



void loadCSS(GtkWidget *window)
{
    GFile *css_gFile = g_file_new_for_path("style.css");
    GtkCssProvider *cssProvider = gtk_css_provider_new();

    gtk_css_provider_load_from_file(cssProvider, css_gFile, 0);

    gtk_style_context_add_provider_for_screen(gtk_widget_get_screen(window),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
}






void afficher_virus(Virus *vir)
{
    printf("%d\n",vir->Id);
    printf("%s\n",vir->nom);
    printf("%f\n",vir->prctContam);
    printf("%f\n",vir->prctMortel);
    printf("%d\n",vir->cercleDeContam);
}

void afficher_virus_enregistre(GObject *object)
{
    GList *a = ((GList *)g_object_get_data(object,"listVirus"));
    Virus * vir = ((Virus *) a->data);
    afficher_virus(vir);
}

void inserer_data_GObject(GObject * object,gchar * key,gpointer data)
{
    GList * l = g_object_get_data(object,key);

    l = g_list_append(l,data);

    g_object_set_data(object,"listVirus",l);

}

int id = 0;

void enregistrer_virus(GtkButton *button, gpointer builder)
{
    Virus *v = (Virus*) malloc(sizeof(Virus));

    GtkAdjustment *adjust1 = GTK_ADJUSTMENT(gtk_builder_get_object (builder, "adjust1"));
    GtkAdjustment *adjust2 = GTK_ADJUSTMENT(gtk_builder_get_object (builder, "adjust2"));
    GtkAdjustment *adjust3 = GTK_ADJUSTMENT(gtk_builder_get_object (builder, "adjust3"));
    GtkWidget *entryNomVirus = GTK_WIDGET(gtk_builder_get_object (builder, "entryNomVirus"));

    v->Id = ++id;
    v->prctContam = ((gfloat)gtk_adjustment_get_value (GTK_ADJUSTMENT(adjust1)));
    v->prctMortel = ((gfloat)gtk_adjustment_get_value(GTK_ADJUSTMENT(adjust2)));
    v->cercleDeContam = ((gint)gtk_adjustment_get_value (GTK_ADJUSTMENT(adjust3)));
    v->nom = g_strdup(gtk_entry_get_text(GTK_ENTRY(entryNomVirus)));

    g_print("\nVirus from input : \n");
    afficher_virus(v);
    inserer_data_GObject(builder,"listVirus",v);



    afficher_virus_enregistre(builder);

}

void create_backgroundBox(GtkGrid *grid)
{
    for (int i = 0; i < MAXrow; ++i) {
        for (int j = 0; j < MAXcol; ++j) {
            GtkWidget *box = gtk_event_box_new();
            g_signal_connect (box, "button-press-event", (GCallback)add_individu, NULL);

            gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(box), j, i, 1, 1);
            gtk_style_context_add_class(gtk_widget_get_style_context(box), "box");
        }
    }
}
void enregistrer_add_individu(GtkGrid *grid,gchar *path)
{
    for (int i = 0; i < MAXrow; ++i) {
        for (int j = 0; j < MAXcol; ++j) {

            g_signal_connect (gtk_grid_get_child_at(grid, i, j), "button-press-event", (GCallback)add_individu, path);
        }
    }
}

int main(int argc, char *argv [])
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
      GtkWidget *comboBox6 = NULL;
      GtkWidget *comboBox7 = NULL;
      GtkWidget *textView1 = NULL;
      GtkWidget *textView2 = NULL;
      GtkWidget *textView3 = NULL;
      GtkWidget *scale1 = NULL;
      GtkWidget *scale2 = NULL;
      GtkWidget *button = NULL;
      GtkWidget *button1 = NULL;
      GtkWidget *SonBox = NULL;
        GtkWidget *grid = NULL;
    Virus *v = NULL;


      GtkBuilder *builder = NULL;
      GError *error = NULL;
      gchar *filename = NULL;
      Gridprops gprops = set_grid_props(TRUE, TRUE, 0, 0);

      ButtonProps *props = set_button_props(NULL,TRUE,TRUE,GTK_POS_TOP,-1,-1, NULL,
                                 GTK_RELIEF_NORMAL,"system-users-symbolic",FALSE);
      /* Initialisation de la librairie Gtk. */
      gtk_init(&argc, &argv);

      /* Ouverture du fichier Glade de la fenêtre principale */
      builder = gtk_builder_new();

      /* Création du chemin complet pour accéder au fichier test.glade. */
      /* g_build_filename(); construit le chemin complet en fonction du système */
      /* d'exploitation. ( / pour Linux et \ pour Windows) */
      filename =  g_build_filename ("Interface2.glade", NULL);

          /* Chargement du fichier test.glade. */
      gtk_builder_add_from_file (builder, filename, &error);
      g_free (filename);
      if (error)
      {
        gint code = error->code;
        g_printerr("%s\n", error->message);
        g_error_free (error);
        return code;
      }

    /* Récupération du pointeur de la fenêtre principale */
    fenetre_principale = GTK_WIDGET(gtk_builder_get_object (builder, "MainWindow"));
    menu = GTK_WIDGET(gtk_builder_get_object (builder, "MenuBar"));
    //grid = GTK_WIDGET(gtk_builder_get_object (builder, "GameGrid"));
    button = GTK_WIDGET(gtk_builder_get_object (builder, "subutton2"));
    button1 = GTK_WIDGET(gtk_builder_get_object (builder, "start_button"));
    stack = GTK_WIDGET(gtk_builder_get_object (builder, "stack"));
    switcher = GTK_WIDGET(gtk_builder_get_object (builder, "switch"));
    comboBox1 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxGenitiques"));
    comboBox2 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxTension"));
    comboBox3 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxDiabete"));
    comboBox4 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxCardiaque"));
    comboBox5 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxPoumons"));
    comboBox6 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxVirus"));

    scale1 = GTK_WIDGET(gtk_builder_get_object (builder, "scale1"));
    scale2 = GTK_WIDGET(gtk_builder_get_object (builder, "scale2"));
    textView1 = GTK_WIDGET(gtk_builder_get_object (builder, "TextView"));

    //SonBox = GTK_WIDGET(gtk_builder_get_object (builder, "SonBox"));
    GtkWidget *ViewPort2 = GTK_WIDGET(gtk_builder_get_object (builder, "ViewPort2"));

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
    gtk_style_context_add_class(gtk_widget_get_style_context(comboBox6), "comboBox");
    gtk_style_context_add_class(gtk_widget_get_style_context(scale1), "scale");
    gtk_style_context_add_class(gtk_widget_get_style_context(scale2), "scale");
    gtk_style_context_add_class(gtk_widget_get_style_context(textView1), "textView");
    //gtk_style_context_add_class(gtk_widget_get_style_context(grid), "grid");
    gtk_style_context_add_class(gtk_widget_get_style_context(button), "button2");


    g_printerr("\nReached me\n");

    grid = macro_createGrid(gprops);
    create_backgroundBox(GTK_GRID(grid));
    //gtk_box_pack_start(GTK_BOX(SonBox),grid,TRUE,TRUE,0);
    gtk_container_add(GTK_CONTAINER(ViewPort2),grid);

/*
    GtkWidget *image = gtk_image_new_from_file ("person.png");
    GtkWidget *eBox = gtk_grid_get_child_at(GTK_GRID(grid),0,0);
    gtk_container_add(GTK_CONTAINER(eBox),image);


*/

       // create_background(GTK_GRID(grid),props);
    /* Affectation du signal "destroy" à la fonction gtk_main_quit(); pour la */
    /* fermeture de la fenêtre. */
    g_signal_connect (G_OBJECT (fenetre_principale), "destroy", (GCallback)gtk_main_quit, NULL);
    g_signal_connect (GTK_BUTTON(button), "clicked", (GCallback)enregistrer_virus, builder);
 //   enregistrer_add_individu(GTK_GRID(grid),"person.png");


    /* Affichage de la fenêtre principale. */
    gtk_widget_show_all (fenetre_principale);

      gtk_main();



      return 0;
}

