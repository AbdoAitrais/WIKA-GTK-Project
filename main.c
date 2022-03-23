#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>
#include <time.h>
#include "macros.c"
#define MAXrow 40
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
/**********************************
*ajouter un widget au grid
*@param Grid utilise
*@param widget a ajouter
*@param props propriétés du widget
*******************************/

void macro_add_widgetGrid(GtkWidget *Grid,GtkWidget *child,Tchildprops prop){

    gtk_grid_attach (GTK_GRID(Grid),child,prop.left,prop.top,prop.width,prop.height);
    ///the position of child is determined by left and top .
    /// The number of “cells” that child will occupy is determined by width and height .
}
/**********************************
*ajouter un widget au grid on se basant sur
*la position d'un autre child dans le Grid
*@param Grid utilise
*@param widget a ajouter
*@param widget qui existe deja
*@param props propriétés du widget a ajouter
*******************************/

void macro_add_nextto_Grid(GtkWidget *Grid,GtkWidget *child,GtkWidget *sibling,Tchildprops prop)
{   ///add a widget to the grid next to another child
    gtk_grid_attach_next_to (GTK_GRID(Grid),child,sibling,prop.side,prop.width,prop.height);
    ///he widget is placed next to sibling , on the side determined by side .
    ///When sibling is NULL, the widget is placed in row or column at the end indicated by side .

}

static void deplacer_button (GtkButton *widget,gpointer   data)
{
    g_print ("Hello World, I'm button 2\n");
    GtkWidget *grid = gtk_widget_get_parent(GTK_WIDGET(widget));
    gtk_container_remove(GTK_CONTAINER(grid), GTK_WIDGET(widget));
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(widget), 0, 1, 1, 1);

    g_print ("Hello World, I'm button 2\n");
}


/*int main(int argc, char **argv ) {

    gtk_init(&argc,&argv);

    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    ButtonProps *props = set_button_props();
    Gridprops gprops = set_grid_props(TRUE,TRUE,10,10);
    Tchildprops chprops1;
    Tchildprops chprops2;
    Tchildprops chprops3;
    chprops1.height = 1;
    chprops1.left = 0;
    chprops1.top = 1;
    chprops1.width = 1;
    chprops1.side = GTK_POS_TOP;

    chprops2.height = 1;
    chprops2.left = 0;
    chprops2.top = 0;
    chprops2.width = 1;
    chprops2.side = GTK_POS_TOP;

    chprops3.height = 1;
    chprops3.left = 0;
    chprops3.top = 0;
    chprops3.width = 1;
    chprops3.side = GTK_POS_TOP;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    grid = macro_createGrid(gprops);
    button1 = macro_createButton(props);
    button2 = macro_createButton(props);
    button3 = macro_createButton(props);

    macro_add_widgetGrid(grid,button1,chprops1);
    macro_add_nextto_Grid(grid,button2,button1,chprops2);
    gtk_grid_insert_column(GTK_GRID(grid),0);
    gtk_grid_insert_row(GTK_GRID(grid),0);

    macro_add_widgetGrid(grid,button3,chprops3);




    gtk_container_add(GTK_CONTAINER(window),grid);
    gtk_widget_show_all(window);
    g_signal_connect(button3,"clicked", G_CALLBACK(deplacer_button),NULL);
    g_signal_connect(window , "destroy", G_CALLBACK(gtk_main_quit) , NULL);


    gtk_main();
    return 0;
}*/

void create_background(GtkGrid *grid,ButtonProps *props)
{
    for (int i = 0; i < 45; ++i) {
        for (int j = 0; j < 30; ++j) {
            GtkWidget *button = macro_createButton(props);
            gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(button), i, j, 1, 1);
            gtk_style_context_add_class(gtk_widget_get_style_context(button), "box");
        }
    }
}

void create_backgroundBox(GtkGrid *grid)
{
    for (int i = 0; i < MAXrow; ++i) {
        for (int j = 0; j < MAXcol; ++j) {
            GtkWidget *box = gtk_event_box_new();
            gtk_event_box_set_above_child(GTK_EVENT_BOX(box), TRUE);
            gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(box), i, j, 1, 1);
            gtk_style_context_add_class(gtk_widget_get_style_context(box), "box");
        }
    }
}


