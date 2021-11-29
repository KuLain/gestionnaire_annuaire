#include <stdio.h>
#include "header/file_processing.h"
#include "header/base_processing.h"
#include "header/sorted_display.h"
#include "header/filtered_display.h"

#define PATH "files/gang.csv"
#define DELIM ','

int main() {
    AARRAY* dico = aainit(10);
    char choix[3];
    int active = 1;
    parse_csv(dico, PATH, DELIM);

    printf("Bienvenue dans le gestionnaire d'annuaire !\n\n");

    while (active == 1) {

        printf("Que voulez-vous faire ?\n\n");
        printf("1) Ajouter un abonné\n");
        printf("2) Supprimer un abonné\n");
        printf("3) Modifier les données d'un abonné\n");
        printf("4) Afficher un abonné\n");
        printf("5) Afficher tous les abonnés\n");
        printf("6) Afficher tous les abonnés par trié selon un critère\n");
        printf("7) Afficher tous les abonnés par trié selon un filtre\n");
        printf("8) Afficher les abonnés ayant une valeur inconnue\n");
        printf("*) Quitter\n\n");

        printf("Entrez votre selection : ");
        fgets(choix, 3, stdin);
        printf("\n");

        switch (choix[0]) {
            case '1':
                add_record(dico, PATH, DELIM);
                break;
            case '2':
                delete_record(dico, PATH, DELIM);
                break;
            case '3':
                change_record(dico, PATH, DELIM);
                break;
            case '4':
                access_record(dico);
                break;
            case '5':
                aadisplay(dico);
                break;
            case '6':
                sorted_records(dico);
                break;
            case '7':
                filtered_records(dico);
                break;
            case '8':
                // TODO
                break;
            default:
                active = 0;
                break;
        }

        printf("\n");

    }
    return 0;
}
