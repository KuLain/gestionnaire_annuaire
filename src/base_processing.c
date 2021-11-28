//
// Created by julie on 27/11/2021.
//

#include "../header/base_processing.h"
#include "../header/file_processing.h"
#include <string.h>
#include <stdlib.h>

void add_record(AARRAY* array, char path[], char delim) {
    RECORD* client;
    FILE *fp;
    char **tmp;
    int i, n;

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
    printf("\n");

    client = rinit(tmp);
    aapush(array, client->data[0], client->data[1], client);

    fp = fopen(path, "a");
    for (i = 0; i < 6; i++) {
        fprintf(fp,"%s%c",client->data[i],delim);
    }
    fprintf(fp,"%s\n",client->data[6]);
    fclose(fp);
}

void delete_record(AARRAY* array, char path[], char delim) {
    char choix[3];
    char prenom[50];
    char nom[50];
    char filtre[100];

    printf("Entrez les informations du client à supprimer\n\n");
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
            break;
    }

    aarray_csv(array, path, delim);
}