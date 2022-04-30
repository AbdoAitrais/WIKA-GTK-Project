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
            *val+=0.2;
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
            *val+=0.2;
            break;
        case ARTERIELLE_HYPERTENDU:
            *val+=0.6;
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
            *val+=0.3;
            break;
        case DIABETE_MODERE:
            *val+=0.7;
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
            *val+=0.6;
            break;
        case CARDIAQUE_MALADE:
            *val+=0.3;
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
            *val +=0.5;
            break;
        case POUMONS_MALADE:
            *val+=0.2;
            break;
        case POUMONS_GRAVE:
            *val+=0.05;
    }
}


float calculerHPdeIndividu(Individu P)
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
// divise les catégories de virus en 5 selon leurs taux de mortalités
int categorieDeVirus(Virus *V)
{
    if(V->prctMortel >=1     &&  V->prctMortel < 25) return (int)1;
    if(V->prctMortel >=25    &&  V->prctMortel < 50) return (int)2;
    if(V->prctMortel >=50    &&  V->prctMortel < 75) return (int)3;
    if(V->prctMortel >=75    &&  V->prctMortel < 99) return (int)4;
    if(V->prctMortel == 100) return (int)5;
}
/// association à chaque catégorie un réel
float calculeLechampABC(Virus *V)
{
    //int cas = categorieDeVirus(V);
    switch(categorieDeVirus(V))
    {
        case 1: return  (float)  (-0.2);
        case 2: return  (float) (-0.38);
        case 3: return  (float) (-0.56);
        case 4: return  (float) (-0.74);
        case 5: return  (float)(-6.0);
    }
    return ((float)(-0.1));/// layomkin asslan
}

int VirusExiste(Individu *P,Virus *V)
{
    GList *temp = P->VirusList;
    while(temp)
    {
        if( !compare_virus(temp->data,V->nom))
            return (int)1;
        temp = temp->next;
    }
    return (int)0;
}



void contaminationDesIndividus(GtkGrid* grid, Coord pos, Virus virus)
{
    int i,j;
    float x = (float)calculeLechampABC(&virus);
    ///On parcourt la cercle de contamination de première ligne jusqu'à le dernière
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
            GtkWidget *box = (GtkWidget*)gtk_grid_get_child_at(grid,i,j);
            GtkWidget* image = ((GtkWidget*)gtk_bin_get_child(box));
            if(image)
            {
                Individu* individu = (Individu*)g_object_get_data(G_OBJECT(image),DATA_KEY_INDIVIDU);
                if( !VirusExiste(individu,&virus))
                {
                    /// set le virus au l'individu
                    individu->VirusList = g_list_append(individu->VirusList,&virus);
                    individu->abc += x;
                    individu->hp -=individu->abc;
                    if(individu->hp <=0)
                        gtk_widget_hide(image);/// just to know it is the one until we decide how we kill a individu
                }
            }
        }
    }
}

#endif //MAIN_C_CONTAMINATE_UTILS_H
