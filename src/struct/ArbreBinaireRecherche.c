//
// Created by julie on 11/12/2021.
//

#include "../../header/struct/ArbreBinaireRecherche.h"
#include <stdlib.h>
#include <string.h>

ABR *abr_init() {
    ABR *tmp = (ABR *) malloc(sizeof(ABR));
    tmp->cle = NULL;
    tmp->abonne = NULL;
    tmp->fils_droit = NULL;
    tmp->fils_gauche = NULL;
    return tmp;
}

int abr_est_vide(ABR *arbre) {
    return arbre->cle == NULL && arbre->abonne == NULL && arbre->fils_droit == NULL && arbre->fils_gauche == NULL;
}

int abr_est_feuille(ABR *arbre) {
    return arbre->fils_droit == NULL && arbre->fils_gauche == NULL;
}

int abr_taille(ABR* arbre) {
    if (abr_est_vide(arbre)) {
        return 0;
    } else if (abr_est_feuille(arbre)) {
        return 1;
    } else {
        return abr_taille(arbre->fils_droit) + abr_taille(arbre->fils_droit) + 1;
    }
}

void abr_inserer(ABR *arbre, char *prenom, char *nom, RECORD *valeur) {
    if (abr_est_vide(arbre)) {
        char *tmp = (char *) malloc(sizeof(char) * (strlen(prenom) + strlen(nom) + 1));
        strcpy(tmp, prenom);
        strcat(tmp, nom);

        arbre->cle = tmp;
        arbre->abonne = valeur;
        arbre->fils_gauche = abr_init();
        arbre->fils_droit = abr_init();
    } else {
        char tmp[strlen(prenom) + strlen(nom) + 1];
        strcpy(tmp, prenom);
        strcat(tmp, nom);

        if (strcmp(tmp, arbre->cle) > 0) {
            abr_inserer(arbre->fils_droit, prenom, nom, valeur);
        } else {
            abr_inserer(arbre->fils_gauche, prenom, nom, valeur);
        }
    }
}

void abr_supprimer(ABR* arbre, char prenom[], char nom[], char telephone[], char mail[]) {
    // TODO
}

RECORD *abr_valeur(ABR *arbre, char prenom[], char nom[], char telephone[], char mail[]) {
    if (abr_est_vide(arbre) == 1) {
        return NULL;
    }
    if (strcmp(telephone, "") == 0) {
        if (strcmp(prenom, arbre->abonne->data[PRENOM]) == 0 && strcmp(nom, arbre->abonne->data[NOM]) == 0 &&
            strcmp(mail, arbre->abonne->data[MAIL]) == 0) {
            return arbre->abonne;
        } else {
            char tmp[strlen(prenom) + strlen(nom) + 1];
            strcpy(tmp, prenom);
            strcat(tmp, nom);
            if (strcmp(tmp, arbre->cle) > 0) {
                return abr_valeur(arbre->fils_droit, prenom, nom, "", mail);
            } else {
                return abr_valeur(arbre->fils_gauche, prenom, nom, "", mail);
            }
        }
    } else {
        if (strcmp(prenom, arbre->abonne->data[0]) == 0 && strcmp(nom, arbre->abonne->data[1]) == 0 &&
            strcmp(telephone, arbre->abonne->data[TELEPHONE]) == 0) {
            return arbre->abonne;
        } else {
            char tmp[strlen(prenom) + strlen(nom) + 1];
            strcpy(tmp, prenom);
            strcat(tmp, nom);
            if (strcmp(tmp, arbre->cle) > 0) {
                return abr_valeur(arbre->fils_droit, prenom, nom, telephone, "");
            } else {
                return abr_valeur(arbre->fils_gauche, prenom, nom, telephone, "");
            }
        }
    }
}

void abr_display(ABR* arbre) {
    if (!abr_est_vide(arbre)) {
        rdisplay(arbre->abonne);
        abr_display(arbre->fils_gauche);
        abr_display(arbre->fils_droit);
    }
}

void abr_free(ABR *arbre) {
    if (!abr_est_vide(arbre)) {
        abr_est_vide(arbre->fils_gauche);
        abr_est_vide(arbre->fils_droit);
        rfree(arbre->abonne);
        free(arbre->cle);
    }
    free(arbre);
}