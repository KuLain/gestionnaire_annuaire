//
// Created by julie on 27/11/2021.
//

#include "../header/base_processing.h"
#include "../header/file_processing.h"
#include <string.h>
#include <stdlib.h>

/**
 * Affiche les champs pour remplir les données d'un abonné à ajouter et effectue l'ajout
 * @param array : Pointeur vers AARRAY
 * @param path : Chemin vers le fichier CSV
 * @param delim : Caractère délimiteur
 */
void add_record(AARRAY* array, char path[], char delim) {
    RECORD* client;
    FILE *fp;
    char **tmp = (char**)malloc(sizeof(char*)*7);
    int i, n;

    printf("Ajout d'un abonnée\n");
    printf("Entrez les informations du client à ajouter\n\n");

    for (i = 0; i < 7; i++) {
        switch (i) {
            case 0:
                printf("Entrez le prénom : ");
                break;
            case 1:
                printf("Entrez le nom : ");
                break;
            case 2:
                printf("Entrez la ville : ");
                break;
            case 3:
                printf("Entrez le code postal : ");
                break;
            case 4:
                printf("Entrez le numéro de téléphone : ");
                break;
            case 5:
                printf("Entrez l'adresse email : ");
                break;
            case 6:
                printf("Entrez la profession : ");
                break;
        }
        tmp[i] = malloc(sizeof(char)*150);
        if (tmp[i] == NULL) {
            perror("Error while allocating ");
            exit(EXIT_FAILURE);
        }
        fgets(tmp[i], 150, stdin);
        n = strlen(tmp[i]);
        tmp[i][n-1] = '\0';
        tmp[i] = realloc(tmp[i], sizeof(char)*(n-1));
        if (tmp[i] == NULL) {
            perror("Error while reallocating ");
            exit(EXIT_FAILURE);
        }
    }

    client = rinit(tmp);
    aapush(array, client->data[0], client->data[1], client);

    fp = fopen(path, "a");
    for (i = 0; i < 6; i++) {
        fprintf(fp,"%s%c",client->data[i],delim);
    }
    fprintf(fp,"%s\n",client->data[6]);
    fclose(fp);
    printf("\nAjout effectué\n");
    free(tmp);
}

/**
 * Affiche le menu de suppression d'un abonné et effectue la suppression
 * @param array : Pointeur vers AARRAY
 * @param path : Chemin vers le fichier CSV
 * @param delim : Caractère séparateur
 */
void delete_record(AARRAY* array, char path[], char delim) {
    char choix[3];
    char prenom[50];
    char nom[50];
    char filtre[100];

    printf("Suppression d'un abonnée\n");
    printf("Entrez les informations de l'abonné à supprimer\n\n");
    printf("Quels inforamtions voulez-vous utiliser ?\n");
    printf("1) Prénom, nom et numéro de téléphone\n");
    printf("2) Prénom, nom et adresse email\n\n");
    printf("Entrez une valeur : ");
    fgets(choix, 3, stdin);

    printf("Entrez le prénom : ");
    fgets(prenom, 50, stdin);
    prenom[strlen(prenom)-1] = '\0';
    printf("Entrez le nom : ");
    fgets(nom, 50, stdin);
    nom[strlen(nom)-1] = '\0';

    switch (choix[0]) {
        case '1':
            printf("Entrez le numéro de téléphone : ");
            fgets(filtre, 100, stdin);
            filtre[strlen(filtre)-1] = '\0';
            aapop(array, prenom, nom, NULL, filtre);
            break;
        case '2':
            printf("Entrez l'adresse email : ");
            fgets(filtre, 100, stdin);
            filtre[strlen(filtre)-1] = '\0';
            aapop(array, prenom, nom, filtre, NULL);
            break;
        default:
            perror("Unknown input");
            return;
    }
    printf("\nSuppression effectué\n");
    aarray_csv(array, path, delim);
}

/**
 * Affiche le menu de changement des données d'un abonné et effectue le changement
 * @param array : Pointeur vers AARRAY
 * @param path : Chemin vers le fichier CSV
 * @param delim : Caractère séparateur
 */
