#include "../../header/affichage/sorted_display.h"
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

/**
 * Julien
 * Affiche le menu pour selectionner la colonne a trier
 * @param arbre
 */
void sorted_records(ABR *arbre)
{
    struct timespec debut, fin;
    char choix[3];
    int filtre;
    int i = 0;
    const int n = abr_taille(arbre);
    RECORD* tab[n];
    printf("Affichage des abonnes tries par ordre croissant selon un attribut\n");
    printf("Selon quel attribut voulez-vous les trier ?\n\n");

    printf("1) Prenom\n2) Nom\n3) Ville\n4) Code Postal\n5) Numero de telephone\n6) Adresse email\n7) Profession \n\n");

    printf("Entrez votre choix : ");
    fgets(choix, 3, stdin);

    if (choix[0] >= '1' && choix[0] <= '9') {
        filtre = choix[0] - 49;

        if (filtre == 0) {
            abr_display(arbre);
        } else {
            ABR_list(arbre, tab, &i);
            clock_gettime(CLOCK_REALTIME, &debut);
            merge_sort(tab, n, filtre);
            // quick_sort(tab, n, filtre);
            clock_gettime(CLOCK_REALTIME, &fin);
            display_sorted_records(tab, n);
            printf("Le temps d'execution du tri est de : %f millisecondes\n", (fin.tv_nsec - debut.tv_nsec)*0.000001);
        }
        return;
    } else {
        perror("Unknown input");
        return;
    }
}

/**
 * Julien
 * Ajoute tous les pointeurs vers les RECORD du ABR dans le tableau
 * @param arbre : Pointeur vers le ABR source
 * @param liste : Pointeur vers le tableau de pointeur de RECORD recepteur
 */
void ABR_list(ABR* arbre, RECORD* tab[], int* i) {
    if (!abr_est_vide(arbre)) {
        ABR_list(arbre->fils_gauche, tab, i);
        for (int j = 0; j < arbre->nb_abonnes; j++) tab[(*i)++] = arbre->abonnes[j];
        ABR_list(arbre->fils_droit, tab, i);
    }
}

/**
 * Julien
 * Deplace les elements plus grand que le pivot a droite,
 * deplace les elements plus petit que le pivot a gauche puis
 * place le pivot au milieu de le tableau
 * @param tab : Pointeur vers le tableau contenant les RECORD
 * @param gauche : Indice du debut du sous tableau
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
 * Julien
 * Effectue le tri rapide
 * @param tab : Pointeur vers le tableau contenant les RECORD
 * @param gauche : Indice du debut du sous tableau
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
 * Julien
 * Appelle la fonction de tri rapide recursif
 * @param tab : Pointeur vers le tableau contenant les RECORD
 * @param taille : Taille du tableau contenant tous les RECORD
 * @param filter : 0 <= filter <= 7 : Indice de la colonne selon laquelle les RECORD vont être trier
 */
void quick_sort(RECORD* tab[],const int taille, int filter) {
    quick_sort_rec(tab, 0, taille-1, filter);
}

/**
 * Julien
 * Effectue la fusion des deux sous tableaux
 * @param tab : Tableau de pointeurs de RECORD
 * @param debut : Indice du premier élément du sous tableau gauche
 * @param milieu : Indice du milieu
 * @param fin : Indice du dernier élément du sous tableau droit
 * @param filter : 0 <= filter < 7 : Indice de la colonne dans laquelle on effectue le tri
 */
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
 * Julien
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
 * Julien
 * Appelle la fonction de tri fusion recursif
 * @param tab : Pointeur vers le tableau contenant les RECORD
 * @param taille : Taille du tableau contenant les RECORD
 * @param filter : 0 <= filter <= 7 : Indice de la colonne selon laquelle les RECORD vont être trier
 */
void merge_sort(RECORD* tab[], const int taille, int filter) {
    merge_sort_rec(tab, 0, taille-1, filter);
}

/**
 * Julien
 * Affiche tous les RECORD de le tableau
 * @param tab : Pointeur vers le tableau contenant les RECORD
 */
void display_sorted_records(RECORD* tab[], const int taille)
{
    int i;
    for (i = 0; i < taille; i++) rdisplay(tab[i]);
}
