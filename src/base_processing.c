//
// Created by julie on 27/11/2021.
//

#include "../header/base_processing.h"
#include <string.h>
#include <stdlib.h>

void add_record(AARRAY* array) {
    RECORD* client;
    char **tmp = malloc(sizeof(char*));
    int i, n;

    printf("Entrez les informations du client\n");

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
        fgets(tmp[i], 150, stdin);
        n = strlen(tmp[i]);
        tmp[i][n-1] = '\0';
        tmp[i] = realloc(tmp[i], sizeof(char)*n);
    }
    client = rinit(tmp);
    aapush(array, client->data[0], client->data[1], client);
}