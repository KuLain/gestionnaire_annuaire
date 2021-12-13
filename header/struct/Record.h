#ifndef SAE1_2_LINUX_RECORD_H
#define SAE1_2_LINUX_RECORD_H

#include <stdio.h>

#define PRENOM 0
#define NOM 1
#define VILLE 2
#define CP 3
#define TELEPHONE 4
#define MAIL 5
#define PROFESSION 6

typedef struct Record {
    char **data;
} RECORD;

RECORD* rinit(char **data);
void rdisplay(RECORD *r);
void rfree(RECORD *r);



#endif //SAE1_2_LINUX_RECORD_H
