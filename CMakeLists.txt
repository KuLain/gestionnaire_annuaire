cmake_minimum_required(VERSION 3.22)
project(gestionnaire_annuaire C)

set(CMAKE_C_STANDARD 11)

include_directories(header)
include_directories(header/affichage)
include_directories(header/gui)
include_directories(header/struct)

add_executable(gestionnaire_annuaire
        header/affichage/empty_display.h
        header/affichage/filtered_display.h
        header/affichage/sorted_display.h
        header/gui/buttons_event.h
        header/gui/call_dialogs.h
        header/gui/main_menu_gui.h
        header/gui/tree_display.h
        header/struct/ArbreBinaireRecherche.h
        header/struct/Record.h
        header/file_processing.h
        src/affichage/empty_display.c
        src/affichage/filtered_display.c
        src/affichage/sorted_display.c
        src/gui/buttons_event.c
        src/gui/call_dialogs.c
        src/gui/tree_display.c
        src/struct/ArbreBinaireRecherche.c
        src/struct/Record.c
        src/file_processing.c
        main.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(gestionnaire_annuaire ${GTK3_LIBRARIES})
