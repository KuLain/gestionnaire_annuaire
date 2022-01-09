#include <stdio.h>
#include <string.h>

#include "header/file_processing.h"
#include "header/base_processing.h"
#include "header/filtered_display.h"
#include "header/sorted_display.h"
#include "header/empty_display.h"

int main() {
    ABR* base = abr_init();
    char choix[3], chemin[150], delim[2];
    int active = 1;

    printf("Entrez le chemin vers le fichier : ");
    fgets(chemin, 150, stdin);
    chemin[strlen(chemin)-1] = '\0';

    printf("Entrez le caractere delimiteur du CSV : ");
    fgets(delim, 2, stdin);

    parse_csv(&base, chemin, delim[0]);

    printf("Bienvenue dans le gestionnaire d'annuaire !\n\n");

    while (active) {

        printf("Que voulez-vous faire ?\n\n");
        printf("1) Ajouter un abonné\n");
        printf("2) Supprimer un abonné\n");
        printf("3) Modifier les données d'un abonné\n");
        printf("4) Afficher un abonné\n");
        printf("5) Afficher tous les abonnés\n");
        printf("6) Afficher tous les abonnés trié selon un critère\n");
        printf("7) Afficher tous les abonnés trié selon un filtre\n");
        printf("8) Afficher les abonnés avec des attributs manquants\n");
        printf("*) Quitter\n\n");

        printf("Entrez votre selection : ");
        do {
            fgets(choix, 3, stdin);
        } while (choix[0] == '\n');

        printf("\n");

        switch (choix[0]) {
            case '1':
                add_record(&base, chemin, delim);
                break;
            case '2':
                delete_record(&base, chemin, delim);
                break;
            case '3':
                change_record(base, chemin, delim);
                break;
            case '4':
                access_record(base);
                break;
            case '5':
                abr_display(base);
                break;
            case '6':
                sorted_records(base);
                break;
            case '7':
                filtered_records(base);
                break;
            case '8':
                missing_record(base);
                break;
            default:
                active = 0;
                abr_free(base);
                break;
        }

        printf("\n");

    }

    return 0;
}
