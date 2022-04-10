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

#include "macros.c"

#define TAG_ROOT                    "env"
#define TAG_LIST_PERSONS            "persons"
#define TAG_LIST_VIRUS              "viruss"
#define TAG_PERSON                  "person"
#define TAG_PERSON_SANTE            "sante"
#define TAG_VIRUS                   "virus"
#define TAG_DIMENSION               "dimension"


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





typedef struct {
    guint x ,y;
    Individu indiv;
}IndivInfo;


typedef struct {
    /// contains data of type IndivInfo
    GList *indivs;
    /// contains data of type Virus
    GList *virus;
    /// environnement dimension
    guint cols, rows;

}EnvInfo;


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


int
main1(const gchar  *file, EnvInfo envInfo)
{
    xmlDocPtr doc = NULL;       /* document pointer */
    xmlNodePtr root_node = NULL, persons = NULL, virus = NULL, coord = NULL;/* node pointers */
    char buff[256];
    int i, j;

    /*
     * Creates a new document, a node and set it as a root node
     */
    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST TAG_ROOT);
    xmlDocSetRootElement(doc, root_node);

    /*
     * Creates a DTD declaration. Isn't mandatory.
     */
//    xmlCreateIntSubset(doc, BAD_CAST TAG_ROOT, NULL, BAD_CAST "tree2.dtd");


    /// create dimension tag which contain env rows and cols
    coord = xmlNewChild(root_node, NULL,
                        BAD_CAST TAG_DIMENSION,
                        NULL);
    sprintf(buff, "%d", envInfo.rows);
    xmlNewProp(coord, BAD_CAST ATTR_DIMENSION_ROWS, BAD_CAST buff);
    sprintf(buff, "%d", envInfo.cols);
    xmlNewProp(coord, BAD_CAST ATTR_DIMENSION_COLS, BAD_CAST buff);



    /// create persons list node
    persons = xmlNewNode(NULL, BAD_CAST TAG_LIST_PERSONS);
    xmlAddChild(root_node, persons);


    /// create virus list node
    virus = xmlNewNode(NULL, BAD_CAST TAG_LIST_VIRUS);
    xmlAddChild(root_node, virus);
    /// save virus list
    g_list_foreach(envInfo.virus, macro_save_single_virus_node, virus);

    /*
     * Dumping document to given file or status.kass
     */
    xmlSaveFormatFileEnc(file? file:"status.kaas", doc, "UTF-8", 1);


    macro_cleanupXML(doc);

    return(0);
}


#endif //MAIN_C_SAVE_STATUS_H
