//
// Created by W0L1D on 4/29/2022.
//

#ifndef MAIN_C_CONTAMINATE_UTILS_H
#define MAIN_C_CONTAMINATE_UTILS_H

#include "../by Abderrahman/structures.h"
#include "../constants.h"

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


int includeCercle(GtkGrid* grid, Coord pos, Virus virus)
{
    int i,j;
    /// on parcourt la cercle de contamination de première ligne jusqu'à le dernière
    for(i = (pos.x - virus.cercleDeContam); i < (pos.x + virus.cercleDeContam); i++)
    {
        /// if it is out of the table(grid)
        if( i<0 || i>=DEFAULT_MAX_ROWS)
            continue;
        ///on parcourt la cercle de contamination de premier colonne jusqu'à la dernière
        for(j = (pos.y - virus.cercleDeContam); j < (pos.y + virus.cercleDeContam); j++)
        {
            if( j< 0 || j >= DEFAULT_MAX_COLS)/// if it is out of the table(grid)
                continue;

            GtkWidget* image = gtk_grid_get_child_at(grid,i,j);
            Individu* individu = (Individu*)g_object_get_data(G_OBJECT(image),DATA_KEY_INDIVIDU);
            if(individu)
                return 0;
        }
    }
}

#endif //MAIN_C_CONTAMINATE_UTILS_H
