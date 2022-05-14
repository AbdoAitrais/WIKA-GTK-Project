//
// Created by abdo on 5/4/2022.
//

#ifndef MAIN_C_TABLEAUMANIP_H
#define MAIN_C_TABLEAUMANIP_H
#include <stdio.h>
#include "structures.h"

gint Est_Pleine_TListe(Maliste liste) // tester si la liste est pleine
{
    return ((gint)liste.nbrElem == DEFAULT_MAX_ARRAY);
}// fin fonction
/*************************************/

gint initialisationList(Maliste list) // initialiser la liste comme elle est vide
{
    list.nbrElem = 0;
    return list.nbrElem;
}// fin fonction
/*************************************/

gint Est_Vide_TListe(Maliste liste)// tester si la liste est vide
{
    return ((gint)liste.nbrElem == 0);
}

gint inserer_TListe(Maliste *list,gint info) // l'element p et pas l'indice p
{
    gint index;
    if(Est_Pleine_TListe(*list)) return ((gint)0);// si la liste est pleine

    list->tab[list->nbrElem++] = info;// inserer l'element à la position doner
    return 1;
}// fin de fonction inserer

gint suppPosition_TListe(Maliste *list,gint pos)
// supprimer une valeur à l'aide sa position
{
    gint i;
    if(!list) return 0;// si la liste est n'existe jamais
    // teste si la liste est Vide
    if(Est_Vide_TListe(*list)) {printf("\npas d'elements à supprimer");return -1;}
    // teste si la position donnée est invalide
    if(pos<1 || pos>list->nbrElem) {printf("\npos invalide");return ((gint)-2);}
    for(i=pos-1;i<list->nbrElem;i++)
        list->tab[i] = list->tab[i+1];// decalage à gauche
    list->nbrElem--;// decremnter le nombre d'element par 1
    return 1;// succes
}// fin de fonction suppPosition_TListe



#endif //MAIN_C_TABLEAUMANIP_H
