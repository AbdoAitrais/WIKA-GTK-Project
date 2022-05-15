//
// Created by abdo on 4/28/2022.
//

#ifndef MAIN_C_STRUCTURES_H
#define MAIN_C_STRUCTURES_H
#include <gtk/gtk.h>
#include "constants.h"

/********** structures ************/
typedef struct {
    const gchar *nom;//Indentifiant du virus le nom associé à le virus
    guint virusLife;//le temps de vie du Virus
    gfloat prctMortel; // le pourcentage de mortalite de virus
    guint cercleDeContam;// le rayon ou bien la cercle de contamination
    gfloat damage;// la valeur  à calculer à partir de champ prctMortel
} Virus;

typedef struct {
    gint x;// la position selon les lignes
    gint y;// la position selon les colonnes
} Coord;// les cooordonnées d'une entité dans l'interface

typedef enum {
    GENETIQUEMENT_FAIBLE,
    GENETIQUEMENT_FRAGILE,
    GENETIQUEMENT_MOYEN,
    GENETIQUEMENT_FORT
} Genitique;

typedef enum {
    ARTERIELLE_NORMAL,
    ARTERIELLE_HYPERTENDU,
    ARTERIELLE_HYPERTENSION_FORTE,
} Tension;

typedef enum {
    DIABETE_NORMAL,
    DIABETE_MODERE,
    DIABETE_AVANCE
} Diabete;

typedef enum {
    CARDIAQUE_NORMAL,
    CARDIAQUE_MALADE,
    CARDIAQUE_SEVERE
} Cardiaque;

typedef enum {
    POUMONS_SEIN,
    POUMONS_MALADE,
    POUMONS_GRAVE
} Poumons;

typedef struct {
    Genitique genetic;
    Tension tension;
    Diabete diabete;
    Cardiaque cardiac;
    Poumons poumons;
}Sante;

typedef enum {
    GENRE_UNSPECIFIED,
    GENRE_MALE,
    GENRE_FEMALE
} Genre;

typedef enum {
    AGE_KIDS, AGE_TEENS,
    AGE_YOUTH, AGE_ADULT,
    AGE_OLD
} Age;

// si vous voulez faire deux entites (personne,animal) mais je pense c'est pas le peine

typedef struct
{
    gint tab[DEFAULT_MAX_ARRAY]; // le tableau de la liste
    gint nbrElem;// le nombre d'element du tableau
}Maliste;// definition de la structure

typedef struct {
    Genre gender;// le sexe de Individu
    Age categorie;//la categorie associé à le Individu selon son âge
    Coord pos;//les coordonnées où se présente le Individu
    Sante health;// l'état sanitaire associé à le Individu
    GList *virusList;// liste des virus qui a le Individu
    gfloat hp;// health points
    gfloat damageTaken;// c'est la valeur pour decrementer le hp selon les virus associés à l'individu
    Maliste virusesLifes;
} Individu;// peut être animal,personne...



/************ Statistics Structures *************/

typedef struct {
    const gchar *virusName; /// nom du virus
    guint infected;         /// nombre des individus affectees par ce virus
} StatVirus;

typedef struct {
    guint deaths;           /// nombre des deces total
    guint totalPopulation; /// nombre total des individus
    GList *virusInfection; /// statistique par virus
} Stats;

#endif //MAIN_C_STRUCTURES_H








