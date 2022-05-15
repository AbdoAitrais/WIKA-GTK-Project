//
// Created by W0L1D on 4/29/2022.
//

#ifndef MAIN_C_CONTAMINATE_UTILS_H
#define MAIN_C_CONTAMINATE_UTILS_H

#include "UI_individu_macros.h"
#include "gobject_utils.h"
#include "show_functions.h"
#include "Statistics.h"
#include "tableauManip.h"

void AgePerson(Individu P, double *val) {
    switch (P.categorie) {
        case AGE_KIDS :
            *val += 0.5;
            break;
        case AGE_TEENS :
            *val += 1.0;
            break;
        case AGE_YOUTH :
            *val += 0.8;
            break;
        case AGE_ADULT :
            *val += 0.4;
            break;
        case AGE_OLD :
            *val += 0.1;
        default:
            *val = 0.0;
    }
}

void LaGenetique(Individu P, double *val) {
    switch (P.health.genetic) {
        case GENETIQUEMENT_FAIBLE:
            *val += 0.2;
            break;
        case GENETIQUEMENT_FRAGILE:
            *val += 0.4;
            break;
        case GENETIQUEMENT_MOYEN:
            *val += 0.6;
            break;
        case GENETIQUEMENT_FORT:
            *val += 1.0;
    }
}

void LaTension(Individu P, double *val) {
    switch (P.health.tension) {
        case ARTERIELLE_NORMAL:
            *val += 1.0;
            break;
        case ARTERIELLE_HYPERTENDU:
            *val += 0.5;
            break;
        case ARTERIELLE_HYPERTENSION_FORTE:
            *val += 0.1;
    }
}

void LaDiabete(Individu P, double *val) {
    switch (P.health.diabete) {
        case DIABETE_NORMAL:
            *val += 0.5;
            break;
        case DIABETE_MODERE:
            *val += 0.9;
            break;
        case DIABETE_AVANCE:
            *val += 0.1;
    }
}

void LaCardiaque(Individu P, double *val) {
    switch (P.health.cardiac) {
        case CARDIAQUE_NORMAL:
            *val += 0.6;
            break;
        case CARDIAQUE_MALADE:
            *val += 0.3;
            break;
        case CARDIAQUE_SEVERE:
            *val += 0.1;
    }
}


void LaPoumons(Individu P, double *val) {
    switch (P.health.poumons) {
        case POUMONS_SEIN:
            *val += 0.5;
            break;
        case POUMONS_MALADE:
            *val += 0.2;
            break;
        case POUMONS_GRAVE:
            *val += 0.05;
    }
}

void calcule_Virus_DamageTaken(gpointer virus,gpointer indiv) {
    ((Individu *) indiv)->damageTaken += ((gfloat) ((((Virus *) virus)->prctMortel / 100.0) * -1.0));
}

void calculate_damageTaken_per_Individu(Individu * indiv)
{
    GList * virusList = indiv->virusList;
    indiv->damageTaken = ((gfloat) 0.0);//initialization
    g_list_foreach(virusList,calcule_Virus_DamageTaken,indiv);
}


void damage_to_Virus(Individu * indiv)
{
    int i;
    GList * crt = indiv->virusList;
    GList * elemSupp = NULL;
    for (i = 0; i < indiv->virusesLifes.nbrElem; i++)
    {
        elemSupp = crt;
        if(indiv->virusesLifes.tab[i] <= 0)
        {
            suppPosition_TListe(&indiv->virusesLifes,i + 1);
            indiv->virusList = g_list_remove(indiv->virusList, elemSupp->data);
            calculate_damageTaken_per_Individu(indiv);
        }
        else
            indiv->virusesLifes.tab[i]--;
        if(!crt)
            break;
        crt = crt->next;
    }
}

gfloat calculerHPdeIndividu(Individu P) {
    double etat = 0.0;
    AgePerson(P, &etat);
    LaGenetique(P, &etat);
    LaDiabete(P, &etat);
    LaCardiaque(P, &etat);
    LaPoumons(P, &etat);
    LaTension(P, &etat);
    return ((float) etat);
}


/// association à chaque catégorie un réel
gfloat calculeVirusDamageField(Virus *v) {
    return ((gfloat) ((v->prctMortel / 100.0) * -1.0));
}

gint VirusExiste(Individu *individu, Virus *virus) {
    return g_list_find_custom(individu->virusList, virus->nom, (GCompareFunc) macro_find_compareVirusByName) ? 1 : 0;
}





