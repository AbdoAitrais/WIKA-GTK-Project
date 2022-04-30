//
// Created by abdo on 4/29/2022.
//

#ifndef MAIN_C_STATISTICS_H
#define MAIN_C_STATISTICS_H
#include <stdlib.h>
#include <gtk/gtk.h>

#include "../constants.h"
#include "structures.h"


/************ Tools ***********/

typedef struct {

    gint gap;///nombre des pixels au dessus des buffers.
    gint lmarg;///le margine à gauche des buffers.


    const gchar *color_fg;///couleur du text.
    const gchar *color_bg;///couleur du fond.
    PangoStyle style;///le style de police.
    PangoWeight weight;///poids de la police.


}TextBufferProps;

void macro_ApplyTextBuffer(GtkTextBuffer *buffer,TextBufferProps tbprops)
{
    if(tbprops.gap > 0)
        gtk_text_buffer_create_tag(buffer,"gap","pixels_above_lines",tbprops.gap,NULL);
    if(tbprops.lmarg > 0)
        gtk_text_buffer_create_tag(buffer,"lmarg","left_margin",tbprops.lmarg,NULL);
    if(tbprops.color_fg)
        gtk_text_buffer_create_tag(buffer,"color_fg","foreground",tbprops.color_fg,NULL);
    if(tbprops.color_bg)
        gtk_text_buffer_create_tag(buffer,"color_bg","background",tbprops.color_bg,NULL);
    if(tbprops.style)
        gtk_text_buffer_create_tag(buffer,"style","style",tbprops.style,NULL);
    if(tbprops.weight)
        gtk_text_buffer_create_tag(buffer,"weight","weight",tbprops.weight,NULL);

}

typedef struct
{
    gint left;     /// margin gauche
    gint right;       /// margin droit
    gint bottom;    /// margin du bas
    gint top;       /// margin du haut
} MarginTextProps;

typedef struct {

    MarginTextProps marge;///In CSS terms, the value set here is padding. Don't confuse this property with “margin-bottom”.

    gint pixels_above_lines;///Pixels of blank space above paragraphs.
    gint pixels_below_lines;///Pixels of blank space below paragraphs.
    gint pixels_inside_wrap;///Pixels of blank space between wrapped lines in a paragraph.

    gboolean editable;///whether the text is editable or not
    gboolean cursor_visible;///whether the cursor is visible or not
    gboolean monospace;///chaque lettre et caractères y compris les espaces occupent le même espace horizontal que les autres.
    gboolean overwrite;///Whether entered text overwrites existing contents.

    GtkJustification justification;///La justification du texte
    GtkWrapMode wrap_mode;///Whether to wrap lines never, at word boundaries, or at character boundaries.

    TextBufferProps bufferprops;///les proprietés du buffer
    char *text;///Le texte à afficher

}TextViewProps;





void macro_ApplyTextView(GtkTextView *textv,TextViewProps tvprops)
{


    if(!tvprops.cursor_visible)
        gtk_text_view_set_cursor_visible(textv,tvprops.cursor_visible);
    if(tvprops.monospace)
        gtk_text_view_set_monospace(textv,tvprops.monospace);
    if(tvprops.overwrite)
        gtk_text_view_set_overwrite(textv,tvprops.overwrite);
    if(tvprops.justification)
        gtk_text_view_set_justification(textv,tvprops.justification);
    if(tvprops.wrap_mode)
        gtk_text_view_set_wrap_mode(textv,tvprops.wrap_mode);
    if(tvprops.marge.bottom > 0)
        gtk_text_view_set_bottom_margin(textv,tvprops.marge.bottom);
    if(tvprops.marge.top > 0)
        gtk_text_view_set_top_margin(textv,tvprops.marge.top);
    if(tvprops.marge.left > 0)
        gtk_text_view_set_left_margin(textv,tvprops.marge.left);
    if(tvprops.marge.right > 0)
        gtk_text_view_set_right_margin(textv,tvprops.marge.right);
    if(!tvprops.editable )
        gtk_text_view_set_editable(textv,tvprops.editable);
}
GtkWidget *macro_createTextView(TextViewProps tvprops)
{
    GtkTextIter iter;
    GtkWidget *textv = gtk_text_view_new();
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textv));
    macro_ApplyTextView(GTK_TEXT_VIEW(textv),tvprops);
    macro_ApplyTextBuffer(GTK_TEXT_BUFFER(buffer),tvprops.bufferprops);
    gtk_text_buffer_get_iter_at_offset (buffer,&iter,0);

    gtk_text_buffer_insert_with_tags_by_name(buffer,&iter,tvprops.text,-
            1,"color_bg", "color_fg","weight","style","lmarg","gap",NULL);


    return textv;
}

/************ Statistics Structures *************/

typedef struct{
    const gchar * virusName;
    guint infected;
}StatVirus;

typedef struct{
    guint currentPopulation;
    guint deaths;
    GList * virusInfection;
}Stats;

guint sum_GList(GList * individus)
{
    guint sum = 0;
    GList * crt = individus;

    while (crt){
        sum++;
        crt = crt->next;
    }

    return ((guint) sum);
}

//void calculate_current_population()
//{
//
//}

