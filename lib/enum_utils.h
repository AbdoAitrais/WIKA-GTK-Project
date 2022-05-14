//
// Created by abdo on 5/4/2022.
//

#ifndef MAIN_C_ENUM_UTILS_H
#define MAIN_C_ENUM_UTILS_H
#include <gtk/gtk.h>
#include "structures.h"

/******  enum to caracteristiques   *************/




gchar* associerGender(Individu* indiv)
{
    switch(indiv->gender)
    {
        case GENRE_MALE:
            return (gchar*)(" Homme");
        case GENRE_FEMALE:
            return (gchar*)(" Femme");
        case GENRE_UNSPECIFIED:
            return (gchar*)(" Unknown");
    }

}


gchar* associerGenetique(Individu* indiv)
{
    switch(indiv->health.genetic)
    {
        case GENETIQUEMENT_FAIBLE:
            return (gchar*)(" Faible");
        case GENETIQUEMENT_FRAGILE:
            return (gchar*)(" Fragile");
        case GENETIQUEMENT_MOYEN:
            return (gchar*)(" Moyen");
        case GENETIQUEMENT_FORT:
            return (gchar*)(" FORT");
    }
}
gchar* associerTension(Individu* indiv)
{
    switch(indiv->health.tension)
    {
        case ARTERIELLE_NORMAL:
            return (gchar*)(" Normal");
        case ARTERIELLE_HYPERTENDU:
            return (gchar*)(" Hypertendu");
        case ARTERIELLE_HYPERTENSION_FORTE:
            return (gchar*)(" Hypertendu forte");
    }
}

gchar* associerDiabete(Individu* indiv)
{
    switch(indiv->health.diabete)
    {
        case DIABETE_NORMAL:
            return (gchar*)(" Normal");
        case DIABETE_MODERE:
            return (gchar*)(" Modere");
        case DIABETE_AVANCE:
            return (gchar*)(" Avance");
    }
}

gchar* associerCardiaque(Individu* indiv)
{
    switch(indiv->health.cardiac)
    {
        case CARDIAQUE_NORMAL:
            return (gchar*)(" Normal");
        case CARDIAQUE_MALADE:
            return (gchar*)(" Malade");
        case CARDIAQUE_SEVERE:
            return (gchar*)(" Severe");
    }
}

gchar* associerPoumons(Individu* indiv)
{
    switch(indiv->health.poumons)
    {
        case POUMONS_SEIN:
            return (gchar*)(" Sein");
        case POUMONS_MALADE:
            return (gchar*)(" Malade");
        case POUMONS_GRAVE:
            return (gchar*)(" Grave");
    }
}


gchar* associerAge(Individu* indiv)
{
    switch(indiv->categorie)
    {
        case AGE_KIDS:
            return (gchar*)(" Enfant");
        case AGE_TEENS:
            return (gchar*)(" Adolescent");
        case AGE_YOUTH:
            return (gchar*)(" Jeune");
        case AGE_ADULT:
            return (gchar*)(" Adulte");
        case AGE_OLD:
            return (gchar*)(" Vieux");

    }
}




#endif //MAIN_C_ENUM_UTILS_H
