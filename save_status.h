//
// Created by W0L1D on 4/10/2022.
//

#ifndef MAIN_C_SAVE_STATUS_H
#define MAIN_C_SAVE_STATUS_H



#include "xml_management.h"
#include "by Abderrahman/UI_individu_macros.h"


static void macro_save_single_virus_node(gpointer virus_data, gpointer virussND) {
    Virus *virus = virus_data;
    xmlNode *virusND = NULL;
    gchar buffer[256];


    /// attach single virus to virus's list node
    /// with setting the nam as virus node content
    virusND = xmlNewChild(virussND,NULL,BAD_CAST TAG_VIRUS,
                          BAD_CAST virus->nom);

    sprintf(buffer,"%d", virus->Id);
    xmlNewProp(virusND,BAD_CAST ATTR_VIRUS_ID,BAD_CAST buffer);

    sprintf(buffer, "%u", virus->cercleDeContam);
    xmlNewProp(virusND,BAD_CAST ATTR_VIRUS_SPREAD_CIRCLE,BAD_CAST buffer);

    sprintf(buffer,"%f", virus->prctContam);
    xmlNewProp(virusND,BAD_CAST ATTR_VIRUS_SPREAD,BAD_CAST buffer);

    sprintf(buffer,"%f", virus->prctMortel);
    xmlNewProp(virusND,BAD_CAST ATTR_VIRUS_MORTALITY,BAD_CAST buffer);

}


