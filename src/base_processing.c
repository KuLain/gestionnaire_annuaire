#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../header/base_processing.h"

#define N 7

/**
 * Saimati
 * Affiche les champs pour remplir les donnees d'un abonne a ajouter et effectue l'ajout
 * @param arbre : Pointeur vers ABR
 * @param path : Chemin vers le fichier CSV
 * @param delim : Caractère delimiteur
 */
void add_record(ABR **arbre, char path[], char delim) {
    char **tab = malloc(sizeof(char *) * 7);
    int i;
    for (i = 0; i < 7; i++) tab[i] = malloc(sizeof(char) * 50);

    RECORD *abonne;

    printf("entre le prenom :");
    fgets(tab[0], 50, stdin);
    tab[0][strlen(tab[0]) - 1] = '\0';

    printf("entre le nom : ");
    fgets(tab[1], 50, stdin);
    tab[1][strlen(tab[1]) - 1] = '\0';

    printf("entre la  ville: ");
    fgets(tab[2], 50, stdin);
    tab[2][strlen(tab[2]) - 1] = '\0';

    printf("entre le code postal: ");
    fgets(tab[3], 50, stdin);
    tab[3][strlen(tab[3]) - 1] = '\0';

    printf("entre le num tel: ");
    fgets(tab[4], 50, stdin);
    tab[4][strlen(tab[4]) - 1] = '\0';

    printf("entre adresse mail:  ");
    fgets(tab[5], 50, stdin);
    tab[5][strlen(tab[5]) - 1] = '\0';

    printf("entre la profesion: ");
    fgets(tab[6], 50, stdin);
    tab[6][strlen(tab[6]) - 1] = '\0';

    abonne = rinit(tab);

    abr_inserer(arbre, tab[0], tab[1], abonne);

    for (i = 0; i <= 6; i++)
        free(tab[i]);
    free(tab);
}

/**
 * Saimati
 * Affiche le menu de suppression d'un abonne et effectue la suppression
 * @param arbre : Pointeur vers ABR
 * @param path : Chemin vers le fichier CSV
 * @param delim : Caractère separateur
 */
void delete_record(ABR **arbre, char path[], char delim) {
    char choix[3];
    char prenom[50];
    char nom[50];
    char filtre[100];

    printf("Suppression d'un abonnee\n");
    printf("Entrez les informations de l'abonne a supprimer\n\n");
    printf("Quels inforamtions voulez-vous utiliser ?\n");
    printf("1) Prenom, nom et numero de telephone\n");
    printf("2) Prenom, nom et adresse email\n\n");
    printf("Entrez une valeur : ");
    fgets(choix, 3, stdin);

    printf("Entrez le prenom : ");
    fgets(prenom, 50, stdin);
    prenom[strlen(prenom) - 1] = '\0';
    printf("Entrez le nom : ");
    fgets(nom, 50, stdin);
    nom[strlen(nom) - 1] = '\0';

    switch (choix[0]) {
        case '1':
            printf("Entrez le numero de telephone : ");
            fgets(filtre, 100, stdin);
            filtre[strlen(filtre) - 1] = '\0';
            abr_supprimer(arbre, prenom, nom, TELEPHONE, filtre);
            break;
        case '2':
            printf("Entrez l'adresse email : ");
            fgets(filtre, 100, stdin);
            filtre[strlen(filtre) - 1] = '\0';
            abr_supprimer(arbre, prenom, nom, MAIL, filtre);
            break;
        default:
            perror("Unknown input");
            return;
    }
    printf("\nSuppression effectue\n");
}

/**
 * Julien
 * Affiche le menu de changement des donnees d'un abonne et effectue le changement
 * @param arbre : Pointeur vers ABR
 * @param path : Chemin vers le fichier CSV
 * @param delim : Caractère separateur
 */
