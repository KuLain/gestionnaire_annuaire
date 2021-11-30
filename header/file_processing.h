//
// Created by lain on 30/11/2021.
//

#ifndef SAE1_2_LINUX_FILE_PROCESSING_H
#define SAE1_2_LINUX_FILE_PROCESSING_H
#include "struct/AssociativeArray.h"

char** tokenize(char ligne[], char delim);
void parse_csv(AARRAY* array, char path[],char delim);
void aarray_csv(AARRAY* array, char path[], char delim);



#endif //SAE1_2_LINUX_FILE_PROCESSING_H
