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
    int s1 = 0;
    int s = 0;

    for (int i = 0, c1, c2; k[i + s1] && k2[i + s]; i++) {
        for (; k[s1 + i] && !IS_ASCII(k[s1 + i]); s1++);
        for (; k2[s + i] && !IS_ASCII(k2[s + i]); s++);
        c1 = k[i + s1] >= 'A' && k[i + s1] <= 'Z' ? k[i + s1] : k[i + s1] - 32;
        c2 = k2[i + s] >= 'A' && k2[i + s] <= 'Z' ? k2[i + s] : k2[i + s] - 32;
        if (c1 < c2)
            return (false);
        else if (c1 > c2)
            return (true);
    }
    if (!strcmp("__data_start", k2) && !strcmp("data_start", k))
        return (true);
    if (!strcmp("__data_start", k) && !strcmp("data_start", k2))
        return (false);
    if (s1 < s)
        return (false);
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