gint compare_StatVirus(gpointer virus,gpointer nom)
{
    gchar * name = nom;
    StatVirus * v = virus;
    return g_strcmp0(v->virusName,name);
}

StatVirus * get_StatVirus_fromString(const gchar *nom,Stats * stat)
{
    GList * elem = NULL;
    if(stat->virusInfection)
    {
        elem = g_list_find_custom(
                stat->virusInfection,nom,(GCompareFunc)compare_StatVirus
        );
    }


    return elem?((StatVirus *)elem->data):NULL;
}

StatVirus * init_StatVirus(const gchar * nom)
{
    StatVirus * sv = (StatVirus *) g_malloc(sizeof(StatVirus));
    if(!sv)
    {
        g_printerr("StatVirus Allocation problem !");
        exit(0);
    }
    sv->infected = 0;
    sv->virusName = g_strdup(nom);
    return ((StatVirus *) sv);
}

void calculate_StatVirus(GList * individus,Stats * stat)
{
    GList *crtIndividu = individus;
    while(crtIndividu)
    {
        GList * crtvirus = ((Individu *) g_object_get_data(G_OBJECT(crtIndividu->data),DATA_KEY_INDIVIDU))->VirusList;

        while (crtvirus)
        {
            if(crtvirus->data)
            {
                StatVirus * sVirus = get_StatVirus_fromString(((Virus *) crtvirus->data)->nom,stat);
                if(sVirus)
                {
                    sVirus->infected++;
                }
                else
                {

                    StatVirus * sv = init_StatVirus(((Virus *) crtvirus->data)->nom);
                    sv->infected++;
                    stat->virusInfection = g_list_append(stat->virusInfection,sv);
                }
            }

            crtvirus = crtvirus->next;
        }
        crtIndividu = crtIndividu->next;
    }
}

void reset_StatVirus_Stats(Stats * stat)
{
    g_list_free(stat->virusInfection);
    stat->virusInfection = NULL;
}



Stats * init_Stats()
{
    Stats * stat = (Stats *) g_malloc(sizeof(Stats));
    if(!stat)
    {
        g_printerr("StatVirus Allocation problem !");
        exit(0);
    }
    stat->virusInfection = NULL;
    stat->currentPopulation = 0;
    stat->deaths = 0;

    return ((Stats *) stat);
}

void init_save_Stats(gpointer builder)
{
    Stats * stat = init_Stats();
    if(g_object_get_data(builder,DATA_STATS))
        return;
    g_object_set_data(builder,DATA_STATS,stat);
}

Stats * calculate_stats(gpointer builder,Stats *stat)
{
    GtkWidget * window = GTK_WIDGET(gtk_builder_get_object(builder,"MainWindow"));
    GList * Individus = g_object_get_data(G_OBJECT(window),DATA_KEY_LIST_INDIVIDU);
    reset_StatVirus_Stats(stat);
    if(stat)
    {
        stat->currentPopulation = sum_GList(Individus);
        calculate_StatVirus(Individus,stat);
    }
    return stat;
}

void afficher_StatVirus(GList * Statv)
{
    GList * crt = Statv;

    printf("\nVirus Infections :");
    while(crt)
    {

        printf("\n%s : %d",((StatVirus *) crt->data)->virusName,((StatVirus *) crt->data)->infected);
        crt = crt->next;
    }
}

void afficher_Stats(Stats * stat)
{
    if(stat)
    {

        printf("\nCurrent Population : %d",stat->currentPopulation);
        afficher_StatVirus(stat->virusInfection);
    }
}

TextBufferProps * set_TextBufferProps(const gchar * color_bg,const gchar *color_fg,gint weight,PangoStyle style)
{
    TextBufferProps * tbp = (TextBufferProps *) g_malloc(sizeof(TextBufferProps));

    tbp->color_bg = g_strdup(color_bg);
    tbp->color_fg = g_strdup(color_fg);
    tbp->weight = weight;
    tbp->style = style;



    return ((TextBufferProps *) tbp);
}

TextViewProps * set_TextViewProps(gint margeLeft,gint margeRight,gint margeTop,gint margeBot,gboolean edit,
                                  GtkJustification justify,gboolean cursor_visible,gchar * text,
                                  TextBufferProps bufferprops)
{
    TextViewProps * tvp = (TextViewProps *) g_malloc(sizeof(TextViewProps));

    tvp->marge.left = margeLeft;
    tvp->marge.right = margeRight;
    tvp->marge.top = margeTop;
    tvp->marge.bottom = margeBot;

    tvp->editable = edit;
    tvp->justification = justify;
    tvp->cursor_visible = cursor_visible;
    tvp->text = g_strdup(text);
    tvp->bufferprops = bufferprops;


    return ((TextViewProps *) tvp);
}

void add_TextView_to_stack(gpointer builder,gchar * text)
{
    GtkWidget * box = GTK_WIDGET(gtk_builder_get_object(builder,"GrandSonBoxStats"));
    TextBufferProps * tbp = set_TextBufferProps("grey",NULL,20,PANGO_STYLE_NORMAL);
    TextViewProps * tvp = set_TextViewProps(10,10,10,10,FALSE,
                                            GTK_JUSTIFY_LEFT,FALSE,text,*tbp);
}

#endif //MAIN_C_STATISTICS_H
