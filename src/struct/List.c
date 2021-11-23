//
// Created by julie on 13/11/2021.
//

#include "../../header/struct/List.h"
#include <stdlib.h>
/**
 * Initialise variables of LIST
 * @return pointer to LIST with initialised variables
 */
LIST* linit()
{
    LIST *tmp = malloc(sizeof(LIST));
    tmp->content = NULL;
    tmp->length = 0;
    return tmp;
}

/**
 * Append element to the LIST
 * @param tmp Pointer to LIST
 * @param elt Pointer to the element to append
 */
void lpush(LIST *tmp, void* elt)
{
    tmp->content = realloc(tmp->content, sizeof(void*)*(tmp->length+1));
    if (tmp->content == NULL)
    {
        perror("Erreur lors de la reallocation de la memoire");
        exit(EXIT_FAILURE);
    }
    tmp->content[tmp->length] = elt;
    tmp->length++;
}

void* lpop(LIST *tmp)
{
    if (tmp->length == 0)
    {
        perror("Liste vide");
        exit(EXIT_FAILURE);
    }
    void* elt = tmp->content[tmp->length-1];
    tmp->content = realloc(tmp->content, sizeof(void*)*(tmp->length-1));
    tmp->length--;
    return elt;
}

RECORD* lpop_record(LIST *tmp)
{
    if (tmp->length == 0)
    {
        perror("Liste vide");
        exit(EXIT_FAILURE);
    }
    RECORD * elt = (RECORD*)tmp->content[tmp->length-1];
    tmp->content = realloc(tmp->content, sizeof(void*)*(tmp->length-1));
    tmp->length--;
    return elt;
}

/**
 * Free all RECORD pointer in LIST and LIST pointer
 * @param tmp Pointer to LIST
 */
void lfree_record(LIST *tmp)
{
    int i;
    for (i = 0; i < tmp->length; i++)
    {
        rfree((RECORD*)tmp->content[i]);
    }
    free(tmp->content);
    free(tmp);
}

/**
 * Display all RECORD in LIST
 * @param tmp Pointer to LIST
 */
void ldisplay_record(LIST *tmp)
{
    int i;
    for (i = 0; i < tmp->length; i++)
    {
        rdisplay((RECORD*)tmp->content[i]);
        printf("\n");
    }
}