#ifndef SAE1_2_LINUX_BASE_PROCESSING_H
#define SAE1_2_LINUX_BASE_PROCESSING_H

#include "../header/struct/ArbreBinaireRecherche.h"

void add_record(ABR **, char[], char);

void delete_record(ABR **, char[], char);

void change_record(ABR *, char[], char);

void access_record(ABR *);


#endif //SAE1_2_LINUX_BASE_PROCESSING_H