void change_record(AARRAY* array, char path[], char delim) {
    char choix[3], infos[3][100];
    char *valeur = malloc(sizeof(char)*100);
    int i,n;
    RECORD* abonne;

    if (valeur == NULL) {
        perror("Error while allocation ");
        exit(EXIT_FAILURE);
    }

    printf("Changement des données d'un abonné\n");
    printf("Comment séléctionner l'abonnée ?\n\n");
    printf("1) Avec le prénom, nom et adresse email\n");
    printf("2) Avec le prénom, nom et numéro de téléphone\n");
    printf("*) Retour\n\n");

    printf("Entrez une valeur : ");
    fgets(choix, 3, stdin);

    printf("\n");

    printf("Entrez le prénom : ");
    fgets(infos[0], 100, stdin);
    infos[0][strlen(infos[0])-1] = '\0';
    printf("Entrez le nom : ");
    fgets(infos[1], 100, stdin);
    infos[1][strlen(infos[1])-1] = '\0';

    switch (choix[0]) {
        case '1':
            printf("Entrez l'adresse email : ");
            fgets(infos[2], 100, stdin);
            infos[2][strlen(infos[2])-1] = '\0';
            abonne = aavalue_mail(array, infos[0], infos[1], infos[2]);
            break;
        case '2':
            printf("Entrez le numéro de téléphone : ");
            fgets(infos[2], 100, stdin);
            infos[2][strlen(infos[2])-1] = '\0';
            abonne = aavalue_phone(array, infos[0], infos[1], infos[2]);
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
    printf("1) Prénom\n");
    printf("2) Nom\n");
    printf("3) Ville\n");
    printf("4) Code postal\n");
    printf("5) Numéro de téléphone\n");
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
    valeur[n-1] = '\0';
    valeur = realloc(valeur, sizeof(char)*(n-1));
    if (valeur == NULL) {
        perror("Error while reallocating ");
        exit(EXIT_FAILURE);
    }

    if (i == 0 || i == 1) {
        aapop_resize(array, abonne->data[0], abonne->data[1], abonne->data[5], NULL);
        free(abonne->data[i]);
        abonne->data[i] = valeur;
        aapush(array, abonne->data[0], abonne->data[1], abonne);
    } else {
        free(abonne->data[i]);
        abonne->data[i] = valeur;
    }

    aarray_csv(array, path, delim);
    printf("\nChangement effectué\n\n");
}

/**
 *  Affiche le menu d'accès à un abonné
 * @param array : Pointeur vers AARRAY
 */
void access_record(AARRAY* array)
{
    char choix[3], infos[3][100];

    printf("Accès à un abonné\n");
    printf("Comment séléctionner l'abonné ?\n\n");
    printf("1) Avec le prénom, nom et adresse email\n");
    printf("2) Avec le prénom, nom et numéro de téléphone\n");
    printf("*) Retour\n\n");

    printf("Entrez une valeur : ");
    fgets(choix, 3, stdin);

    printf("\nEntrez le prénom : ");
    fgets(infos[0], 100, stdin);
    infos[0][strlen(infos[0])-1] = '\0';
    printf("Entrez le nom : ");
    fgets(infos[1], 100, stdin);
    infos[1][strlen(infos[1])-1] = '\0';

    switch (choix[0]) {
        case '1':
            printf("Entrez l'adresse email : ");
            fgets(infos[2], 100, stdin);
            infos[2][strlen(infos[2])-1] = '\0';
            rdisplay(aavalue_mail(array, infos[0], infos[1], infos[2]));
            break;
        case '2':
            printf("Entrez le numéro de téléphone : ");
            fgets(infos[2], 100, stdin);
            infos[2][strlen(infos[2])-1] = '\0';
            printf("\n");
            rdisplay(aavalue_phone(array, infos[0], infos[1], infos[2]));
            break;
        default:
            printf("Erreur\n");
            perror("No data associated with thoses keys ");
            break;
    }
    printf("\n");
}