//
// Created by W0L1D on 4/29/2022.
//

#ifndef MAIN_C_CONTAMINATE_UTILS_H
#define MAIN_C_CONTAMINATE_UTILS_H

#include "../by Abderrahman/UI_individu_macros.h"
#include "../constants.h"
#include "../by Abderrahman/gobject_utils.h"

void AgePerson(Individu P, double *val) {
    switch (P.categorie) {
        case AGE_KIDS :
            *val += 0.5;
            break;
        case AGE_TEENS :
            *val ++;
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
            *val++;
    }
}

void LaTension(Individu P, double *val) {
    switch (P.health.tension) {
        case ARTERIELLE_NORMAL:
            *val ++;
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
            *val += 0.7;
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

// divise les catégories de virus en 5 selon leurs taux de mortalités
//gint categorieDeVirus(Virus *V) {
//    if (V->prctMortel >= 1 && V->prctMortel < 25) return (int) 1;
//    if (V->prctMortel >= 25 && V->prctMortel < 50) return (int) 2;
//    if (V->prctMortel >= 50 && V->prctMortel < 75) return (int) 3;
//    if (V->prctMortel >= 75 && V->prctMortel < 99) return (int) 4;
//    if (V->prctMortel == 100) return (int) 5;
//}

/// association à chaque catégorie un réel
gfloat calculeVirusDamageField(Virus *v) {
    //int cas = categorieDeVirus(V);
//    switch(categorieDeVirus(v))
//    {
//        case 1: return  (float)  (-0.2);
//        case 2: return  (float) (-0.38);
//        case 3: return  (float) (-0.56);
//        case 4: return  (float) (-0.74);
//        case 5: return  (float)(-6.0);
//    }
    return ((gfloat) ((v->prctMortel / 100.0) * -1.0));
}

gint VirusExiste(Individu *individu, Virus *virus) {
    return g_list_find_custom(individu->virusList, virus->nom, (GCompareFunc) macro_find_compareVirusByName) ? 1 : 0;
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

/*void contaminationDesIndividus(GtkGrid *grid, Coord pos, Virus *virus) {
    guint i, j;
    float x = (float) calculeVirusDamageField(virus);
    ///On parcourt la cercle de contamination de première ligne jusqu'à le dernière
    for (i = (pos.x - virus->cercleDeContam); i < (pos.x + virus->cercleDeContam); i++) {
        //        /// if it is out of the table(grid)
        if (i < 0 || i >= DEFAULT_MAX_ROWS)
            continue;
        ///on parcourt la cercle de contamination de premier colonne jusqu'à la dernière
        for (j = (pos.y - virus->cercleDeContam); j < (pos.y + virus->cercleDeContam); j++) {
            if (j < 0 || j >= DEFAULT_MAX_COLS)/// if it is out of the table(grid)
                continue;
            GtkWidget *box = gtk_grid_get_child_at(grid, i, j);
            GtkWidget *image = gtk_bin_get_child(GTK_BIN(box));
            if (image) {
                Individu *individu = (Individu *) g_object_get_data(G_OBJECT(image), DATA_KEY_INDIVIDU);
                if (VirusExiste(individu, virus)) {
                    /// set le virus au l'individu
                    individu->virusList = g_list_append(individu->virusList, virus);
                    individu->damageTaken += x;
                    //individu->hp -=individu->damageTaken;
                    if (individu->hp <= 0)
                        gtk_image_set_from_icon_name(GTK_IMAGE(image), "computer",
                                                     GTK_ICON_SIZE_BUTTON);/// just to know it is the one until we decide how we kill a individu
                }
            }
        }
    }
}*/

#endif //MAIN_C_CONTAMINATE_UTILS_H
