#include "struct/ArbreBinaireRecherche.h"
#include "affichage/filtered_display.h"
#include "affichage/sorted_display.h"
#include <string.h>
#include <stdlib.h>



void matching_filter_rec(ABR* arbre,int column,char filtre[], int taille_filtre, RECORD* tab[], int* i) {
    if (!abr_est_vide(arbre)) {
        int k;
        for (int j = 0; j < arbre->nb_abonnes; j++) {
            k = 0;
            while (k < strlen(arbre->abonnes[j]->data[column]) && arbre->abonnes[j]->data[column][k] == filtre[k]) k++;
            if (k == taille_filtre) tab[(*i)++] = arbre->abonnes[j];
        }
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
void matching_filter(ABR* arbre, int column, char *filter, GtkListStore* store, GtkTreeIter *iter) {
    const int taille = abr_taille(arbre);
    const int n = strlen(filter);
    int i = 0, j;
    RECORD* matching_patterns[taille];

    matching_filter_rec(arbre, column, filter, n, matching_patterns, &i);

    fill_model_tab(matching_patterns, i, store, iter);
    for (j = 0; j < i; j++) rdisplay(matching_patterns[j]);
}

