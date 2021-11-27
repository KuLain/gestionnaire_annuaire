//
// Created by julie on 25/11/2021.
//

#include "../header/file_processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** tokenize(char line[], char delim)
{
    int n = strlen(line);
    if (n <= 6) return NULL;

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
    for (k = 0; k < n; k++)
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
    return ans;
}

void parse_csv(AARRAY* array, char path[],char delim)
{
    RECORD *tmp;
    char buffer[150];
    char **splited;
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Error while opening the file ");
        exit(EXIT_FAILURE);
    }

    do {
        fgets(buffer, 150, fp);
        splited = tokenize(buffer, delim);
        if (splited != NULL) {
            tmp = rinit(splited);
            aapush(array, tmp->data[0], tmp->data[1], tmp);
        }
        buffer[0] = '\0';
    } while (!feof(fp));
    fclose(fp);
}

void aarray_csv(AARRAY* array, char path[], char delim)
{
    FILE *fp = fopen(path, "w");
    RECORD *tmp;
    int i, j, k;
    for (i = 0; i < array->size; i++) {
        if (array->content[i] != NULL) {
            for (j = 0; j < array->content[i]->length; j++) {
                tmp = (RECORD*)array->content[i]->content[j];
                for (k = 0; k < 6; k++) {
                    fprintf(fp,"%s%c",tmp->data[k],delim);
                }
                fprintf(fp,"%s\n",tmp->data[6]);
            }
        }
    }
    fclose(fp);
}