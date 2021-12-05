//
// Created by julie on 29/11/2021.
//

#include "../header/filtered_display.h"
#include "../header/sorted_display.h"
#include <string.h>
#include <stdlib.h>


/**
 * Affiche le menu pour choisir comment filtrer les RECORD
 * @param array : Pointeur vers le AARRAY contenant les RECORD
 */
void filtered_records(AARRAY* array) {
    char choix[3], filter[150];
    int column;

    printf("Séléction des abonnés par filtre\n");
    printf("Selon quel critère voulez-vous filter les abonnés ?\n\n");
    printf("1) Prénom\n");
    printf("2) Nom\n");
    printf("3) Ville\n");
    printf("4) Code postal\n");
    printf("5) Numéro de téléphone\n");
    printf("6) Adresse email\n");
    printf("7) Profession\n");
    printf("*) Retour au menu principal\n\n");

    printf("Entrez votre séléction : ");
    fgets(choix, 3, stdin);
    printf("\n");

    if (choix[0] >= '1' && choix[0] <= '7') {
        column = choix[0] - 49;
    } else {;
        return;
    }

    printf("Entrez le fitre souhaité : ");
    fgets(filter, 150, stdin);
    filter[strlen(filter)-1] = '\0';

    matching_filter(array, column, filter);
    return;
}

/**
 * Affiche les RECORD correspondant au filtre
 * @param array : Pointeur vers le AARRAY
 * @param column : 0 <= column <= 7 : Indice de la colonne dans laquel on applique le filtre
 * @param filter : Filtre à appliquer
 */
void matching_filter(AARRAY* array, int column, char filter[]) {
    LIST *matching_patterns = linit();
    RECORD *tmp;
    int i, j, k;
    const int n = strlen(filter);

    for (i = 0; i < array->size; i++) {
        if (array->content[i] != NULL) {
            for (j = 0; j < array->content[i]->length; j++) {
                tmp = (RECORD*)array->content[i]->content[j];
                k = 0;
                while (k < n && tmp->data[column][k] == filter[k]) k++;
                if (k == n) lpush(matching_patterns, tmp);
            }
        }
    }
    display_sorted_records(matching_patterns);
    free(matching_patterns->content);
    free(matching_patterns);
}