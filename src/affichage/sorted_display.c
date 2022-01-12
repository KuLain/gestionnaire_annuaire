//
// Created by julie on 28/11/2021.
//

#include "affichage/sorted_display.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <gtk-3.0/gtk/gtk.h>

#define CONVERT_UTF8(chaine) g_locale_from_utf8(chaine, -1, NULL, NULL, NULL)

enum {
    COL_PRENOM = 0,
    COL_NOM,
    COL_VILLE,
    COL_CP,
    COL_TELEPHONE,
    COL_MAIL,
    COL_PROFESSION,
};


/**
 * Ajoute tous les pointeurs vers les RECORD du ABR dans le tableau
 * @param arbre : Pointeur vers le ABR source
 * @param liste : Pointeur vers le tableau de pointeur de RECORD récepteur
 */
void ABR_list(ABR* arbre, RECORD* tab[], int* i) {
    if (!abr_est_vide(arbre)) {
        for (int j = 0; j < arbre->nb_abonnes; j++) tab[(*i)++] = arbre->abonnes[j];
        ABR_list(arbre->fils_gauche, tab, i);
        ABR_list(arbre->fils_droit, tab, i);
    }
}

/**
 * Déplace les éléments plus grand que le pivot à droite,
 * déplace les éléments plus petit que le pivot à gauche puis
 * place le pivot au milieu de le tableau
 * @param tab : Pointeur vers le tableau contenant les RECORD
 * @param gauche : Indice du début du sous tableau
 * @param droite : Indice de la fin du sous tableau
 * @param filter : 0 <= filter <= 7 : Indice de la colonne selon laquelle les RECORD vont être trier
 * @return Indice du pivot une fois au milieu de le tableau
 */
int partition(RECORD* tab[], int gauche, int droite, int filter) {
    srand(time(NULL));
    char *clef;
    RECORD *tmp;
    int i, j;

    clef = tab[rand()%(droite-gauche)+gauche]->data[filter];
    i = gauche-1;
    j = droite;
    while (i <= j) {
        while ((++i < droite) && (strcmp(tab[i]->data[filter],clef) < 0));
        while ((--j > (gauche-1)) && (strcmp(tab[j]->data[filter],clef) > 0));
        if (i < j) {
            tmp = tab[i];
            tab[i] = tab[j];
            tab[j] = tmp;
        }
    }
    tmp = tab[i];
    tab[i] = tab[droite];
    tab[droite] = tmp;
    return i;
}

/**
 * Effectue le tri rapide
 * @param tab : Pointeur vers le tableau contenant les RECORD
 * @param gauche : Indice du début du sous tableau
 * @param droite : Indice de la fin du sous tableau
 * @param filter : 0 <= filter <= 7 : Indice de la colonne selon laquelle les RECORD vont être trier
 */
void quick_sort_rec(RECORD* tab[], int gauche, int droite, int filter) {
    int pivot;
    if (gauche < droite) {
        pivot = partition(tab, gauche, droite, filter);
        quick_sort_rec(tab, gauche, pivot-1,filter);
        quick_sort_rec(tab, pivot+1, droite,filter);
    }
}

/**
 * Appelle la fonction de tri rapide récursif
 * @param tab : Pointeur vers le tableau contenant les RECORD
 * @param taille : Taille du tableau contenant tous les RECORD
 * @param filter : 0 <= filter <= 7 : Indice de la colonne selon laquelle les RECORD vont être trier
 */
void quick_sort(RECORD* tab[],const int taille, int filter, GtkListStore *store, GtkTreeIter *iter) {
    quick_sort_rec(tab, 0, taille-1, filter);
    fill_model_tab(tab, taille, store, iter);
}

void merge(RECORD* tab[], int debut, int milieu, int fin, int filter) {
    int i, j, k;
    int const n1 = milieu - debut + 1;
    int const n2 = fin - milieu;

    RECORD *gauche[n1], *droite[n2];

    for (i = 0; i < n1; i++) gauche[i] = tab[debut+i];
    for (i = 0; i < n2; i++) droite[i] = tab[milieu+1+i];

    i = 0;
    j = 0;
    k = debut;

    while (i < n1 && j < n2) {
        if (strcmp(gauche[i]->data[filter], droite[j]->data[filter]) < 0) {
            tab[k] = gauche[i];
            i++;
        } else {
            tab[k] = droite[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        tab[k] = gauche[i];
        i++;
        k++;
    }

    while (j < n2) {
        tab[k] = droite[j];
        j++;
        k++;
    }
}

/**
 * Effectue le tri fusion
 * @param tab : Pointeur vers le tableau contenant les RECORD
 * @param debut : Indice du debut du sous tableau
 * @param fin : Indice de la fin du sous tableau
 * @param filter : 0 <= filter <= 7 : Indice de la colonne selon laquelle les RECORD vont être trier
 */
void merge_sort_rec(RECORD* tab[], int debut, int fin, int filter) {
    if (debut < fin) {
        int m = (debut+fin) / 2;

        merge_sort_rec(tab, debut, m, filter);
        merge_sort_rec(tab, m+1, fin, filter);

        merge(tab, debut, m, fin, filter);
    }
}

/**
 * Appelle la fonction de tri fusion récursif
 * @param tab : Pointeur vers le tableau contenant les RECORD
 * @param taille : Taille du tableau contenant les RECORD
 * @param filter : 0 <= filter <= 7 : Indice de la colonne selon laquelle les RECORD vont être trier
 */
void merge_sort(RECORD* tab[], const int taille, int filter) {
    merge_sort_rec(tab, 0, taille-1, filter);
}

/**
 * Affiche tous les RECORD de le tableau
 * @param tab : Pointeur vers le tableau contenant les RECORD
 */
void display_sorted_records(RECORD* tab[], const int taille)
{
    int i;
    for (i = 0; i < taille; i++) rdisplay(tab[i]);
}

void fill_model_tab(RECORD *tab[], int taille, GtkListStore *store, GtkTreeIter *iter) {
    for (int i = 0; i < taille; i++) {
        gtk_list_store_append (store, iter);
        gtk_list_store_set (store, iter,
                            COL_PRENOM, CONVERT_UTF8(tab[i]->data[PRENOM]),
                            COL_NOM, CONVERT_UTF8(tab[i]->data[NOM]),
                            COL_VILLE, CONVERT_UTF8(tab[i]->data[VILLE]),
                            COL_CP, CONVERT_UTF8(tab[i]->data[CP]),
                            COL_TELEPHONE, CONVERT_UTF8(tab[i]->data[TELEPHONE]),
                            COL_MAIL, CONVERT_UTF8(tab[i]->data[MAIL]),
                            COL_PROFESSION, CONVERT_UTF8(tab[i]->data[PROFESSION]),
                            -1);
    }
}