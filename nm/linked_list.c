/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** linked_list.c
*/

#include "nm.h"

node_t *node_create(char type, char *key, unsigned int value)
{
    node_t *new = malloc(sizeof(node_t));

    if (!new)
        return (NULL);
    new->key = key;
    new->type = type;
    new->value = value;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

bool key_is_higher(char *k, char *k2)
{
    if (strcmp("__data_start", k2) == 0 && strcmp("data_start", k) == 0)
        return (true);
    if (strcmp("__data_start", k) == 0 && strcmp("data_start", k2) == 0)
        return (false);
    for (int i = 0, j = 0, c1, c2; k[i] && k2[j]; i++, j++) {
        for (; k[i] && (k[i] == '_' || k[i] == '@'); i++);
        for (; k2[j] && (k2[j] == '_' || k2[j] == '@'); j++);
        c1 = k[i] >= 'A' && k[i] <= 'Z' ? k[i] : k[i] - 32;
        c2 = k2[j] >= 'A' && k2[j] <= 'Z' ? k2[j] : k2[j] - 32;
        if (c1 < c2)
            return (false);
        else if (c1 > c2)
            return (true);
    }
    return (strlen(k) < strlen(k2) ? false : true);
}

void swap(node_t *s1, node_t *s2)
{
    char tmp_type = s1->type;
    char *tmp_key = s1->key;
    unsigned int tmp_value = s1->value;

    s1->type = s2->type;
    s1->key = s2->key;
    s1->value = s2->value;
    s2->type = tmp_type;
    s2->key = tmp_key;
    s2->value = tmp_value;
}

void bubble_sort(node_t **llist)
{
    int swapped = 0;

    for (node_t *tmp = *llist; tmp->next; tmp = tmp->next) {
        if (key_is_higher(tmp->key, tmp->next->key)) {
            swap(tmp, tmp->next);
            swapped = 1;
        }
    }
    if (swapped)
        bubble_sort(llist);
}

node_t *add_to_llist(char type, char *key, unsigned int value, node_t **llist)
{
    node_t *new = node_create(type, key, value);
    node_t *tmp = *llist;

    if (!new)
        return (NULL);
    if (!tmp) {
        *llist = new;
        return (new);
    }
    for (; tmp->next; tmp = tmp->next);
    tmp->next = new;
    new->prev = tmp;
    return (new);
}