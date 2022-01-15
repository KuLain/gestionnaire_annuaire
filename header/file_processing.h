//
// Created by lain on 30/11/2021.
//

#ifndef SAE1_2_LINUX_FILE_PROCESSING_H
#define SAE1_2_LINUX_FILE_PROCESSING_H
#include "struct/ArbreBinaireRecherche.h"
#include "gui/main_menu_gui.h"

char** tokenize(char ligne[], char delim);
int parse_csv(ABR** arbre, char path[],char delim, GLOBAL_P*);
void abr_csv(ABR* arbre, char path[], char delim);



#endif //SAE1_2_LINUX_FILE_PROCESSING_H
