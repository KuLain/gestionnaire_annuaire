//
// Created by julie on 13/11/2021.
//

#include "../../header/struct/List.h"
#include <stdlib.h>
#include <assert.h>
/**
 * Initialise variables of LIST
 * @return pointer to LIST with initialised variables
 */
LIST* linit()
{
    LIST *liste = malloc(sizeof(LIST));
    if (liste->content == NULL)
    {
        perror("Erreur lors de la reallocation de la memoire");
        exit(EXIT_FAILURE);
    }
    liste->content = NULL;
    liste->length = 0;
    return liste;
}

/**
 * Append element to the LIST
 * @param liste Pointer to LIST
 * @param elt Pointer to the element to append
 */
void lpush(LIST *liste, void* elt)
{
    liste->content = realloc(liste->content, sizeof(void*)*(liste->length+1));
    if (liste->content == NULL)
    {
        perror("Erreur lors de la reallocation de la memoire");
        exit(EXIT_FAILURE);
    }
    liste->content[liste->length] = elt;
    liste->length++;
}

void* lpop(LIST *liste)
{
    if (liste->length == 0)
    {
        perror("Liste vide");
        exit(EXIT_FAILURE);
    }
    void* elt = liste->content[liste->length-1];
    liste->content = realloc(liste->content, sizeof(void*)*(liste->length-1));
    if (liste->content == NULL)
    {
        perror("Erreur lors de la reallocation de la memoire");
        exit(EXIT_FAILURE);
    }
    liste->length--;
    return elt;
}

void* lpop_i(LIST *liste, int index)
{
    assert(index >= 0 && index < liste->length);
    void* result = liste->content[index];
    int i;
    for (i = index; i < liste->length-1; i++) liste->content[i] = liste->content[i+1];
    liste->content = realloc(liste->content, sizeof(void*)*liste->length-1);
    if (liste->content == NULL)
    {
        perror("Erreur lors de la reallocation de la memoire");
        exit(EXIT_FAILURE);
    }
    liste->length--;
    return result;
}

void lfree(LIST *liste)
{
    int i;
    for (i = 0; i < liste->length; i++) free(liste->content[i]);
}
