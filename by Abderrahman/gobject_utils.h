//
// Created by abdo on 4/28/2022.
//

#ifndef MAIN_C_GOBJECT_UTILS_H
#define MAIN_C_GOBJECT_UTILS_H
#include "structures.h"

void inserer_data_GObject(GObject * object,gchar * key,gpointer data)
{
    GList * l = g_object_get_data(object,key);

    l = g_list_append(l,data);

    g_object_set_data(object,key,l);

}

gint macro_find_compareVirusByName(gpointer virus, gpointer nom) {
    Virus *v = virus;
    return g_ascii_strcasecmp(v->nom, nom);
}


#endif //MAIN_C_GOBJECT_UTILS_H
