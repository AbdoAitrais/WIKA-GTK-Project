//
// Created by abdo on 4/28/2022.
//

#ifndef MAIN_C_GOBJECT_UTILS_H
#define MAIN_C_GOBJECT_UTILS_H
#include <gtk/gtk.h>

void inserer_data_GObject(GObject * object,gchar * key,gpointer data)
{
    GList * l = g_object_get_data(object,key);

    l = g_list_append(l,data);

    g_object_set_data(object,key,l);

}

#endif //MAIN_C_GOBJECT_UTILS_H
