//
// Created by W0L1D on 4/29/2022.
//

#ifndef MAIN_C_CONTAMINATE_UTILS_H
#define MAIN_C_CONTAMINATE_UTILS_H

#include "../by Abderrahman/UI_individu_macros.h"
#include "../by Abderrahman/gobject_utils.h"
#include "../by Abderrahman/show_functions.h"
#include "../by Abderrahman/tableauManip.h"


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

float calculerHPdeIndividu(Individu P) {
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





static void macro_contaminateSingleIndiv(Individu *individu, Virus *virus) {

    if (!VirusExiste(individu, virus)) {
        individu->virusList = g_list_append(individu->virusList, virus);
        inserer_TListe(&individu->virusesLifes,virus->virusLife);
        ///TODO :: Update damageTaken value
        individu->damageTaken += virus->damage;
    }
}

static void contaminate_indivCercleSingleVrs(gpointer *virus, gpointer *img) {
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

                Individu *individu = (Individu *) g_object_get_data(G_OBJECT(image), DATA_KEY_INDIVIDU);
                macro_contaminateSingleIndiv(individu, (Virus *) virus);


            }
        }
    }
}


#endif //MAIN_C_CONTAMINATE_UTILS_H