void change_record(ABR *arbre, char path[], char delim) {
    char choix[3], infos[3][100];
    char *valeur = malloc(sizeof(char) * 100);
    int i, n;
    RECORD *abonne, *new_abonne;

    if (valeur == NULL) {
        perror("Erreur lors de l'allocation");
        exit(EXIT_FAILURE);
    }

    printf("Changement des donnees d'un abonne\n");
    printf("Comment selectionner l'abonnee ?\n\n");
    printf("1) Avec le prenom, nom et adresse email\n");
    printf("2) Avec le prenom, nom et numero de telephone\n");
    printf("*) Retour\n\n");

    printf("Entrez une valeur : ");
    fgets(choix, 3, stdin);

    printf("\n");

    printf("Entrez le prenom : ");
    fgets(infos[0], 100, stdin);
    infos[0][strlen(infos[0]) - 1] = '\0';
    printf("Entrez le nom : ");
    fgets(infos[1], 100, stdin);
    infos[1][strlen(infos[1]) - 1] = '\0';

    switch (choix[0]) {
        case '1':
            printf("Entrez l'adresse email : ");
            fgets(infos[2], 100, stdin);
            infos[2][strlen(infos[2]) - 1] = '\0';
            abonne = abr_valeur(arbre, infos[0], infos[1], MAIL, infos[2]);
            break;
        case '2':
            printf("Entrez le numero de telephone : ");
            fgets(infos[2], 100, stdin);
            infos[2][strlen(infos[2]) - 1] = '\0';
            abonne = abr_valeur(arbre, infos[0], infos[1], TELEPHONE, infos[2]);
            break;
        default:
            return;
    }

    if (abonne == NULL) {
        free(valeur);
        return;
    }

    printf("\n");

    printf("Quel information de %s %s voulez-vous changer ?\n\n", abonne->data[0], abonne->data[1]);
    printf("1) Prenom\n");
    printf("2) Nom\n");
    printf("3) Ville\n");
    printf("4) Code postal\n");
    printf("5) Numero de telephone\n");
    printf("6) Adresse email\n");
    printf("7) Profession\n");
    printf("*) Retour au menu principal\n\n");

    printf("Entrez votre choix : ");
    fgets(choix, 3, stdin);
    switch (choix[0]) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
            i = choix[0] - 49;
            break;
        default:
            free(valeur);
            return;
    }

    printf("\nEntrez la nouvelle valeur : ");
    fgets(valeur, 100, stdin);
    n = strlen(valeur);
    valeur[n - 1] = '\0';
    valeur = realloc(valeur, sizeof(char) * (n - 1));
    if (valeur == NULL) {
        perror("Error while reallocating ");
        exit(EXIT_FAILURE);
    }


    if (i == 0 || i == 1) {
        new_abonne = r_copy(abonne);
        abr_supprimer(&arbre, abonne->data[PRENOM], abonne->data[NOM], MAIL, abonne->data[MAIL]);
        free(new_abonne->data[i]);
        new_abonne->data[i] = valeur;
        abr_inserer(&arbre, new_abonne->data[PRENOM], new_abonne->data[NOM], new_abonne);
    } else {
        free(abonne->data[i]);
        abonne->data[i] = valeur;
    }
    printf("\nChangement effectue\n\n");
}

/**
 * Julien
 *  Affiche le menu d'accès a un abonne
 * @param arbre : Pointeur vers ABR
 */
void access_record(ABR *arbre) {
    struct timespec debut, fin;
    char choix[3], infos[3][100];
    RECORD *ans;
    printf("Accss a un abonne\n");
    printf("Comment selectionner l'abonne ?\n\n");
    printf("1) Avec le prenom, nom et adresse email\n");
    printf("2) Avec le prenom, nom et numero de telephone\n");
    printf("*) Retour\n\n");


    printf("Entrez une valeur : ");
    fgets(choix, 3, stdin);

    if (choix[0] != '1' && choix[0] != '2' && choix[0] != '3') {
        return;
    }

    printf("\nEntrez le prenom : ");
    fgets(infos[0], 100, stdin);
    infos[0][strlen(infos[0]) - 1] = '\0';
    printf("Entrez le nom : ");
    fgets(infos[1], 100, stdin);
    infos[1][strlen(infos[1]) - 1] = '\0';

    switch (choix[0]) {
        case '1':
            printf("Entrez l'adresse email : ");
            fgets(infos[2], 100, stdin);
            infos[2][strlen(infos[2]) - 1] = '\0';
            printf("\n");
            clock_gettime(CLOCK_REALTIME, &debut);
            ans = abr_valeur(arbre, infos[0], infos[1], MAIL, infos[2]);
            clock_gettime(CLOCK_REALTIME, &fin);
            if (ans == NULL) {
                printf("Aucun abonne n'est associe a ces informations");
            } else {
                rdisplay(ans);
            }
            break;
        case '2':
            printf("Entrez le numero de telephone : ");
            fgets(infos[2], 100, stdin);
            infos[2][strlen(infos[2]) - 1] = '\0';
            printf("\n");
            clock_gettime(CLOCK_REALTIME, &debut);
            ans = abr_valeur(arbre, infos[0], infos[1], TELEPHONE, infos[2]);
            clock_gettime(CLOCK_REALTIME, &fin);
            if (ans == NULL) {
                printf("Aucun abonne n'est associe a ces informations\n");
            } else {
                rdisplay(ans);
            }
            break;
        default:
            printf("Erreur\n");
            perror("No data associated with thoses keys ");
            printf("\n");
            break;
    }
    printf("Le temps d'execution de la recherche est de : %lf millisecondes\n",
           (fin.tv_nsec - debut.tv_nsec) * 0.000001);
    printf("\n");
}