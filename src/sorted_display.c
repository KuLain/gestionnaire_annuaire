//
// Created by julie on 28/11/2021.
//

#include "../header/sorted_display.h"
#include <stdlib.h>
#include <string.h>


/**
 * Affiche le menu pour sélectionner la colonne à trier
 * @param array
 */
void sorted_records(AARRAY *array)
{
    char choix[3];
    int filtre;
    LIST* liste;
    printf("Affichage des abonnés triés par ordre croissant selon un attribut\n");
    printf("Selon quel attribut voulez-vous les trier ?\n\n");

    printf("1) Prénom\n2) Nom\n3) Ville\n4) Code Postal\n5) Numéro de téléphone\n6) Adresse email\n7) Profession \n\n");

    printf("Entrez votre choix : ");
    fgets(choix, 3, stdin);

    if (choix[0] >= '1' && choix[0] <= '9') {
        filtre = choix[0] - 49;
        liste = linit();

        aarray_list(array, liste);
        merge_sort(liste, filtre);
        display_sorted_records(liste);

        free(liste->content);
        free(liste);
        return;
    } else {
        perror("Unknown input");
        return;
    }
}

/**
 * Ajoute tous les pointeurs vers les RECORD du AARRAY dans la LIST
 * @param array : Pointeur vers le AARRAY source
 * @param liste : Pointeur vers la LIST réceptrice
 */
void aarray_list(AARRAY* array, LIST* liste) {
    int i,j;
    for (i = 0; i < array->size; i++) {
        if (array->content[i] != NULL) {
            for (j = 0; j < array->content[i]->length; j++) {
                lpush(liste, (RECORD*)array->content[i]->content[j]);
            }
        }
    }
}

/**
 * Déplace les éléments plus grand que le pivot à droite,
 * déplace les éléments plus petit que le pivot à gauche puis
 * place le pivot au milieu de la LIST
 * @param liste : Pointeur vers la LIST contenant les RECORD
 * @param gauche : Indice du début de la sous LIST
 * @param droite : Indice de la fin de la sous LIST
 * @param filter : 0 <= filter <= 7 : Indice de la colonne selon laquelle les RECORD vont être trier
 * @return Indice du pivot une fois au milieu de la LIST
 */
int partition(LIST *liste, int gauche, int droite, int filter) {
    char *clef;
    RECORD *tmp;
    int i, j;

    clef = liste->content[droite]->data[filter];
    i = gauche-1;
    j = droite;
    while (i <= j) {
        while ((++i < droite) && (strcmp(liste->content[i]->data[filter],clef) < 0));
        while ((--j > (gauche-1)) && (strcmp(liste->content[j]->data[filter],clef) > 0));
        if (i < j) {
            tmp = liste->content[i];
            liste->content[i] = liste->content[j];
            liste->content[j] = tmp;
        }
    }
    tmp = liste->content[i];
    liste->content[i] = liste->content[droite];
    liste->content[droite] = tmp;
    return i;
}

/**
 * Effectue le tri rapide
 * @param liste : Pointeur vers la LIST contenant les RECORD
 * @param gauche : Indice du début de la sous LIST
 * @param droite : Indice de la fin de la sous LIST
 * @param filter : 0 <= filter <= 7 : Indice de la colonne selon laquelle les RECORD vont être trier
 */
void quick_sort_rec(LIST *liste, int gauche, int droite, int filter) {
    int pivot;
    if (gauche < droite) {
        pivot = partition(liste, gauche, droite, filter);
        quick_sort_rec(liste, gauche, pivot-1,filter);
        quick_sort_rec(liste, pivot+1, droite,filter);
    }
}

/**
 * Appelle la fonction de tri rapide récursif
 * @param liste : Pointeur vers la LIST contenant les RECORD
 * @param filter : 0 <= filter <= 7 : Indice de la colonne selon laquelle les RECORD vont être trier
 */
void quick_sort(LIST *liste, int filter) {
    quick_sort_rec(liste, 0, liste->length-1, filter);
}

void merge(LIST *liste, int debut, int milieu, int fin, int filter) {
    int i, j, k;
    int n1 = milieu - debut + 1;
    int n2 = fin - milieu;

    RECORD *gauche[n1], *droite[n2];

    for (i = 0; i < n1; i++) gauche[i] = liste->content[debut+i];
    for (i = 0; i < n2; i++) droite[i] = liste->content[milieu+1+i];

    i = 0;
    j = 0;
    k = debut;

    while (i < n1 && j < n2) {
        if (strcmp(gauche[i]->data[filter], droite[j]->data[filter]) < 0) {
            liste->content[k] = gauche[i];
            i++;
        } else {
            liste->content[k] = droite[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        liste->content[k] = gauche[i];
        i++;
        k++;
    }

    while (j < n2) {
        liste->content[k] = droite[j];
        j++;
        k++;
    }
}

/**
 * Effectue le tri fusion
 * @param liste : Pointeur vers la LIST contenant les RECORD
 * @param debut : Indice du debut du sous tableau
 * @param fin : Indice de la fin du sous tableau
 * @param filter : 0 <= filter <= 7 : Indice de la colonne selon laquelle les RECORD vont être trier
 */
void merge_sort_rec(LIST *liste, int debut, int fin, int filter) {
    if (debut < fin) {
        int m = (debut+fin) / 2;

        merge_sort_rec(liste, debut, m, filter);
        merge_sort_rec(liste, m+1, fin, filter);

        merge(liste, debut, m, fin, filter);
    }
}

/**
 * Appelle la fonction de tri fusion récursif
 * @param liste : Pointeur ver la LIST contenant les RECORD
 * @param filter : 0 <= filter <= 7 : Indice de la colonne selon laquelle les RECORD vont être trier
 */
void merge_sort(LIST *liste, int filter) {
    merge_sort_rec(liste, 0, liste->length-1, filter);
}

/**
 * Affiche tous les RECORD de la LIST
 * @param liste : Pointeur vers la LIST contenant les RECORD
 */
void display_sorted_records(LIST *liste)
{
    int i;
    for (i = 0; i < liste->length; i++) {
        rdisplay((RECORD*)liste->content[i]);
    }
}