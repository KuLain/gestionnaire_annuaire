//
// Created by julie on 29/11/2021.
//
#include "../header/struct/ArbreBinaireRecherche.h"
#include "../header/filtered_display.h"
#include "../header/sorted_display.h"
#include <string.h>
#include <stdlib.h>


/**
 * Affiche le menu pour choisir comment filtrer les RECORD
 * @param arbre : Pointeur vers le ABR contenant les RECORD
 */
void filtered_records(ABR* arbre) {
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

    matching_filter(arbre, column, filter);
    return;
}

void matching_filter_rec(ABR* arbre,int column,char filtre[], int taille_filtre, RECORD* tab[], int* i) {
    if (!abr_est_vide(arbre)) {
        int k = 0;
        while (k < strlen(arbre->abonne->data[column]) && arbre->abonne->data[column][k] == filtre[k]) k++;
        if (k == taille_filtre) tab[(*i)++] = arbre->abonne;
        matching_filter_rec(arbre->fils_gauche, column, filtre, taille_filtre, tab, i);
        matching_filter_rec(arbre->fils_droit, column, filtre, taille_filtre, tab, i);
    }
}

/**
 * Affiche les RECORD correspondant au filtre
 * @param arbre : Pointeur vers le ABR
 * @param column : 0 <= column <= 7 : Indice de la colonne dans laquel on applique le filtre
 * @param filter : Filtre à appliquer
 */
void matching_filter(ABR* arbre, int column, char filter[]) {
    const int taille = abr_taille(arbre);
    const int n = strlen(filter);
    int i = 0, j;
    RECORD* matching_patterns[taille];

    matching_filter_rec(arbre, column, filter, n, matching_patterns, &i);

    for (j = 0; j < i; j++) matching_patterns[j];
}