static xmlNode *trans_SanteToXmlNode(Sante sante) {

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

static void macro_save_single_pers_node(gpointer pers_data, gpointer personsND) {
    Individu *individu = pers_data;
    xmlNode *persNd = NULL;
    gchar buffer[256];

    /// attach single person to persons' list node
    persNd = xmlNewChild(personsND, NULL, BAD_CAST TAG_PERSON,
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


int macro_saveStatus(const gchar *file, EnvInfo envInfo) {
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
    xmlSaveFormatFileEnc(file ? file : DEFAULT_SAVE_FILE_NAME, doc, "UTF-8", 1);


    macro_cleanupXML(doc);

    return (0);
}


static GList *test_sample_virus_list() {
    Virus *virus = (Virus *) g_malloc(sizeof(Virus));
    GList *list = NULL;

    virus->prctMortel = 15.5;
    virus->prctContam = 52.5;
    virus->cercleDeContam = 10;
    virus->Id = 11155;
    virus->nom = "premier virus";


    list = g_list_append(list, virus);
    list = g_list_append(list, virus);
    list = g_list_append(list, virus);
    list = g_list_append(list, virus);
    return list;
}


static GList *test_sample_indiv_list() {
    Individu *individu = (Individu *) g_malloc(sizeof(Individu));
    GList *list = NULL;

    individu->pos.x = 15;
    individu->pos.y = 20;
    individu->categorie = AGE_ADULT;
    individu->gender = GENRE_MALE;
    individu->health.cardiac = CARDIAQUE_MALADE;
    individu->health.diabete = DIABETE_MODERE;
    individu->health.genetic = GENETIQUEMENT_FORT;
    individu->health.tension = ARTERIELLE_HYPERTENSION_FORTE;
    individu->health.poumons = POUMONS_SEIN;
    individu->VirusList = test_sample_virus_list();


    list = g_list_append(list, individu);
    list = g_list_append(list, individu);
    list = g_list_append(list, individu);
    list = g_list_append(list, individu);
    return list;
}



static EnvInfo *macro_initEnvInfo() {
    EnvInfo *envInfo = g_malloc(sizeof(EnvInfo));
    envInfo->virus = NULL;
    envInfo->indivs = NULL;
    envInfo->cols = DEFAULT_MAX_COLS;
    envInfo->rows = DEFAULT_MAX_ROWS;
    return envInfo;
}


static void macro_parseDimension(EnvInfo *envInfo, xmlNode *node) {
    const gchar *property = (gchar *) xmlGetProp(node, (const xmlChar *) ATTR_DIMENSION_ROWS);
    envInfo->rows = g_ascii_strtoull(property, NULL, 0);

    property = (gchar *) xmlGetProp(node, (const xmlChar *) ATTR_DIMENSION_COLS);
    envInfo->cols = g_ascii_strtoull(property, NULL, 0);

}

static Virus *macro_parseVirus(xmlNode *node) {
    Virus *virus = g_malloc(sizeof(Virus));
    const gchar *property = (gchar *) xmlGetProp(node, (const xmlChar *) ATTR_VIRUS_ID);
    virus->Id = g_ascii_strtoll(property, NULL, 0);

    property = (gchar *) xmlGetProp(node, (const xmlChar *) ATTR_VIRUS_MORTALITY);
    virus->prctMortel = g_ascii_strtod(property, NULL);

    property = (gchar *) xmlGetProp(node, (const xmlChar *) ATTR_VIRUS_SPREAD);
    virus->prctContam = g_ascii_strtod(property, NULL);

    property = (gchar *) xmlGetProp(node, (const xmlChar *) ATTR_VIRUS_SPREAD_CIRCLE);
    virus->cercleDeContam = g_ascii_strtoull(property, NULL, 0);

    virus->nom = g_strdup((gchar *) xmlNodeGetContent(node));

    return ((Virus *) virus);
}

/********************************
 * parse virus list
 * @param node xmlNode representing the virus list
 * @return List of parsed virus
 */
static GList *macro_parseViruss(xmlNode *node) {
    xmlNode *curNode;
    GList *viruss = NULL;
    for (curNode = node->children; curNode; curNode = curNode->next)
        if (!xmlStrcasecmp(curNode->name, (const xmlChar *) TAG_VIRUS))
            viruss = g_list_append(viruss, macro_parseVirus(curNode));
    return ((GList *)viruss);
}

static void macro_parseIndividusSante(xmlNode *node, Sante *sante) {
    const gchar *property = (gchar *) xmlGetProp(
            node,
            (const xmlChar *) ATTR_PERSON_TENSION);
    sante->tension = g_ascii_strtoll(property, NULL, 0);

    property = (gchar *) xmlGetProp(
            node,
            (const xmlChar *) ATTR_PERSON_POUMON);
    sante->poumons = g_ascii_strtoll(property, NULL, 0);

    property = (gchar *) xmlGetProp(
            node,
            (const xmlChar *) ATTR_PERSON_GENETIC);
    sante->genetic = g_ascii_strtoll(property, NULL, 0);

    property = (gchar *) xmlGetProp(
            node,
            (const xmlChar *) ATTR_PERSON_DIABETE);
    sante->diabete = g_ascii_strtoll(property, NULL, 0);

    property = (gchar *) xmlGetProp(
            node,
            (const xmlChar *) ATTR_PERSON_CARDIAC);
    sante->cardiac = g_ascii_strtoll(property, NULL, 0);

}

static Individu *macro_parseSingleIndiv(xmlNode *node) {
    Individu *indiv = g_malloc(sizeof(Individu));
    const gchar *property = (gchar *) xmlGetProp(
            node,
            (const xmlChar *) ATTR_PERSON_X);
    indiv->pos.x = g_ascii_strtoll(property, NULL, 0);

    property = (gchar *) xmlGetProp(
            node,
            (const xmlChar *) ATTR_PERSON_Y);
    indiv->pos.y = g_ascii_strtoll(property, NULL, 0);

    property = (gchar *) xmlGetProp(
            node,
            (const xmlChar *) ATTR_PERSON_GENRE);
    indiv->gender = g_ascii_strtoll(property, NULL, 0);

    property = (gchar *) xmlGetProp(
            node,
            (const xmlChar *) ATTR_PERSON_AGE);
    indiv->categorie = g_ascii_strtoll(property, NULL, 0);

    xmlNode *curNode;
    for (curNode = node->children; curNode; curNode = curNode->next) {
        if (!xmlStrcasecmp(curNode->name, (const xmlChar *) TAG_LIST_VIRUS))
            indiv->VirusList = macro_parseViruss(curNode);
        else if (!xmlStrcasecmp(curNode->name, (const xmlChar *) TAG_PERSON_SANTE))
            macro_parseIndividusSante(curNode, &(indiv->health));
    }

    return ((Individu *) indiv);
}


static void macro_parseIndividus(EnvInfo *envInfo, xmlNode *node) {
    xmlNode *curNode;
    for (curNode = node->children; curNode; curNode = curNode->next)
        if (!xmlStrcasecmp(curNode->name, (const xmlChar *) TAG_PERSON))
            envInfo->indivs = g_list_append(envInfo->indivs, macro_parseSingleIndiv(curNode));

}


/**************************************
 * parse saved status from wika file
 * @param file wika file
 * @return environnement properties
 */
static EnvInfo *macro_parseStatus(const gchar *file) {
    if (!file)
        file = DEFAULT_SAVE_FILE_NAME;

    EnvInfo *envInfo = macro_initEnvInfo();

    xmlNode *root;
    root = macro_getRootElem(file);
    /// if the file is not found or could not be parsed
    if (!root) return envInfo;

    if (xmlStrcasecmp(root->name, (const xmlChar *) TAG_ROOT))
        goto out_of_parsing;

    xmlNode *curNode;
    for (curNode = root->children; curNode; curNode = curNode->next) {
        if (!xmlStrcasecmp(curNode->name, (const xmlChar *) TAG_DIMENSION))
            macro_parseDimension(envInfo, curNode);
        else if (!xmlStrcasecmp(curNode->name, (const xmlChar *) TAG_LIST_VIRUS))
            envInfo->virus = macro_parseViruss(curNode);
        else if (!xmlStrcasecmp(curNode->name, (const xmlChar *) TAG_LIST_PERSONS))
            macro_parseIndividus(envInfo, curNode);
    }


    out_of_parsing:
    macro_cleanupXML(root->doc);

    return envInfo;
}


void test_save_env() {


    EnvInfo envInfo;

    envInfo.virus = test_sample_virus_list();
    envInfo.indivs = test_sample_indiv_list();

    envInfo.rows = 15;
    envInfo.cols = 15;


    macro_saveStatus("test.wika", envInfo);
}

void test_parse_env() {
    EnvInfo *envInfo = macro_parseStatus("test.wika");

    afficher_individu(envInfo->indivs->data);
}





#endif //MAIN_C_SAVE_STATUS_H
