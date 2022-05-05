//
// Created by W0L1D on 4/26/2022.
//

#ifndef MAIN_C_XML_MANAGEMENT_H
#define MAIN_C_XML_MANAGEMENT_H

#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include "by Abderrahman/structures.h"



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

    Stats *stats;

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
