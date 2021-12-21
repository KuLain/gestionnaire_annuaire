//
// Created by julie on 11/12/2021.
//

#include "../../header/struct/ArbreBinaireRecherche.h"
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

ABR *abr_init() {
    ABR *tmp = (ABR *) malloc(sizeof(ABR));
    tmp->abonnes = NULL;
    tmp->hauteur = tmp->facteur_eq = 0;
    tmp->nb_abonnes = -1;
    tmp->fils_droit = NULL;
    tmp->fils_gauche = NULL;
    return tmp;
}

int abr_est_vide(ABR *arbre) {
    return arbre->abonnes == NULL;
}

int abr_est_feuille(ABR *arbre) {
    return arbre->fils_droit == NULL && arbre->fils_gauche == NULL;
}

int abr_taille(ABR *arbre) {
    if (abr_est_vide(arbre)) {
        return 0;
    } else if (abr_est_feuille(arbre)) {
        return arbre->nb_abonnes;
    } else {
        return abr_taille(arbre->fils_droit) + abr_taille(arbre->fils_gauche) + arbre->nb_abonnes;
    }
}

int choix_branche(ABR *arbre, char prenom[], char nom[]) {
    if (strcmp(prenom, arbre->abonnes[0]->data[PRENOM]) == 0) {
        if (strcmp(nom, arbre->abonnes[0]->data[NOM]) > 0) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (strcmp(prenom, arbre->abonnes[0]->data[PRENOM]) > 0) {
            return 1;
        } else {
            return 0;
        }
    }
}

int sont_egales(char *chaine1, char *chaine2) {
    return strcmp(chaine1, chaine2) == 0;
}

int recherche_seq(ABR *arbre, char *filtre, int colonne) {
    for (int i = 0; i < arbre->nb_abonnes; i++) {
        if (sont_egales(arbre->abonnes[i]->data[colonne], filtre)) {
            return i;
        }
    }
    return -1;
}

void suppression_indice(ABR *arbre, int indice) {
    rfree(arbre->abonnes[indice]);
    for (int i = indice; i < arbre->nb_abonnes - 1; i++) arbre->abonnes[i] = arbre->abonnes[i + 1];
    arbre->abonnes = realloc(arbre->abonnes, sizeof(RECORD *) * (--arbre->nb_abonnes));
}


void ll_rotation(ABR **noeud) {
    ABR *main = (*noeud)->fils_gauche;
    ABR *fd = *noeud;

    fd->fils_gauche = main->fils_droit;
    main->fils_droit = fd;

    *noeud = main;
}

void rr_rotation(ABR **noeud) {
    ABR *fg = *noeud;
    ABR *main = (*noeud)->fils_droit;

    fg->fils_droit = main->fils_gauche;
    main->fils_gauche = fg;

    *noeud = main;
}

void rl_rotation(ABR **noeud) {
    ABR *fg = *noeud;
    ABR *main = (*noeud)->fils_droit->fils_gauche;
    ABR *fd = (*noeud)->fils_droit;

    fd->fils_droit = fg->fils_droit->fils_droit;
    fg->fils_droit = main->fils_gauche;
    fd->fils_gauche = main->fils_droit;

    main->fils_droit = fd;
    main->fils_gauche = fg;

    *noeud = main;
}

void lr_rotation(ABR **noeud) {
    ABR *fg = *noeud;
    ABR *main = (*noeud)->fils_gauche->fils_droit;
    ABR *fd = (*noeud)->fils_gauche;

    fg->fils_gauche = fd->fils_gauche;
    fd->fils_droit = fg->fils_droit;
    fg->fils_droit = main->fils_gauche;
    fd->fils_gauche = main->fils_droit;

    main->fils_gauche = fg;
    main->fils_droit = fd;

    *noeud = main;
}

