//
// Created by julie on 23/11/2021.
//

#include "../../header/struct/AssociativeArray.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

AARRAY* aainit(int size)
{
    AARRAY* tmp = malloc(sizeof(AARRAY));
    tmp->size = pow(2,size);
    tmp->content = malloc(sizeof(LIST*)*tmp->size);
    tmp->length = 0;
    return tmp;
}

int hash(char prenom[], char nom[], int aa_size)
{
    int poids = 8;
    int somme = 0;
    int i;
    int n1 = strlen(prenom);
    int n2 = strlen(nom);

    for (i = 0; i < n1; i++)
    {
        if (poids == 0)
        {
            poids = 8;
            somme += prenom[i];
        }
        else
        {
            somme += prenom[i]*poids;
            poids--;
        }
    }
    for (i = 0; i < n2; i++)
    {
        if (poids == 0)
        {
            poids = 8;
            somme += nom[i];
        }
        else
        {
            somme += nom[i]*poids;
            poids--;
        }
    }
    return somme % aa_size;
}

void aapush(AARRAY* array, char prenom[], char nom[], RECORD* elt)
{
    int indice = hash(prenom, nom, array->size);
    if (array->content[indice] == NULL) array->content[indice] = linit();
    lpush(array->content[indice], elt);
}

RECORD* aapop(AARRAY* array, char prenom[], char nom[], char mail[], char telephone[])
{
    assert(array->length > 0 && (mail == NULL || telephone == NULL));
    int indice = hash(prenom, nom, array->size);
    int i;
    RECORD* tmp;

    if (mail == NULL) {
        while (i < array->content[indice]->length && !(strcmp(((RECORD*)array->content[indice]->content[i])->data[4], telephone))) i++;
    } else {
        while (i < array->content[indice]->length && !(strcmp(((RECORD*)array->content[indice]->content[i])->data[5], mail))) i++;
    }
    if (i == array->content[indice]->length) {
        perror("The record doesn't exist");
        exit(EXIT_FAILURE);
    }

    tmp = (RECORD*)array->content[indice]->content[i];
    lpop_i(array->content[indice], i);
    return tmp;

}

void aafree(AARRAY* tmp)
{
    int i;
    for (i = 0; i < tmp->size; i++)
    {
        if (tmp->content[i] != NULL)
        {
            lfree(tmp->content[i]);
        }
    }
    free(tmp->content);
    free(tmp);
}