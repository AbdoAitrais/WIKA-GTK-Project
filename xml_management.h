//
// Created by W0L1D on 4/26/2022.
//

#ifndef MAIN_C_XML_MANAGEMENT_H
#define MAIN_C_XML_MANAGEMENT_H

#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include <gtk/gtk.h>
#include "constants.h"




/********** structures ************/


typedef struct cel {
    gint Id;//Indentifiant du virus(peut être coleur par exemple rgb Ox......) // it can be gchar* too choose one
    const gchar *nom;// le nom associé à le virus
    gfloat prctContam;// le pourcentage de contamination de virus
    gfloat prctMortel; // le pourcentage de mortalite de virus
    guint cercleDeContam;// le rayon ou bien la cercle de contamination
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
} Sante;

typedef enum {
    GENRE_UNSPECIFIED,
    GENRE_MALE,
    GENRE_FEMALE
} Genre;

typedef enum {
    AGE_KIDS,
    AGE_TEENS,
    AGE_YOUTH,
    AGE_ADULT,
    AGE_OLD
} Age;

typedef enum {
    AGE_INF12,
    AGE_BETWEEN1225,
    AGE_BETWEEN2540,
    AGE_BETWEEN4065,
    AGE_SUP65
} Age2;

// si vous voulez faire deux entites (personne,animal) mais je pense c'est pas le peine
typedef struct {

    Genre gender;// le sexe de Individu
    ///gint age;//l'âge de Individu
    Age categorie;//la categorie associé à le Individu selon son âge
    Coord pos;//les coordonnées où se présente le Individu
    Sante health;// l'état sanitaire associé à le Individu
    GList *VirusList;// liste des virus qui a le Individu
} Individu;// peut être animal,personne...

/*********** project functions ****************/






typedef struct {
    guint x, y;
    Individu indiv;
} IndivInfo;


typedef struct {
    /// contains data of type IndivInfo
    GList *indivs;
    /// contains data of type Virus
    GList *virus;
    /// environnement dimension
    guint cols, rows;

} EnvInfo;






/******
 * Read th file and get it root node
 * @param filename file to parse
 * @return root node
 */
xmlNode *macro_getRootElem(const gchar *filename) {
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    /*parse the file and get the DOM */
    doc = xmlReadFile(filename, NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", filename);
        return NULL;
    }

    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);

    return root_element;
}



/***
 * frees the pbjects used to parse the xml file
 * @param doc xml document to free
 */
void macro_cleanupXML(xmlDoc *doc) {
    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
}

#endif //MAIN_C_XML_MANAGEMENT_H
