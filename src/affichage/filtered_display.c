#include "struct/ArbreBinaireRecherche.h"
#include "affichage/filtered_display.h"
#include <string.h>
#include <time.h>

/**
 * Julien
 * Affiche le menu pour choisir comment filtrer les RECORD
 * @param arbre : Pointeur vers le ABR contenant les RECORD
 */
void filtered_records(ABR *arbre) {
    char choix[3], filter[150];
    int column;
    struct timespec debut, fin;

    printf("Selection des abonnes par filtre\n");
    printf("Selon quel critere voulez-vous filter les abonnes ?\n\n");
    printf("1) Prenom\n");
    printf("2) Nom\n");
    printf("3) Ville\n");
    printf("4) Code postal\n");
    printf("5) Numero de telephone\n");
    printf("6) Adresse email\n");
    printf("7) Profession\n");
    printf("*) Retour au menu principal\n\n");

    printf("Entrez votre selection : ");
    fgets(choix, 3, stdin);
    printf("\n");

    if (choix[0] >= '1' && choix[0] <= '7') {
        column = choix[0] - 49;
    } else {
        return;
    }

    printf("Entrez le fitre souhaite : ");
    fgets(filter, 150, stdin);
    filter[strlen(filter) - 1] = '\0';
    clock_gettime(CLOCK_REALTIME, &debut);
    matching_filter(arbre, column, filter);
    clock_gettime(CLOCK_REALTIME, &fin);
    printf("Le temps d'execution du filtre est de : %f millisecondes\n", (fin.tv_nsec - debut.tv_nsec) * 0.000001);
}

/**
 * Julien
 * Vérifie si le pattern est prefix de la chaine source
 * @param source : Chaine source
 * @param pattern : Pattern à verifier
 * @return 1 si le pattern est préfixe de la chaine source, 0 sinon
 */
int matching_pattern(char *source, char pattern[], int const taille_filtre) {
    int k = 0;
    const int n = strlen(source);
    while (k < n && source[k] == pattern[k]) k++;
    return k == taille_filtre;
}

/**
 * Julien
 * Ajoute les abonnés ayant pour préfixe filtre dans tab
 * @param arbre : Pointeur vers l'ABR contenant les abonnés
 * @param column : 0 <= column < 7 : Colonne sur laquelle appliquer le filtre
 * @param filtre : Chaine de caractère que l'on cherche en prefix
 * @param taille_filtre : Taille du filtre
 * @param tab : Tableau de pointeurs de RECORD contenant les abonnés
 * @param i
 */
void matching_filter_rec(ABR *arbre, int column, char filtre[], int taille_filtre, RECORD *tab[], int *i) {
    if (!abr_est_vide(arbre)) {
        for (int j = 0; j < arbre->nb_abonnes; j++) {
            if (matching_pattern(arbre->abonnes[j]->data[column], filtre, taille_filtre))
                tab[(*i)++] = arbre->abonnes[j];
        }
        matching_filter_rec(arbre->fils_gauche, column, filtre, taille_filtre, tab, i);
        matching_filter_rec(arbre->fils_droit, column, filtre, taille_filtre, tab, i);
    }
}

/**
 * Julien
 * Affiche les RECORD correspondant au filtre
 * @param arbre : Pointeur vers le ABR
 * @param column : 0 <= column <= 7 : Indice de la colonne dans laquel on applique le filtre
 * @param filter : Filtre à appliquer
 */
void matching_filter(ABR *arbre, int column, char filter[]) {
    const int taille = abr_taille(arbre);
    const int n = strlen(filter);
    int i = 0, j;
    RECORD *matching_patterns[taille];

    matching_filter_rec(arbre, column, filter, n, matching_patterns, &i);

    for (j = 0; j < i; j++) rdisplay(matching_patterns[j]);
}

