//
// Created by abdo on 4/28/2022.
//

#ifndef MAIN_C_UI_INDIVIDU_MACROS_H
#define MAIN_C_UI_INDIVIDU_MACROS_H
#include "structures.h"
#include "../constants.h"
#include "gobject_utils.h"

/************* Individu ***************/

void Afficher_VirusList(GList * VirusList);
void Afficher_individu(Individu * indiv)
{
    if(indiv)
    {
        g_print("individu gender = %d\n",indiv->gender);
        g_print("individu genetic = %d\n",indiv->health.genetic);
        g_print("individu tension = %d\n",indiv->health.tension);
        g_print("individu diabete = %d\n",indiv->health.diabete);
        g_print("individu cardiac = %d\n",indiv->health.cardiac);
        g_print("individu poumons = %d\n",indiv->health.poumons);
        g_print("individu categorie = %d\n",indiv->categorie);
        Afficher_VirusList(indiv->VirusList);
    }
}

void get_selected_radioButtonLabel_fromGrp(GSList * List,gchar *label)
{
    GSList *crt = List;
    while (crt)
    {
        //GtkRadioButton *radio = crt->data;
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(crt->data)))
        {
//            g_print("gender from GSList = %s\n",gtk_button_get_label(GTK_BUTTON(crt->data)));
            g_stpcpy(label,gtk_button_get_label(GTK_BUTTON(crt->data)));
            //g_print("gender from GSList = %s\n",label);
            return ;
        }
        crt = crt->next;
    }
}

Genre get_genre_fromString(gchar *genre)
{
    if(!g_strcmp0(genre,"Homme"))
        return GENRE_MALE;
    if(!g_strcmp0(genre,"Femme"))
        return GENRE_FEMALE;
    return GENRE_UNSPECIFIED;
}

Genitique get_genetic_fromString(gchar *genetic)
{
    if(!g_strcmp0(genetic,"GENETIQUEMENT_FRAGILE"))
        return GENETIQUEMENT_FRAGILE;
    if(!g_strcmp0(genetic,"GENETIQUEMENT_MOYEN"))
        return GENETIQUEMENT_MOYEN;
    if(!g_strcmp0(genetic,"GENETIQUEMENT_FORT"))
        return GENETIQUEMENT_FORT;
    return GENETIQUEMENT_FAIBLE;
}

Tension get_tension_fromString(gchar *tension)
{
    if(!g_strcmp0(tension,"ARTERIELLE_HYPERTENDU"))
        return ARTERIELLE_HYPERTENDU;
    if(!g_strcmp0(tension,"ARTERIELLE_HYPERTENSION_FORTE"))
        return ARTERIELLE_HYPERTENSION_FORTE;
    return ARTERIELLE_NORMAL;
}

Diabete get_diabete_fromString(gchar *diabete)
{
    if(!g_strcmp0(diabete,"DIABETE_MODERE"))
        return DIABETE_MODERE;
    if(!g_strcmp0(diabete,"DIABETE_AVANCE"))
        return DIABETE_AVANCE;
    return DIABETE_NORMAL;
}

Cardiaque get_cardiac_fromString(gchar *cardiac)
{
    if(!g_strcmp0(cardiac,"CARDIAQUE_MALADE"))
        return CARDIAQUE_MALADE;
    if(!g_strcmp0(cardiac,"CARDIAQUE_SEVERE"))
        return CARDIAQUE_SEVERE;
    return CARDIAQUE_NORMAL;
}

Poumons get_poumons_fromString(gchar *poumons)
{
    if(!g_strcmp0(poumons,"POUMONS_MALADE"))
        return POUMONS_MALADE;
    if(!g_strcmp0(poumons,"POUMONS_GRAVE"))
        return POUMONS_GRAVE;
    return POUMONS_SEIN;
}

Age get_age_fromString(gchar *age)
{
    if(!g_strcmp0(age,"inférieur à 12 ans"))
        return AGE_KIDS;
    if(!g_strcmp0(age,"entre 12 et 25 ans"))
        return AGE_TEENS;
    if(!g_strcmp0(age,"entre 40 et 65 ans"))
        return AGE_ADULT;
    if(!g_strcmp0(age,"plus de 65 ans"))
        return AGE_OLD;
    return AGE_YOUTH;
}



gint compare_virus(gpointer virus,gpointer nom)
{
    gchar * name = nom;
    Virus * v = virus;
    return g_strcmp0(v->nom,name);
}

Virus * get_virus_fromString(const gchar *nom,gpointer builder)
{
    GList * elem = g_list_find_custom(
            g_object_get_data(builder,DATA_KEY_LIST_VIRUS),nom,(GCompareFunc)compare_virus
    );

    return elem?((Virus *)elem->data):NULL;
}


GList *get_selected_checkButtons_fromButtonList(GList * buttonList,gpointer builder)
{
    GList *crt = buttonList;
    GList *VirusList = NULL;
    while (crt)
    {
        //GtkRadioButton *radio = crt->data;
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(crt->data)))
        {
            VirusList = g_list_append(VirusList,get_virus_fromString(
                    gtk_button_get_label(GTK_BUTTON(crt->data)),builder
            ));
        }
        crt = crt->next;
    }
    return ((GList *) VirusList);
}

//GList * get_virus_list_fromCheckButtons(GtkButtonBox * buttonBox,gpointer builder)
//{
//    GList * buttonList = gtk_container_get_children(GTK_CONTAINER(buttonBox));
//    GList * VirusList = get_selected_checkButtons_fromButtonList(buttonList,builder);
//    return ((GList *) VirusList);
//}

