//
// Created by lain on 30/11/2021.
//

#include "../../header/struct/AssociativeArray.h"
#include "../../header/sorted_display.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

/**
 * Initialise les variables et alloue la mémoire du AARRAY
 * @param size : Poids de la puissance de 2 correspondant à la taille du tableau
 * @return : Pointeur vers le AARRAY
 */
AARRAY* aainit(int size)
{
    AARRAY* tmp = (AARRAY*) malloc(sizeof(AARRAY));
    tmp->size = pow(2,size);
    tmp->content = (LIST**) calloc(tmp->size,sizeof(LIST*));
    tmp->length = 0;
    return tmp;
}

/**
 * Fonction de hachage, application de la méthode de P.J. Weinberger
 * @param prenom : Pointeur vers la chaine correspondant au prénom du RECORD
 * @param nom : Pointeur vers la chaine correspondant au nom du RECORD
 * @param aa_size : Taille du tableau du AARRAY
 * @return : Indice correspondant aux clés prénom et nom
 */
int hash(char prenom[], char nom[], int aa_size)
{
    int i;
    long tmp;
    long somme = 0;
    int const p1 = pow(2,28);
    int const p2 = pow(2,24);

    for (i = 0; i < strlen(prenom); i++)
    {
        somme = (somme*16) + prenom[i];
        if (somme > p1) {
            tmp = (somme / p1) * p1;
            somme += tmp / p2;
            somme -= tmp;
        }
    }
    for (i = 0; i < strlen(nom); i++)
    {
        somme = (somme*16) + nom[i];
        if (somme > p1) {
            tmp = (somme / p1) * p1;
            somme += tmp / p2;
            somme -= tmp;
        }
    }
    return somme % aa_size;
}

/**
 * Ajoute le RECORD dans le AARRAY
 * @param array : Pointeur vers le AARRAY
 * @param prenom : Chaine de caractère correspondant au prénom
 * @param nom : Chaine de caractère correspondant au nom
 * @param elt : Pointeur vers le RECORD
 */
void aapush(AARRAY* array, char *prenom, char *nom, RECORD* elt)
{
    int indice = hash(prenom, nom, array->size);
    if (array->content[indice] == NULL) array->content[indice] = linit();
    lpush(array->content[indice], elt);
    array->length++;
}

/**
 * Effectue une recherche dichotomique dans la LIST
 * @param liste : Pointeur vers la LIST
 * @param mail : Pointeur vers la chaine de caractère correspondant au mail, NULL si ce n'est pas le filtre
 * @param phone : Pointeur vers la chaine de caractère correspondant au numéro de téléphone, NULL si ce n'est pas le filtre
 * @return : Indice du RECORD correspondant, -1 si il n'est pas dans la LIST
 */
int dichotomic_search(LIST *liste, char mail[], char phone[]) {
    int debut = 0;
    int fin = liste->length;
    int milieu, i_filtre;
    char filtre[150];
    if (mail == NULL) {
        i_filtre = 4;
        strcpy(filtre, phone);
    } else {
        i_filtre = 5;
        strcpy(filtre, mail);
    }

    while (debut <= fin) {
        milieu = (debut+fin)/2;
        if (strcmp(liste->content[milieu]->data[i_filtre], filtre) == 0) return milieu;
        if (strcmp(liste->content[milieu]->data[i_filtre], filtre) < 0) {
            debut = milieu + 1;
        } else {
            fin = milieu - 1;
        }
    }
    return -1;
}

/**
 * Permet d'accéder au RECORD associé à clé (prénom,nom) correspondant au mail
 * @param array : Pointeur vers la AARRAY
 * @param prenom : Chaine de caractère correspondant au prénom
 * @param nom : Chaine de caractère correspondant au nom
 * @param mail : Chaine de caractère correspondant au mail
 * @return Pointeur vers le RECORD correspondant à la clé (prénom,nom)
 */
RECORD* aavalue_mail(AARRAY* array, char prenom[], char nom[], char mail[])
{
    int index = hash(prenom, nom, array->size);
    LIST* tmp = array->content[index];
    if (tmp == NULL) {
        printf("No data associated with thoses keys ");
        return NULL;
    }
    merge_sort(tmp, 5);
    int i;


    i = dichotomic_search(tmp, mail, NULL);
    if (i == -1) {
        printf("No data associated with thoses keys ");
        return NULL;
    } else {
        return tmp->content[i];
    }
}

