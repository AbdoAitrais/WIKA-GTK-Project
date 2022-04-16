//
// Created by W0L1D on 4/10/2022.
//

#ifndef MAIN_C_SAVE_STATUS_H
#define MAIN_C_SAVE_STATUS_H




/*
 * section:  Tree
 * synopsis: Creates a tree
 * purpose:  Shows how to create document, nodes and dump it to stdout or file.
 * usage:    tree2 <filename>  -Default output: stdout
 * test:     tree2 > tree2.tmp && diff tree2.tmp $(srcdir)/tree2.res
 * author:   Lucas Brasilino <brasilino@recife.pe.gov.br>
 * copy:     see Copyright for the status of this software
 */

#include <stdio.h>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include <gtk/gtk.h>

//#include "macros.c"

#define TAG_ROOT                    "env"
#define TAG_LIST_PERSONS            "persons"
#define TAG_LIST_VIRUS              "viruss"
#define TAG_PERSON                  "person"
#define TAG_PERSON_SANTE            "sante"
#define TAG_VIRUS                   "virus"
#define TAG_DIMENSION               "dimension"
#define TAG_SANTE                   "sante"


#define ATTR_DIMENSION_ROWS         "rows"
#define ATTR_DIMENSION_COLS         "cols"


#define ATTR_PERSON_AGE             "age"
#define ATTR_PERSON_GENRE           "genre"
#define ATTR_PERSON_POUMON          "poumon"
#define ATTR_PERSON_DIABETE         "diabete"
#define ATTR_PERSON_TENSION         "tension"
#define ATTR_PERSON_GENETIC         "genetic"
#define ATTR_PERSON_CARDIAC         "cardiac"
#define ATTR_PERSON_Y               "Y"
#define ATTR_PERSON_X               "x"


#define ATTR_VIRUS_ID               "id"
#define ATTR_VIRUS_nom              "nom"
#define ATTR_VIRUS_SPREAD           "spread"
#define ATTR_VIRUS_MORTALITY        "mortality"
#define ATTR_VIRUS_SPREAD_CIRCLE    "sp-circle"


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


void macro_save_single_virus_node(gpointer virus_data, gpointer virussND) {
    Virus *virus = virus_data;
    xmlNode *virusND = NULL;
    gchar buffer[256];

    /// attach single virus to virus's list node
    /// with setting the nam as virus node content
    virusND = xmlNewChild(virussND, NULL, BAD_CAST TAG_VIRUS,
                          BAD_CAST virus->nom);

    sprintf(buffer, "%d", virus->Id);
    xmlNewProp(virusND, BAD_CAST ATTR_VIRUS_ID, BAD_CAST buffer);

    sprintf(buffer, "%u", virus->cercleDeContam);
    xmlNewProp(virusND, BAD_CAST ATTR_VIRUS_SPREAD_CIRCLE, BAD_CAST buffer);

    sprintf(buffer, "%f", virus->prctContam);
    xmlNewProp(virusND, BAD_CAST ATTR_VIRUS_SPREAD, BAD_CAST buffer);

    sprintf(buffer, "%f", virus->prctMortel);
    xmlNewProp(virusND, BAD_CAST ATTR_VIRUS_MORTALITY, BAD_CAST buffer);

}


xmlNode *trans_SanteToXmlNode(Sante sante) {

    gchar buffer[256];
    xmlNode *santeND = xmlNewNode(NULL, BAD_CAST TAG_SANTE);


    /// TODO :: replace enum int with string
    sprintf(buffer, "%d", sante.cardiac);
    xmlNewProp(santeND, BAD_CAST ATTR_PERSON_CARDIAC, BAD_CAST buffer);

    /// TODO :: replace enum int with string
    sprintf(buffer, "%d", sante.diabete);
    xmlNewProp(santeND, BAD_CAST ATTR_PERSON_DIABETE, BAD_CAST buffer);

    /// TODO :: replace enum int with string
    sprintf(buffer, "%d", sante.genetic);
    xmlNewProp(santeND, BAD_CAST ATTR_PERSON_GENETIC, BAD_CAST buffer);

    /// TODO :: replace enum int with string
    sprintf(buffer, "%d", sante.poumons);
    xmlNewProp(santeND, BAD_CAST ATTR_PERSON_POUMON, BAD_CAST buffer);

    /// TODO :: replace enum int with string
    sprintf(buffer, "%d", sante.tension);
    xmlNewProp(santeND, BAD_CAST ATTR_PERSON_TENSION, BAD_CAST buffer);

    return santeND;

}

