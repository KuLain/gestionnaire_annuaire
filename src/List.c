//
// Created by julie on 13/11/2021.
//

#include "../header/List.h"
#include <stdlib.h>

LIST* linit()
{
    LIST *tmp = malloc(sizeof(LIST));
    tmp->content = NULL;
    tmp->length = 0;
    return tmp;
}

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

void ldisplay_record(LIST *tmp)
{
    int i;
    for (i = 0; i < tmp->length; i++)
    {
        rdisplay((RECORD*)tmp->content[i]);
        printf("\n");
    }
}