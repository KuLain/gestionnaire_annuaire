//
// Created by julie on 25/11/2021.
//

#include "../header/file_processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** tokenize(char line[], char delim)
{
    char **ans = malloc(sizeof(char*)*7);
    if (ans == NULL) {
        perror("Error while allocating");
        exit(EXIT_FAILURE);
    }
    int i = 0, j = 0, k;
    ans[0] = malloc(sizeof(char)*50);
    if (ans[0] == NULL) {
        perror("Error while allocating");
        exit(EXIT_FAILURE);
    }
    for (k = 0; k < strlen(line); k++)
    {
        if (line[k] == delim || line[k] == '\n') {
            ans[i][j] = '\0';
            ans[i] = realloc(ans[i], j + 1);
            if (ans[i] == NULL) {
                perror("Error while reallocating");
                exit(EXIT_FAILURE);
            }
            ans[++i] = malloc(sizeof(char) * 50);
            if (ans[i] == NULL) {
                perror("Error while allocating");
                exit(EXIT_FAILURE);
            }
            j = 0;
        }
        else {
            if (!(line[k] == '.' && i == 4))
            {
                ans[i][j] = line[k];
                j++;
            }
        }
    }
    while (i < 7)
    {
        ans[i] = malloc(sizeof(char));
        ans[i][0] = '\0';
        i++;
    }
    return ans;
}

void parse_csv(AARRAY* array, char path[],char delim)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Error while opening the file ");
        exit(EXIT_FAILURE);
    }
    RECORD *tmp;
    char buffer[150];

    do {
        fgets(buffer, 150, fp);
        tmp = rinit(tokenize(buffer, delim));
        aapush(array, tmp->data[0], tmp->data[1], tmp);
    } while (!feof(fp));
    fclose(fp);
}