static void
print_hello1(GtkWidget *widget,
             gpointer data) {
    g_print("Hello World, I'm button 1\n");
}
//"face-cool-symbolic"
/*
int main(int argc, char **argv )
{
    gtk_init(&argc, &argv);
    GtkWidget *menu_bar;
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *image = gtk_image_new_from_file("person.png");
    GtkWidget *image1 = gtk_image_new_from_file("person.png");
    GtkWidget *image2 = gtk_image_new_from_file("person.png");
    GtkWidget *image3 = gtk_image_new_from_file("person.png");
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget *boxv = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    GtkWidget *boxv1 = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    ButtonProps *props = set_button_props(NULL,TRUE,TRUE,GTK_POS_TOP,30,30,image,
                                          GTK_RELIEF_NORMAL,NULL,FALSE);
    Gridprops gprops = set_grid_props(TRUE, TRUE, 0, 0);
    GtkWidget *button;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *buttonc1;
    GtkWidget *buttonc2;
    GtkWidget *buttonc3;
    CheckButtonProps propscheck;
    RadioButtonProps propsradio;
    RadioButtonProps propsradio2;
    ToggleButtonProps propstoggle ;
    BoxProps *boxProps;

    propstoggle.active = FALSE;
    propstoggle.ButtonProps = set_button_props("Some",TRUE,FALSE,GTK_POS_TOP,80,20, NULL,
                                                       GTK_RELIEF_NORMAL,NULL,FALSE);;

    propscheck.props = propstoggle;





    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    grid = macro_createGrid(gprops);

    create_background(GTK_GRID(grid),props);
    button = gtk_grid_get_child_at(GTK_GRID(grid),5,5);
    props = set_button_props("Add",TRUE,TRUE,GTK_POS_TOP,100,20, NULL,
                             GTK_RELIEF_NORMAL,NULL,FALSE);
    button1 = macro_createButton(props);
    button2 = macro_createButton(props);
    button3 = macro_createButton(props);


    buttonc2 = gtk_check_button_new_with_label("some");
    buttonc3 = gtk_check_button_new_with_label("good");

    buttonc1 = gtk_check_button_new_with_label("View");

    gtk_box_pack_start(GTK_BOX(boxv),button1,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(boxv),button2,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(boxv),button3,TRUE,TRUE,0);
    gtk_box_pack_end(GTK_BOX(boxv),buttonc1,TRUE,TRUE,0);
    gtk_box_pack_end(GTK_BOX(boxv),buttonc2,TRUE,TRUE,0);
    gtk_box_pack_end(GTK_BOX(boxv),buttonc3,TRUE,TRUE,0);
    props = set_button_props(NULL,TRUE,TRUE,GTK_POS_TOP,50,50, image,
                             GTK_RELIEF_NORMAL,NULL,FALSE);

    gtk_box_pack_start(GTK_BOX(box),grid,TRUE,TRUE,0);
    gtk_box_pack_end(GTK_BOX(box),boxv,TRUE,TRUE,0);


    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);
    ///g_signal_connect(button, "clicked", G_CALLBACK(deplacer_button), NULL);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    gtk_main();
    return 0;
}
*/
void loadCSS(GtkWidget *window)
{
    GFile *css_gFile = g_file_new_for_path("style.css");
    GtkCssProvider *cssProvider = gtk_css_provider_new();

    gtk_css_provider_load_from_file(cssProvider, css_gFile, 0);

    gtk_style_context_add_provider_for_screen(gtk_widget_get_screen(window),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void macro_moveGrid (GtkEventBox *boxSrc)
{

    srand(time(NULL));
    GtkWidget *child = gtk_bin_get_child(GTK_BIN(boxSrc));
    gint pas  = (gint)(rand()%4);
    gint left,top;
    gtk_container_child_get(GTK_CONTAINER(boxSrc), GTK_WIDGET(boxSrc), "left-attach", &left,
                            "top-attach", &top);
    /*
				    0
				    ^
				1<     >3
				    v
				    2
    */

    switch(pas)
    {
    	case 0:
    	{
    		if(!top-1)
    			return;
    		top--;
    		break;
    	}
    	case 1:
    	{
    		if(!left-1)
    			return;
    		left--;
    		break;
    	}
    	case 2:
    	{
    		if(top+1 == MAXrow)
    			return;
    		top++;
    		break;
    	}
    	case 3:
    	{
    		if(left+1 == MAXcol)
    			return;
    		left++;
            break;
    	}
        default:
            exit(0);
      }
    GtkWidget *boxDst = gtk_grid_get_child_at(
            GTK_GRID(gtk_widget_get_parent(GTK_WIDGET(boxSrc))),left,top);
    if(!boxDst && gtk_bin_get_child(GTK_BIN(boxDst)))// si la case ne contient pas bnadem on ajoute
    {
        /*
         * GObject is a reference counted type. Reference counting is a form of garbage collection.
         * Every time you take ownership of an object instance, you must acquire a reference to it—using g_object_ref().
         * Once you drop the ownership of that instance, you must release the reference you acquired—using g_object_unref().

         * If you get an object back from a function, and the documentation says “transfer full” or “newly allocated” or “a new reference”,
         * then you need to call g_object_unref() to release the reference you’re given.
         * The API reference will always tell you if you’re dealing with something you own, or just a pointer to something that
         * is owned by something else.
         */
	    g_object_ref(child);
	    gtk_container_remove(GTK_CONTAINER(boxSrc), child);
	    ///child->pos.x = top;
        ///child->pos.y=left;
	    gtk_container_add(GTK_CONTAINER(boxDst),child);
	    g_object_unref(child);
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
      GtkWidget *SonBox = NULL;
        GtkWidget *grid = NULL;

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
      filename =  g_build_filename ("C:\\msys64\\mingw64\\bin\\Interface2.glade", NULL);

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
    stack = GTK_WIDGET(gtk_builder_get_object (builder, "stack"));
    switcher = GTK_WIDGET(gtk_builder_get_object (builder, "switch"));
    comboBox1 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBox7"));
    comboBox2 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBox8"));
    comboBox3 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBox9"));
    comboBox4 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBox10"));
    comboBox5 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBox11"));
    comboBox6 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBox12"));
    comboBox7 = GTK_WIDGET(gtk_builder_get_object (builder, "comboBox13"));
    scale1 = GTK_WIDGET(gtk_builder_get_object (builder, "scale1"));
    scale2 = GTK_WIDGET(gtk_builder_get_object (builder, "scale2"));
    textView1 = GTK_WIDGET(gtk_builder_get_object (builder, "TextView"));
    SonBox = GTK_WIDGET(gtk_builder_get_object (builder, "SonBox"));



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
    gtk_style_context_add_class(gtk_widget_get_style_context(comboBox7), "comboBox");
    gtk_style_context_add_class(gtk_widget_get_style_context(scale1), "scale");
    gtk_style_context_add_class(gtk_widget_get_style_context(scale2), "scale");
    gtk_style_context_add_class(gtk_widget_get_style_context(textView1), "textView");
    //gtk_style_context_add_class(gtk_widget_get_style_context(grid), "grid");
    gtk_style_context_add_class(gtk_widget_get_style_context(button), "button2");


    grid = macro_createGrid(gprops);
    create_backgroundBox(GTK_GRID(grid));
    gtk_box_pack_start(GTK_BOX(SonBox),grid,TRUE,TRUE,0);



    GtkWidget *image = gtk_image_new_from_file ("facebook.png");
    GtkWidget *eBox = gtk_grid_get_child_at(GTK_GRID(grid),2,2);
    //gtk_container_add(GTK_CONTAINER(eBox),image);

        macro_moveGrid(GTK_EVENT_BOX(eBox));

       // create_background(GTK_GRID(grid),props);
    /* Affectation du signal "destroy" à la fonction gtk_main_quit(); pour la */
    /* fermeture de la fenêtre. */
    g_signal_connect (G_OBJECT (fenetre_principale), "destroy", (GCallback)gtk_main_quit, NULL);

    /* Affichage de la fenêtre principale. */
    gtk_widget_show_all (fenetre_principale);

      gtk_main();

      return 0;
}

