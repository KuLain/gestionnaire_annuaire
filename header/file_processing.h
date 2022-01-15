#ifndef SAE1_2_LINUX_FILE_PROCESSING_H
#define SAE1_2_LINUX_FILE_PROCESSING_H

#include "struct/ArbreBinaireRecherche.h"

void slow_exit();

char **tokenize(char ligne[], char delim);

void parse_csv(ABR **arbre, char path[], char delim);

void abr_csv(ABR *arbre, char path[], char delim);


#endif //SAE1_2_LINUX_FILE_PROCESSING_H
