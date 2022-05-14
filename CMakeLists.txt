cmake_minimum_required(VERSION 3.21)
project(TestProjectGtk C)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")


find_package(LibXml2 REQUIRED)

add_compile_definitions(TestProjectGtk PUBLIC ${LIBXML2_DEFINITIONS})
include_directories(PUBLIC ${LIBXML2_INCLUDE_DIRS})
link_libraries(${LIBXML2_LIBRARIES})


# On utilise le module PkgConfig pour détecter la librairie GTK+ sur le système
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# On dit à CMake d'utiliser GTK+, on indique au compilateur où trouver les fichiers headers
# Et au linker où trouver les librairies
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Instructions pour le compilateur
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})


# Ajoute un éxecutable à partir du main.c
add_executable(TestProjectGtk
        "lib/constants.h"
        "lib/structures.h"
        "lib/gobject_utils.h"
        "lib/init_env_macro.h"
        "lib/tableauManip.h"
        "lib/contaminate_utils.h"
        "lib/dialog_macro.h"
        "lib/enum_utils.h"
        "lib/show_functions.h"
        "lib/Statistics.h"
        "lib/UI_individu_macros.h"
        "lib/save_status.h"
        "lib/tool.h"
        "lib/xml_management.h"
        main.c
        lib/library.c lib/library.h
#        testMain.c
        )

# Lie à l'éxecutable la librairie GTK+
TARGET_LINK_LIBRARIES(TestProjectGtk ${GTK3_LIBRARIES})