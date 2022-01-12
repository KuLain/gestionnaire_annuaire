//
// Created by lain on 30/11/2021.
//

#include "affichage/empty_display.h"
#include "struct/ArbreBinaireRecherche.h"
#include "string.h"
#include "../header/affichage/sorted_display.h"

#define N 7

/**
 * Recherche les RECORD ayant un attribut maintenant
 * @param arbre : Pointeur vers l'arbre
 * @return Nombre de RECORD ayant des informations manquantes
 */
int missing_record_rec(ABR *arbre, RECORD *tab[], int *indice) {
    if (abr_est_vide(arbre)) {
        return 0;
    } else {
        int somme = 0;
        int k = 0;

        for (int i = 0; i < arbre->nb_abonnes; i++) {
            k = 0;
            while (k < N && strcmp(arbre->abonnes[i]->data[k], "") != 0) k++;
            if (k < N) {
                tab[(*indice)++] = arbre->abonnes[i];
                somme++;
            }
        }

        if (!abr_est_vide(arbre->fils_gauche)) {
            somme += missing_record_rec(arbre->fils_gauche, tab, indice);
        }

        if (!abr_est_vide(arbre->fils_droit)) {
            somme += missing_record_rec(arbre->fils_droit, tab, indice);
        }

        return somme;
    }
}

/**
 * Affiche les RECORD ayant un attribut vide et leur nombre
 * @param array : Pointeur vers AARRAY
 */
void missing_record(ABR *arbre, GtkListStore *store, GtkTreeIter *iter, int *nb_abo) {
    const int n = abr_taille(arbre);
    RECORD *tab[n];
    int i = 0;
    *nb_abo = missing_record_rec(arbre, tab, &i);
    fill_model_tab(tab, i, store, iter);
}