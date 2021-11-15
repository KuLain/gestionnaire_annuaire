//
// Created by julie on 13/11/2021.
//

#ifndef SAE1_2_FIXEDSTRING_H
#define SAE1_2_FIXEDSTRING_H

typedef struct FixedString {
    char *string;
    int length;
} FSTRING;

FSTRING fsinit(const char *string);
void fsfree(FSTRING tmp);

#endif //SAE1_2_FIXEDSTRING_H
