//
// Created by julie on 11/12/2021.
//

#include "../../header/struct/ArbreBinaireRecherche.h"
#include <stdlib.h>
#include <string.h>

ABR *abr_init() {
    ABR *tmp = (ABR *) malloc(sizeof(ABR));
    tmp->abonne = NULL;
    tmp->fils_droit = NULL;
    tmp->fils_gauche = NULL;
    return tmp;
}

int abr_est_vide(ABR *arbre) {
    return (arbre->abonne == NULL && arbre->fils_droit == NULL && arbre->fils_gauche == NULL) || arbre == NULL;
}

int abr_est_feuille(ABR *arbre) {
    return arbre->fils_droit == NULL && arbre->fils_gauche == NULL;
}

int abr_taille(ABR *arbre) {
    if (abr_est_vide(arbre)) {
        return 0;
    } else if (abr_est_feuille(arbre)) {
        return 1;
    } else {
        return abr_taille(arbre->fils_droit) + abr_taille(arbre->fils_droit) + 1;
    }
}

int choix_branche(ABR *arbre, char prenom[], char nom[]) {
    if (strcmp(prenom, arbre->abonne->data[PRENOM]) == 0) {
        if (strcmp(nom, arbre->abonne->data[NOM]) > 0) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (strcmp(prenom, arbre->abonne->data[PRENOM]) > 0) {
            return 1;
        } else {
            return 0;
        }
    }
}

void abr_inserer(ABR *arbre, char *prenom, char *nom, RECORD *valeur) {
    if (abr_est_vide(arbre)) {
        arbre->abonne = valeur;
        arbre->fils_gauche = abr_init();
        arbre->fils_droit = abr_init();
    } else {
        if (choix_branche(arbre, prenom, nom) == 1) {
            abr_inserer(arbre->fils_droit, prenom, nom, valeur);
        } else {
            abr_inserer(arbre->fils_gauche, prenom, nom, valeur);
        }
    }
}

void suppression(ABR **arbre) {
    if (abr_est_feuille(*arbre)) {
        abr_free(*arbre);
        *arbre = abr_init();
    } else if (abr_est_vide((*arbre)->fils_gauche)) {
        abr_free((*arbre)->fils_gauche);
        ABR *tmp = *arbre;
        *arbre = (*arbre)->fils_droit;
        tmp->fils_gauche = NULL;
        tmp->fils_droit = NULL;
        abr_free(tmp);
    } else if (abr_est_vide((*arbre)->fils_droit)) {
        abr_free((*arbre)->fils_droit);
        ABR *tmp = *arbre;
        *arbre = (*arbre)->fils_gauche;
        tmp->fils_gauche = NULL;
        tmp->fils_droit = NULL;
        abr_free(tmp);
    } else {
        ABR *tmp = (*arbre)->fils_droit;
        while (!abr_est_vide(tmp->fils_gauche)) tmp = tmp->fils_gauche;
        abr_free(tmp->fils_gauche);
        tmp->fils_gauche = (*arbre)->fils_gauche;
        tmp = *arbre;
        *arbre = (*arbre)->fils_droit;
        tmp->fils_gauche = NULL;
        tmp->fils_droit = NULL;
        abr_free(tmp);
    }
}

void abr_supprimer(ABR *arbre, char prenom[], char nom[], int colomne, char filtre[]) {
    if (abr_est_vide(arbre)) {
        printf("Aucun abonné n'est associé à ces informations\n");
    } else {
        if (strcmp(prenom, arbre->abonne->data[PRENOM]) == 0 && strcmp(nom, arbre->abonne->data[NOM]) == 0 &&
            strcmp(filtre, arbre->abonne->data[colomne]) == 0) {
            suppression(&arbre);
        } else {
            switch (choix_branche(arbre, prenom, nom)) {
                case 1:
                    abr_supprimer(arbre->fils_droit, prenom, nom, colomne, filtre);
                    break;
                case 0:
                    abr_supprimer(arbre->fils_gauche, prenom, nom, colomne, filtre);
                    break;
            }
        }
    }
}

RECORD* abr_valeur(ABR *arbre, char prenom[], char nom[], int colomne, char filtre[]) {
    if (abr_est_vide(arbre)) {
        printf("Aucun abonné n'est associé à ces informations\n");
        return NULL;
    } else {
        if (strcmp(prenom, arbre->abonne->data[PRENOM]) == 0 && strcmp(nom, arbre->abonne->data[NOM]) == 0 &&
            strcmp(filtre, arbre->abonne->data[colomne]) == 0) {
            return arbre->abonne;
        } else {
            switch (choix_branche(arbre, prenom, nom)) {
                case 1:
                    abr_valeur(arbre->fils_droit, prenom, nom, colomne, filtre);
                    break;
                case 0:
                    abr_valeur(arbre->fils_gauche, prenom, nom, colomne, filtre);
                    break;
            }
        }
    }
}

void abr_display(ABR *arbre) {
    if (!abr_est_vide(arbre)) {
        abr_display(arbre->fils_gauche);
        rdisplay(arbre->abonne);
        abr_display(arbre->fils_droit);
    }
}

void abr_free(ABR *arbre) {
    if (!abr_est_vide(arbre)) {
        abr_est_vide(arbre->fils_gauche);
        abr_est_vide(arbre->fils_droit);
        rfree(arbre->abonne);
    }
    free(arbre);
}