Individu *lire_Indiv(gpointer builder)
{
    Individu *individu = (Individu*)g_malloc(sizeof(Individu));
    GtkRadioButton * radioButton =  GTK_RADIO_BUTTON(gtk_builder_get_object (builder, "radioButtonHomme"));
    GSList * radioGrp = gtk_radio_button_get_group(radioButton);
    gchar * genre = (gchar*)g_malloc(sizeof(gchar));
    GtkWidget *comboBoxGen = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxGenitiques"));
    GtkWidget *comboBoxTens = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxTension"));
    GtkWidget *comboBoxDiab = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxDiabete"));
    GtkWidget *comboBoxCard = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxCardiaque"));
    GtkWidget *comboBoxPoum = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxPoumons"));
    GtkWidget *buttonBox = GTK_WIDGET(gtk_builder_get_object (builder, "ButtonBoxVirus"));
    GtkWidget *comboBoxAge = GTK_WIDGET(gtk_builder_get_object (builder, "comboBoxAge"));


    get_selected_radioButtonLabel_fromGrp(radioGrp,genre);
    //g_print("string gender = %s\n",genre);
    individu->gender = get_genre_fromString(genre);
    individu->health.genetic = get_genetic_fromString(
            gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBoxGen))
    );
    individu->health.tension = get_tension_fromString(
            gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBoxTens))
    );
    individu->health.diabete = get_diabete_fromString(
            gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBoxDiab))
    );
    individu->health.cardiac = get_cardiac_fromString(
            gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBoxCard))
    );
    individu->health.poumons = get_poumons_fromString(
            gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBoxPoum))
    );
    individu->VirusList = get_selected_checkButtons_fromButtonList(
            gtk_container_get_children(GTK_CONTAINER(buttonBox)),builder
    );
    individu->categorie = get_age_fromString(
            gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboBoxAge))
    );

    return individu;
}

/*********** Virus ***************/


void afficher_virus(Virus *vir)
{
    printf("L'id = %d\n",vir->Id);
    printf("Le nom = %s\n",vir->nom);
    printf("Le pourcentage de contamination = %f\n",vir->prctContam);
    printf("Le taux de mortalite = %f\n",vir->prctMortel);
    printf("Le cercle de contamination = %d\n",vir->cercleDeContam);
}



void Afficher_VirusList(GList * VirusList)
{
    GList *crt = VirusList;
    while (crt)
    {
        afficher_virus((Virus *)crt->data);
        crt = crt->next;
    }
}



void add_checkbutton_with_label_toBox(GtkWidget *box,Virus * virus)
{
    GtkWidget * checkButton = gtk_check_button_new_with_label(virus->nom);
    gtk_box_pack_start(GTK_BOX(box), checkButton, TRUE, TRUE, 0);
    gtk_widget_show(checkButton);
}

void inserer_virus(gpointer builder,Virus *virus)
{
    GtkWidget *buttonBox = GTK_WIDGET(gtk_builder_get_object (builder, "ButtonBoxVirus"));
    if(!get_virus_fromString(virus->nom,builder))
    {
        g_print("\nVirus from input : \n");
        afficher_virus(virus);
        inserer_data_GObject(builder,DATA_KEY_LIST_VIRUS,virus);
        add_checkbutton_with_label_toBox(buttonBox,virus);
    }
}

void remplir_virus(gpointer builder,gint Id,const gchar *nom,gfloat prctContam,gfloat prctMortel,guint cercleDeContam)
{
    Virus *virus = (Virus*)g_malloc(sizeof(Virus));
    virus->Id = Id;
    virus->nom = g_strdup(nom);
    virus->prctContam = prctContam;
    virus->prctMortel = prctMortel;
    virus->cercleDeContam = cercleDeContam;

    inserer_virus(builder,virus);
}

int id = 0;

void enregistrer_virus(GtkButton *button, gpointer builder)
{
    Virus *v = (Virus*) g_malloc(sizeof(Virus));

    GtkAdjustment *adjust1 = GTK_ADJUSTMENT(gtk_builder_get_object (builder, "adjust1"));
    GtkAdjustment *adjust2 = GTK_ADJUSTMENT(gtk_builder_get_object (builder, "adjust2"));
    GtkAdjustment *adjust3 = GTK_ADJUSTMENT(gtk_builder_get_object (builder, "adjust3"));
    GtkWidget *entryNomVirus = GTK_WIDGET(gtk_builder_get_object (builder, "entryNomVirus"));
    const gchar * nom = gtk_entry_get_text(GTK_ENTRY(entryNomVirus));

    if(!g_strcmp0(nom,""))
    {
        GtkWidget *limit;

        limit = gtk_message_dialog_new (NULL,
                                        GTK_DIALOG_MODAL,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_CLOSE,
                                        "Invalid Virus name !");

        /* Affichage de la boite de message */
        gtk_dialog_run(GTK_DIALOG(limit));

        /* Destruction de la boite de message */
        gtk_widget_destroy(limit);

        return ;
    }
    remplir_virus(builder,++id,gtk_entry_get_text(GTK_ENTRY(entryNomVirus)),
                  ((gfloat)gtk_adjustment_get_value (GTK_ADJUSTMENT(adjust1))),
                  ((gfloat)gtk_adjustment_get_value(GTK_ADJUSTMENT(adjust2))),
                  ((gint)gtk_adjustment_get_value (GTK_ADJUSTMENT(adjust3)))
    );


    //inserer_virus(builder,v);


    //afficher_virus_enregistre(builder);

}

#endif //MAIN_C_UI_INDIVIDU_MACROS_H