void macro_save_single_pers_node(gpointer pers_data, gpointer personsND) {
    Individu *individu = pers_data;
    xmlNode *persNd = NULL;
    gchar buffer[256];

    /// attach single person to persons' list node
    persNd = xmlNewChild(personsND, NULL, BAD_CAST TAG_VIRUS,
                         NULL);

    sprintf(buffer, "%d", individu->pos.x);
    xmlNewProp(persNd, BAD_CAST ATTR_PERSON_X, BAD_CAST buffer);

    sprintf(buffer, "%d", individu->pos.y);
    xmlNewProp(persNd, BAD_CAST ATTR_PERSON_Y, BAD_CAST buffer);

    /// TODO :: replace enum int with string
    sprintf(buffer, "%d", individu->categorie);
    xmlNewProp(persNd, BAD_CAST ATTR_PERSON_AGE, BAD_CAST buffer);


    /// TODO :: replace enum int with string
    sprintf(buffer, "%d", individu->gender);
    xmlNewProp(persNd, BAD_CAST ATTR_PERSON_GENRE, BAD_CAST buffer);


    /// add sante tag to person
    xmlAddChild(persNd, trans_SanteToXmlNode(individu->health));

    /// save person virus' list
    xmlNode *virus = xmlNewChild(persNd, NULL,
                                 BAD_CAST TAG_LIST_VIRUS,
                                 NULL);
    g_list_foreach(individu->VirusList, macro_save_single_virus_node, virus);

}

typedef struct {
    xmlNode *persons;
    GList *virus_list;
} NdVirusList;

int
main1(const gchar *file, EnvInfo envInfo) {
    xmlDocPtr doc = NULL;       /* document pointer */
    xmlNodePtr root_node = NULL, persons = NULL, virus = NULL, coord = NULL;/* node pointers */
    char buff[256];


    /// init document with root node
    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST TAG_ROOT);
    xmlDocSetRootElement(doc, root_node);

    /// Creates a DTD declaration. Isn't mandatory.
//    xmlCreateIntSubset(doc, BAD_CAST TAG_ROOT, NULL, BAD_CAST "tree2.dtd");


    /// create dimension tag which contain env rows and cols
    coord = xmlNewChild(root_node, NULL,
                        BAD_CAST TAG_DIMENSION,
                        NULL);
    sprintf(buff, "%d", envInfo.rows);
    xmlNewProp(coord,
               BAD_CAST ATTR_DIMENSION_ROWS,
               BAD_CAST buff);
    sprintf(buff, "%d", envInfo.cols);
    xmlNewProp(coord,
               BAD_CAST ATTR_DIMENSION_COLS,
               BAD_CAST buff);



    /// create persons list node
    persons = xmlNewNode(NULL, BAD_CAST TAG_LIST_PERSONS);
    xmlAddChild(root_node, persons);

    ///TODO :: to use on parsing document
//    NdVirusList *persNd_virusList = g_malloc(sizeof (NdVirusList));
//    persNd_virusList->virus_list = envInfo.virus;
//    persNd_virusList->persons = persons;
    /// save persons list
    g_list_foreach(envInfo.indivs,
                   macro_save_single_pers_node,
                   persons);



    /// create virus list node
    virus = xmlNewNode(NULL, BAD_CAST TAG_LIST_VIRUS);
    xmlAddChild(root_node, virus);
    /// save virus list
    g_list_foreach(envInfo.virus, macro_save_single_virus_node, virus);


    /// Dumping document to given file or status.kass
    xmlSaveFormatFileEnc(file ? file : "status.kaas", doc, "UTF-8", 1);


    macro_cleanupXML(doc);

    return (0);
}


void test_save_virus() {
    Virus virus;
    GList *list = NULL;

    virus.prctMortel = 15.5;
    virus.prctContam = 52.5;
    virus.cercleDeContam = 10;
    virus.Id = 11155;
    virus.nom = "premier virus";


    list = g_list_append(list, &virus);
    list = g_list_append(list, &virus);
    list = g_list_append(list, &virus);
    list = g_list_append(list, &virus);


    EnvInfo envInfo;

    envInfo.virus = list;
    envInfo.rows = 15;
    envInfo.cols = 15;

    main1("test.xml", envInfo);
}


#endif //MAIN_C_SAVE_STATUS_H
