
//
// Created by abdo on 3/8/2022.
//


#include "constants.h"
#include "by Abderrahman/structures.h"



    void AgePerson(Individu P,float *val)
{
     switch(P.categorie)
    {
        case AGE_KIDS :
            *val += 0.5;
            break;
        case AGE_TEENS :
            *val +=0.3;
            break;
        case AGE_YOUTH :
            *val+=0.7;
            break;
        case AGE_ADULT :
            *val++;
            break;
        case AGE_OLD :
            *val+=0.1;
        default: *val = 0.0;
    }

}
void LaGenetique(Individu P,float* val)
{
    switch(P.health.genetic)
    {
        case GENETIQUEMENT_FAIBLE:
            *val+=0.3;
            break;
        case GENETIQUEMENT_FRAGILE:
            *val+=0.4;
            break;
        case GENETIQUEMENT_MOYEN:
            *val+=0.6;
            break;
        case GENETIQUEMENT_FORT:
            *val++;
    }
}
void LaTension(Individu P,float *val)
{
    switch(P.health.tension)
    {
        case ARTERIELLE_NORMAL:
            *val+=0.5;
            break;
        case ARTERIELLE_HYPERTENDU:
            *val+=0.7;
            break;
        case ARTERIELLE_HYPERTENSION_FORTE:
            *val++;
    }
}
void LaDiabete(Individu P,float* val)
{
    switch(P.health.diabete)
    {
        case DIABETE_NORMAL:
            *val+=0.5;
            break;
        case DIABETE_MODERE:
            *val+=0.8;
            break;
        case DIABETE_AVANCE:
            *val++;
    }
}
void LaCardiaque(Individu P,float* val)
{
    switch(P.health.cardiac)
    {
        case CARDIAQUE_NORMAL:
            *val++;
            break;
        case CARDIAQUE_MALADE:
            *val+=0.4;
            break;
        case CARDIAQUE_SEVERE:
            *val+=0.1;
    }
}


void LaPoumons(Individu P,float* val)
{
    switch(P.health.poumons)
    {
        case POUMONS_SEIN:
            *val++;
            break;
        case POUMONS_MALADE:
            *val+=0.5;
            break;
        case POUMONS_GRAVE:
            *val+=0.2;
    }
}


float etatSanteIndivdu(Individu P)
{
    float etat = 0.0;
    AgePerson(P,&etat);
    LaGenetique(P,&etat);
    LaDiabete(P,&etat);
    LaCardiaque(P,&etat);
    LaPoumons(P,&etat);
    LaTension(P,&etat);
    return ((float)etat);
}


int includeCercle(GtkGrid* Tab,Coord pos,Virus V)
{
    int i,j;
        for(i=(pos.x-V.cercleDeContam);i<(pos.x+V.cercleDeContam);i++)/// on pacrourt la cercle de contamination de première ligne jusqu'à le dernière
        {
            if( i<0 || i>=MAXrow)///    if it is out of the table(grid)
                continue;
            for(j=(pos.y-V.cercleDeContam);j<(pos.y+V.cercleDeContam);j++)///on pacrourt la cercle de contamination de premier colonne jusqu'à la dernière
                {
                        if( j< 0 || j>=MAXcol)/// if it is out of the table(grid)
                                continue;
                          GtkWidget* image = gtk_grid_get_child_at(Tab,i,j);
                        Individu* PersonExiste = (Individu*)g_object_get_data(image,DATA_KEY_INDIVIDU);
                            if(PersonExiste)
                }
        }
}



/// check this out






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

//    printf("\ninit pos : top = %d left = %d\n", top, left);

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

//    printf("\nnew pos : top = %d left = %d. ", top, left);
    boxDst = gtk_grid_get_child_at(
            GTK_GRID(gtk_widget_get_parent(GTK_WIDGET(boxSrc))), left, top);
    g_assert(GTK_IS_EVENT_BOX(boxDst));
    if (boxDst && !(gtk_bin_get_child(GTK_BIN(boxDst))))// si la case ne contient pas bnadem on ajoute
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
//        printf("is valid\n\n");
        g_object_ref(child);
        gtk_container_remove(GTK_CONTAINER(boxSrc), child);
        ///child->pos.x = top;
        ///child->pos.y=left;
        gtk_container_add(GTK_CONTAINER(boxDst), child);
        g_object_unref(child);
    }
    return returnVal;

}




Individu *lire_Indiv(gpointer builder);



void iterateSingleIndividu( gpointer data, gpointer user_data) {
    if (PLAY_MODE)
        macro_moveGrid(data);
}



gboolean iterateIndividusList(gpointer data) {
    GTK_IS_WIDGET(data);

    GList *pers = g_object_get_data(data, DATA_KEY_LIST_INDIVIDU);

    g_list_foreach(pers, iterateSingleIndividu, NULL);


    // TODO :: test if the play mode is started
    //  GET PLAY MODE BOOLEAN FROM TOOLBAR
    if (PLAY_MODE)
        g_timeout_add(600, iterateIndividusList, data);

    return FALSE;
}


