//
// Created by abdo on 5/4/2022.
//

#ifndef MAIN_C_SHOW_FUNCTIONS_H
#define MAIN_C_SHOW_FUNCTIONS_H
#include <gtk/gtk.h>
#include "structures.h"
#include "enum_utils.h"
#include "dialog_macro.h"

void get_virusName_from_Virus(gpointer virus, gpointer virusName)
{
    gchar name[20];
    sprintf(((gchar *) name),"%s\n",((Virus *)virus)->nom);
    strcat(virusName,name);
}

void concatinate_virusName(GList * virusList,gchar * virusesNames)
{
    g_list_foreach(virusList,get_virusName_from_Virus,virusesNames);
}

void show_Individu_to_Interface(Individu * indiv)
{
    gchar msg[500];
    gchar virusList[200];
    sprintf(msg,
            "Infos d'individu\n"
            "gender = %s\n"
            "genetic = %s\n"
            "tension = %s\n"
            "diabete = %s\n"
            "cardiaque = %s\n"
            "poumons = %s\n"
            "categorie = %s\n"
            "hp = %.2f\n"
            ,(gchar*)associerGender(indiv),(gchar*)associerGenetique(indiv),(gchar*)associerTension(indiv),(gchar*)associerDiabete(indiv),
            (gchar*)associerCardiaque(indiv),(gchar*)associerPoumons(indiv),(gchar*)associerAge(indiv),indiv->hp
    );
    if(indiv->virusList)
    {
        sprintf(virusList,"Liste des virus :\n");
        concatinate_virusName(indiv->virusList,virusList);
        strcat(msg,virusList);
    }

    macro_dialog(msg);
}

#endif //MAIN_C_SHOW_FUNCTIONS_H
