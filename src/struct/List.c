//
// Created by lain on 30/11/2021.
//

#include "../../header/struct/List.h"
#include <stdlib.h>
#include <assert.h>


/**
 * Initialise les variables d'une LIST et alloue de la mémoire pour cette LIST
 * @return : Pointeur vers la LIST
 */
LIST* linit()
{
    LIST *liste = (LIST*)malloc(sizeof(LIST));
    if (liste == NULL)
    {
        perror("Erreur lors de la reallocation de la memoire");
        exit(EXIT_FAILURE);
    }
    liste->content = NULL;
    liste->length = 0;
    return liste;
}

/**
 * Ajoute le record à la fin de la liste
 * @param liste : Pointeur vers la LIST
 * @param elt : Pointeur vers le RECORD à ajouter à la fin
 */
void lpush(LIST *liste, RECORD* elt)
{
    liste->content = (RECORD**)realloc(liste->content, sizeof(RECORD*)*(liste->length+1));
    if (liste->content == NULL)
    {
        perror("Erreur lors de la reallocation de la memoire");
        exit(EXIT_FAILURE);
    }
    liste->content[liste->length] = elt;
    liste->length++;
}

/**
 * Supprime le dernier RECORD de la LIST et libère la mémoire alloué à ce RECORD
 * @param liste : Pointeur vers la LIST
 */
void lpop(LIST *liste)
{
    if (liste->length == 0)
    {
        perror("Liste vide");
        exit(EXIT_FAILURE);
    }
    RECORD* elt = liste->content[liste->length-1];
    liste->content = (RECORD**) realloc(liste->content, sizeof(RECORD*)*(liste->length-1));
    if (liste->content == NULL)
    {
        perror("Erreur lors de la reallocation de la memoire");
        exit(EXIT_FAILURE);
    }
    liste->length--;
    rfree(elt);
}

/**
 * Supprime le RECORD d'indice index et libère la mémoire alloué à ce RECORD
 * @param liste : Pointeur vers la LIST
 */
void lpop_i(LIST *liste, int index)
{
    assert(index >= 0 && index < liste->length);
    RECORD* result = liste->content[index];
    int i;
    for (i = index; i < liste->length-1; i++) liste->content[i] = liste->content[i+1];
    liste->content = (RECORD**) realloc(liste->content, sizeof(RECORD*)*liste->length-1);
    if (liste->content == NULL)
    {
        perror("Erreur lors de la reallocation de la memoire");
        exit(EXIT_FAILURE);
    }
    liste->length--;
    rfree(result);
}

/**
 * Supprime le RECORD d'indice index mais ne libère pas la mémoire du RECORD
 * @param liste : Pointeur vers la LIST
 */
void lpop_i_resize(LIST* liste, int index)
{
    assert(index >= 0 && index < liste->length);
    RECORD* result = liste->content[index];
    int i;
    for (i = index; i < liste->length-1; i++) liste->content[i] = liste->content[i+1];
    liste->content = (RECORD**) realloc(liste->content, sizeof(RECORD*)*liste->length-1);
    if (liste->content == NULL)
    {
        perror("Erreur lors de la reallocation de la memoire");
        exit(EXIT_FAILURE);
    }
    liste->length--;
}

/**
 * Libère la mémoire de tous les RECORD de la LIST, ainsi que la mémoire dynamiquement alloué de la LIST
 * @param liste : Pointeur vers la LIST
 */
void lfree(LIST *liste)
{
    int i;
    for (i = 0; i < liste->length; i++) rfree(liste->content[i]);
    free(liste->content);
    free(liste);
}

