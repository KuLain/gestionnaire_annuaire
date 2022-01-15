//
// Created by julie on 11/12/2021.
//

#ifndef SAE_1_2_ARBREBINAIRERECHERCHE_H
#define SAE_1_2_ARBREBINAIRERECHERCHE_H

#include "Record.h"

typedef struct ArbreBinaireRecherche {
    RECORD **abonnes;
    int hauteur, facteur_eq;
    int nb_abonnes;
    struct ArbreBinaireRecherche *fils_gauche;
    struct ArbreBinaireRecherche *fils_droit;
} ABR;

ABR *abr_init();

int abr_est_vide(ABR *);

int abr_est_feuille(ABR *);

int abr_taille(ABR *);

void abr_inserer(ABR **, char *, char *, RECORD *);

void abr_supprimer(ABR **, char[], char[], int, char[], void*);

RECORD *abr_valeur(ABR *, char[], char[], int, char[]);

void abr_free(ABR *);

#endif //SAE_1_2_ARBREBINAIRERECHERCHE_H
