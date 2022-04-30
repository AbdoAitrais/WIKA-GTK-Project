//
// Created by W0L1D on 4/8/2022.
//

#ifndef MAIN_C_CONSTANTS_H
#define MAIN_C_CONSTANTS_H

#define DATA_KEY_INDIVIDU "individu"
#define DATA_KEY_LIST_INDIVIDU "ListIndividus"
#define DATA_KEY_LIST_VIRUS "listVirus"
#define DATA_STATS "stats"


#define DEFAULT_MAX_ROWS 70
#define DEFAULT_MAX_COLS 40

#define DEFAULT_SAVE_FILE_NAME "status.wika"


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
#define ATTR_VIRUS_SPREAD           "spread"
#define ATTR_VIRUS_MORTALITY        "mortality"
#define ATTR_VIRUS_SPREAD_CIRCLE    "sp-circle"


gboolean PLAY_MODE = TRUE;
guint PLAY_SPEED = 600;
int SEQUENCE_ID_VALUE = 0;




#endif //MAIN_C_CONSTANTS_H
