#include "../header/file_processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 7

/**
 * Sépare la ligne en N parties selon le délimiteur
 * @param line : Chaine de caractère à split
 * @param delim : Caractère séparateur
 * @return Pointeur vers le tableau de chaine de caractère dynamiquement alloué
 */
char** tokenize(char line[], char delim)
{
    int n = strlen(line);
    if (n <= 6) return NULL;

    char **ans = (char**) calloc(N, sizeof(char*));
    if (ans == NULL) {
        perror("Erreur lors de l'allocation");
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
            if (++i < N) {
                ans[i] = (char*) calloc(150, sizeof(char));
                if (ans[i] == NULL) {
                    perror("Erreur lors de l'allocation ");
                    exit(EXIT_FAILURE);
                }
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
 * Remplis le ABR avec les lignes du fichier csv
 * @param arbre : Pointeur vers ABR
 * @param fp : Pointeur vers le FILE en lécture
 * @param delim : Caractère séparateur
 */
void parse_csv(ABR** arbre, char path[],char delim)
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
            abr_inserer(arbre, tmp->data[0], tmp->data[1], tmp);
        }
        buffer[0] = '\0';
        free(splited);
    }
    fclose(fp);
}

void abr_csv_rec(ABR* arbre, char path[], char delim, FILE* fp) {
    if (!abr_est_vide(arbre->fils_gauche)) abr_csv_rec(arbre->fils_gauche, path, delim, fp);
    for (int i = 0; i < arbre->nb_abonnes; i++) {
        for (int k = 0; k < 6; k++) {
            fprintf(fp,"%s%c",arbre->abonnes[i]->data[k],delim);
        }
        fprintf(fp,"%s\n",arbre->abonnes[i]->data[6]);
    }
    if (!abr_est_vide(arbre->fils_droit)) abr_csv_rec(arbre->fils_droit, path, delim, fp);
}

/**
 * Ecris les RECORD du ABR sur le CSV
 * @param array : Pointeur vers ABR
 * @param fp : Pointeur vers le FILE en écriture
 * @param delim : Caractère séparateur
 */
void abr_csv(ABR* arbre, char path[], char delim)
{
    FILE *fp = fopen(path, "w");
    abr_csv_rec(arbre, path, delim, fp);
    fclose(fp);
}