void abr_inserer(ABR **arbre, char *prenom, char *nom, RECORD *valeur) {
    if (abr_est_vide(*arbre)) {
        (*arbre)->abonnes = (RECORD **) malloc(sizeof(RECORD *));
        (*arbre)->abonnes[0] = valeur;
        (*arbre)->nb_abonnes = 1;
        (*arbre)->hauteur = 1;
        (*arbre)->facteur_eq = 0;
        (*arbre)->fils_gauche = abr_init();
        (*arbre)->fils_droit = abr_init();
    } else if (sont_egales((*arbre)->abonnes[0]->data[PRENOM], prenom) &&
               sont_egales((*arbre)->abonnes[0]->data[NOM], nom)) {
        (*arbre)->abonnes = (RECORD **) realloc((*arbre)->abonnes, sizeof(RECORD *) * (++(*arbre)->nb_abonnes));
        (*arbre)->abonnes[(*arbre)->nb_abonnes - 1] = valeur;
    } else {
        if (choix_branche((*arbre), prenom, nom) == 1) {
            abr_inserer(&(*arbre)->fils_droit, prenom, nom, valeur);
            (*arbre)->hauteur = max((*arbre)->fils_gauche->hauteur, (*arbre)->fils_droit->hauteur) + 1;
            (*arbre)->facteur_eq = (*arbre)->fils_gauche->hauteur - (*arbre)->fils_droit->hauteur;
            if ((*arbre)->facteur_eq == -2) {
                rr_rotation(arbre);
            } else if ((*arbre)->facteur_eq == 2 && (*arbre)->fils_gauche->facteur_eq == -1) {
                lr_rotation(arbre);
            }
        } else {
            abr_inserer(&(*arbre)->fils_gauche, prenom, nom, valeur);
            (*arbre)->hauteur = max((*arbre)->fils_gauche->hauteur, (*arbre)->fils_droit->hauteur) + 1;
            (*arbre)->facteur_eq = (*arbre)->fils_gauche->hauteur - (*arbre)->fils_droit->hauteur;
            if ((*arbre)->facteur_eq == 2) {
                ll_rotation(arbre);
            } else if ((*arbre)->facteur_eq == -2 && (*arbre)->fils_droit->facteur_eq == 1) {
                rl_rotation(arbre);
            }
            (*arbre)->facteur_eq = (*arbre)->fils_gauche->facteur_eq = (*arbre)->fils_droit->facteur_eq = 0;
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

void abr_supprimer(ABR **arbre, char prenom[], char nom[], int colomne, char filtre[]) {
    if (abr_est_vide(*arbre)) {
        printf("Aucun abonné n'est associé à ces informations\n");
    } else {
        if (sont_egales(prenom, (*arbre)->abonnes[0]->data[PRENOM]) && sont_egales(nom, (*arbre)->abonnes[0]->data[NOM])){
            if ((*arbre)->nb_abonnes > 1) {
                suppression_indice((*arbre), recherche_seq((*arbre), filtre, colomne));
            } else {
                suppression(arbre);
            }
        } else {
            switch (choix_branche((*arbre), prenom, nom)) {
                case 1:
                    abr_supprimer(&(*arbre)->fils_droit, prenom, nom, colomne, filtre);
                    break;
                case 0:
                    abr_supprimer(&(*arbre)->fils_gauche, prenom, nom, colomne, filtre);
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
        if (sont_egales(prenom, arbre->abonnes[0]->data[PRENOM]) && sont_egales(nom, arbre->abonnes[0]->data[NOM])) {
            return arbre->abonnes[recherche_seq(arbre, filtre, colomne)];
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
        for (int i = 0; i < arbre->nb_abonnes; i++) rdisplay(arbre->abonnes[i]);
        abr_display(arbre->fils_droit);
    }
}

void abr_free(ABR *arbre) {
    if (arbre != NULL && !abr_est_vide(arbre)) {
        abr_free(arbre->fils_gauche);
        abr_free(arbre->fils_droit);
        for (int i = 0; i < arbre->nb_abonnes; i++) rfree(arbre->abonnes[i]);
        free(arbre->abonnes);
    }
    free(arbre);
}