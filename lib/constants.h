//

//

#ifndef MAIN_C_CONSTANTS_H
#define MAIN_C_CONSTANTS_H

/// key of individu  in window storage
#define DATA_KEY_INDIVIDU "individu"
/// key of individu list in window storage
#define DATA_KEY_LIST_INDIVIDU "ListIndividus"
#define DATA_KEY_LIST_VIRUS "listVirus"
#define DATA_KEY_STATS "stats"
#define BUILDER_ID_MAIN_WINDOW "MainWindow"
#define BUILDER_ID_GRID "EnvGrid"
#define DEFAULT_STATUS_FILE "status.wika"


#define DEFAULT_MAX_ROWS 70
#define DEFAULT_MAX_COLS 40
#define DEFAULT_MAX_ARRAY 100

#define DEFAULT_SAVE_FILE_NAME      "status.wika"



#define TAG_ROOT                    "env"
#define TAG_LIST_PERSONS            "persons"
#define TAG_LIST_VIRUS              "viruss"
#define TAG_LIST_VIRUS_LIFE         "viruss-life"
#define TAG_LIST_STATISTICS         "statistics"
#define TAG_PERSON                  "person"
#define TAG_PERSON_SANTE            "sante"
#define TAG_VIRUS                   "virus"
#define TAG_DIMENSION               "dimension"
#define TAG_SANTE                   "sante"
#define TAG_STAT_VIRUS              "statVirus"


#define ATTR_STATISTICS_DEATHS      "deaths"
#define ATTR_STATISTICS_POP_TOTAL   "total"
#define ATTR_STAT_VIRUS_INFECTED    "infected"


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
#define ATTR_PERSON_HP              "hp"
#define ATTR_PERSON_DAMAGE          "damage"


#define ATTR_VIRUS_ID               "id"
#define ATTR_VIRUS_SPREAD           "spread"
#define ATTR_VIRUS_MORTALITY        "mortality"
#define ATTR_VIRUS_SPREAD_CIRCLE    "sp-circle"


gboolean PLAY_MODE = TRUE;
gboolean ADD_INDIVIDU_MODE = FALSE;
guint PLAY_SPEED = 600;

gchar *CURRENT_SAVE_FILE = NULL;


#endif //MAIN_C_CONSTANTS_H
