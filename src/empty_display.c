//
// Created by lain on 30/11/2021.
//

#include "../header/empty_display.h"
#include "../header/struct/ArbreBinaireRecherche.h"
#include "string.h"

#define N 7

int missing_record_rec(ABR *arbre) {
    if (abr_est_vide(arbre)) {
        return 0;
    } else {
        int somme = 0;
        int k = 0;

        for (int i = 0; i < arbre->nb_abonnes; i++) {
            k = 0;
            while (k < N && strcmp(arbre->abonnes[i]->data[k], "") != 0) k++;
            if (k < N) {
                rdisplay(arbre->abonnes[i]);
                somme++;
            }
        }

        if (!abr_est_vide(arbre->fils_gauche)) {
            somme += missing_record_rec(arbre->fils_gauche);
        }

        if (!abr_est_vide(arbre->fils_droit)) {
            somme += missing_record_rec(arbre->fils_droit);
        }

        return somme;
    }
}

/**
 * Affiche les RECORD ayant un attribut vide et leur nombre
 * @param array : Pointeur vers AARRAY
 */
void missing_record(ABR *arbre) {
    printf("Il y a %d abonnées avec une information manquante.", missing_record_rec(arbre));
    printf("\n");
}