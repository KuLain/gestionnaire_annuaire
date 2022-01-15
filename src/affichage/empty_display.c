#include "../../header/affichage/empty_display.h"
#include "../../header/struct/ArbreBinaireRecherche.h"
#include "string.h"
#include "../../header/affichage/sorted_display.h"

#define N 7

/**
 * Affecte les abonnés de arbre ayant une information manquante dans tab
 * @param arbre : Pointeur vers l'ABR
 * @param tab : Tableau de pointeur qui contiendra les abonné ayant une information manquante
 * @param indice : indice du pointeur actuel dans le tableau
 * @return Nombre d'abonnés ayant une information manquante
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
 * Remplis le modèle avec les abonnés ayant information manquante
 * @param arbre : Pointeur vers ABR
 * @param store : Pointeur vers GtkListStore
 * @param iter : Pointeur vers GtkTreeIter
 * @param nb_abo : Pointeur vers int qui contiendra le nombre d'abonnés
 */
void missing_record(ABR *arbre, GtkListStore *store, GtkTreeIter *iter, int *nb_abo) {
    const int n = abr_taille(arbre);
    RECORD *tab[n];
    int i = 0;
    *nb_abo = missing_record_rec(arbre, tab, &i);
    fill_model_tab(tab, i, store, iter);
}