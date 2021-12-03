#include "../header/file_processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Sépare la ligne en 7 parties selon le délimiteur
 * @param line : Chaine de caractère à split
 * @param delim : Caractère séparateur
 * @return Pointeur vers le tableau de chaine de caractère dynamiquement alloué
 */
char** tokenize(char line[], char delim)
{
    int n = strlen(line);
    if (n <= 6) return NULL;

    char **ans = (char**) calloc(7, sizeof(char*));
    if (ans == NULL) {
        perror("Error while allocating");
        exit(EXIT_FAILURE);
    }
    int i = 0, j = 0, k;
    ans[0] = (char*) calloc(150, sizeof(char));
    if (ans[0] == NULL) {
        perror("Error while allocating");
        exit(EXIT_FAILURE);
    }
    for (k = 0; k < n; k++)
    {
        if (line[k] == delim || line[k] == '\n') {
            ans[i][j] = '\0';
            ans[i] = (char*)realloc(ans[i], sizeof(char)*(j+1));
            if (ans[i] == NULL) {
                perror("Error while reallocating");
                exit(EXIT_FAILURE);
            }
            if (i+1 != 7) i++;
            ans[i] = (char*) calloc(150, sizeof(char));
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

/**
 * Remplis le AARRAY avec les lignes du fichier csv
 * @param array : Pointeur vers AARRAY
 * @param fp : Pointeur vers le FILE en lécture
 * @param delim : Caractère séparateur
 */
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

    while (!feof(fp)) {
        fgets(buffer, 150, fp);
        splited = tokenize(buffer, delim);
        if (splited != NULL) {
            tmp = rinit(splited);
            aapush(array, tmp->data[0], tmp->data[1], tmp);
        }
        buffer[0] = '\0';
        free(splited);
    }
    fclose(fp);
}

/**
 * Ecris les RECORD du AARRAY sur le CSV
 * @param array : Pointeur vers AARRAY
 * @param fp : Pointeur vers le FILE en écriture
 * @param delim : Caractère séparateur
 */
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