/**
 * Permet d'accéder au RECORD associé à clé (prénom,nom) correspondant au numéro de téléphone
 * @param array : Pointeur vers la AARRAY
 * @param prenom : Chaine de caractère correspondant au prénom
 * @param nom : Chaine de caractère correspondant au nom
 * @param mail : Chaine de caractère correspondant au numéro de téléphone
 * @return Pointeur vers le RECORD correspondant à la clé (prénom,nom)
 */
RECORD* aavalue_phone(AARRAY* array, char prenom[], char nom[], char phone[])
{
    int index = hash(prenom, nom, array->size);
    LIST* tmp = array->content[index];
    if (tmp == NULL) {
        printf("No data associated with thoses keys ");
        printf("\n");
        return NULL;
    }
    int i;
    merge_sort(tmp, 4);

    i = dichotomic_search(tmp, NULL, phone);
    if (i == -1) {
        printf("No data associated with thoses keys ");
        printf("\n");
        return NULL;
    } else {
        return tmp->content[i];
    }
}

/**
 * Supprime le RECORD correspondant à la clé (prénom,nom) avec le mail ou numéro de téléphone correspondant
 * et libère la mémoire associé à ce RECORD
 * @param array : Pointeur vers le AARRAY
 * @param prenom : Chaine de caractère correspondant au prénom
 * @param nom : Chaine de caractère correspondant au nom
 * @param mail : Chaine de caractère correspondant au l'adresse email,
 * NULL si le critère de selection est le numéro de téléphone
 * @param telephone : Chaine de caractère correspondant au prénom,
 * NULL si le critère de selection est l'adresse email
 */
void aapop(AARRAY* array, char prenom[], char nom[], char mail[], char telephone[])
{
    assert(array->length > 0 && (mail == NULL || telephone == NULL));
    int indice = hash(prenom, nom, array->size);
    int i = 0;

    if (mail == NULL) {
        while (i < array->content[indice]->length &&
               strcmp(array->content[indice]->content[i]->data[4], telephone) != 0) i++;
    } else {
        while (i < array->content[indice]->length &&
               strcmp(array->content[indice]->content[i]->data[5], mail) != 0) i++;
    }
    if (i == array->content[indice]->length) {
        printf("The record doesn't exist");
        printf("\n");
        return ;
    }

    lpop_i(array->content[indice], i);
}

/**
 * Supprime le RECORD correspondant à la clé (prénom,nom) avec le mail ou numéro de téléphone correspondant
 * mais ne libère pas la mémoire associé à ce RECORD
 * @param array : Pointeur vers le AARRAY
 * @param prenom : Chaine de caractère correspondant au prénom
 * @param nom : Chaine de caractère correspondant au nom
 * @param mail : Chaine de caractère correspondant au l'adresse email,
 * NULL si le critère de selection est le numéro de téléphone
 * @param telephone : Chaine de caractère correspondant au prénom,
 * NULL si le critère de selection est l'adresse email
 */
void aapop_resize(AARRAY* array, char prenom[], char nom[], char mail[], char telephone[])
{
    assert(array->length > 0 && (mail == NULL || telephone == NULL));
    int indice = hash(prenom, nom, array->size);
    int i;

    if (mail == NULL) {
        while (i < array->content[indice]->length &&
               strcmp(array->content[indice]->content[i]->data[4], telephone) != 0) i++;
    } else {
        while (i < array->content[indice]->length &&
               strcmp(array->content[indice]->content[i]->data[5], mail) != 0) i++;
    }
    if (i == array->content[indice]->length) {
        printf("The record doesn't exist");
        printf("\n");
        return;
    }
    lpop_i_resize(array->content[indice], i);
}

/**
 * Affiche tous les RECORD du AARRAY
 * @param array : Pointeur vers le AARRAY
 */
void aadisplay(AARRAY* array)
{
    int i, j;
    printf("%-25s%-30s%-25s%-15s%-20s%-50s%-20s\n\n", "Prenom", "Nom", "Ville", "Code Postal", "Telephone", "Email", "Profession");
    for (i = 0; i < array->size; i++) {
        if (array->content[i] != NULL) {
            for (j = 0; j < array->content[i]->length; j++) {
                rdisplay((RECORD*)array->content[i]->content[j]);
            }
        }
    }
}

/**
 * Libère les allocations de mémoire de toutes les LIST du AARRAY, ainsi que la mémoire dynamiquement alloué au AARRAY
 * @param array : Pointeur vers le AARRAY
 */
void aafree(AARRAY* array)
{
    int i;
    for (i = 0; i < array->size; i++)
    {
        if (array->content[i] != NULL)
        {
            lfree(array->content[i]);
        }
    }
    free(array->content);
    free(array);
}