static void macro_contaminateSingleIndiv(gpointer builder, Individu *individu, Virus *virus, Stats * stat) {

    if (!VirusExiste(individu, virus)) {

        individu->virusList = g_list_append(individu->virusList, virus);
        inserer_TListe(&individu->virusesLifes,virus->virusLife);
        individu->damageTaken += virus->damage;

        calculate_StatVirus_Individu(individu,stat);// update stats (add virus)
        show_Stats(builder,stat);
    }
}

void contaminate_indivCercleSingleVrs(gpointer virus, gpointer img) {
    gint i, j;
    guint left, top;
    GtkWidget *imgBox = gtk_widget_get_parent(GTK_WIDGET(img)),
            *grid = gtk_widget_get_parent(GTK_WIDGET(imgBox));

    gtk_container_child_get(GTK_CONTAINER(grid),
                            GTK_WIDGET(imgBox), "left-attach",
                            &left, "top-attach", &top, NULL);

    guint leftBorder = left - (((Virus *) virus)->cercleDeContam),
            rightBorder = left + (((Virus *) virus)->cercleDeContam),
            topBorder = top + (((Virus *) virus)->cercleDeContam),
            bottomBorder = top - (((Virus *) virus)->cercleDeContam);
    {
        if (leftBorder < 0)
            leftBorder = 0;
        if (rightBorder > DEFAULT_MAX_ROWS - 1)
            rightBorder = DEFAULT_MAX_ROWS - 1;
        if (bottomBorder < 0)
            bottomBorder = 0;
        if (topBorder > DEFAULT_MAX_COLS - 1)
            topBorder = DEFAULT_MAX_COLS - 1;
    }

    for (i = leftBorder; i < rightBorder; i++) {
        for (j = bottomBorder; j < topBorder; j++) {
            if (i == left && j == top)
                continue;
            g_assert(GTK_IS_GRID(grid));

            GtkWidget *box = (GtkWidget *) gtk_grid_get_child_at(GTK_GRID(grid), (gint) i, (gint) j);

            GtkWidget *image = ((GtkWidget *) gtk_bin_get_child(GTK_BIN(box)));
            if (image) {
                GtkBuilder * builder = getBuilder();
                Stats * stat = ((Stats *) g_object_get_data((GObject *) builder, DATA_KEY_STATS));
                Individu *individu = (Individu *) g_object_get_data(G_OBJECT(image), DATA_KEY_INDIVIDU);
                macro_contaminateSingleIndiv(builder, individu, (Virus *) virus, stat);



            }
        }
    }
}



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
    scale2 = GTK_WIDGET(gtk_builder_get_object(builder, "scale2"));


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

    gtk_style_context_add_class(gtk_widget_get_style_context(scale2), "scale");


    gtk_style_context_add_class(gtk_widget_get_style_context(button), "button2");
}


gboolean macro_moveGrid(GtkImage *image) {

    gboolean returnVal = TRUE;

    GtkEventBox *boxSrc = GTK_EVENT_BOX (gtk_widget_get_parent(GTK_WIDGET(image)));
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




void iterateSingleIndividu(gpointer data, gpointer builder) {

    Stats *stat = ((Stats *) g_object_get_data(builder, DATA_KEY_STATS));

    if (PLAY_MODE) {
        Individu *individu = (Individu *) g_object_get_data(G_OBJECT(data), DATA_KEY_INDIVIDU);

        if ((individu->hp <= 0) && (individu->hp != -99)) {
            GError * err = NULL;

            GdkPixbuf * gdkPixbuf = gdk_pixbuf_new_from_file("../pic/9ber50.png",&err);
            gtk_image_set_from_pixbuf(data,gdkPixbuf);

            stat->deaths++;
            show_Stats(builder,stat);
            individu->hp = -99;

        } else if (individu->hp > 0){
            macro_moveGrid(data);

            individu->hp += individu->damageTaken;
            damage_to_Virus(individu);

            g_list_foreach(individu->virusList, (GFunc) contaminate_indivCercleSingleVrs, data);
        }


    }
}

gboolean iterateIndividusList(gpointer builder) {
    GTK_IS_WIDGET(builder);
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, BUILDER_ID_MAIN_WINDOW));

    GList *pers = g_object_get_data(G_OBJECT(window), DATA_KEY_LIST_INDIVIDU);

    g_list_foreach(pers, iterateSingleIndividu, builder);

    g_timeout_add(PLAY_SPEED, iterateIndividusList, builder);

    return FALSE;
}



#endif //MAIN_C_CONTAMINATE_UTILS_H
