//
// Created by julie on 25/11/2021.
//

#ifndef SAE_1_2_FILE_PROCESSING_H
#define SAE_1_2_FILE_PROCESSING_H
#include "struct/AssociativeArray.h"
char** tokenize(char ligne[], char delim);
void parse_csv(AARRAY* array, char path[], char delim);

#endif //SAE_1_2_FILE_PROCESSING_H
