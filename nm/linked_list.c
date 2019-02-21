/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** linked_list.c
*/

#include "nm.h"

void destroy_node(node_t *node)
{
    if (node) {
        free(node->key);
        free(node);
    }
}

void destroy_llist(node_t *llist)
{
    node_t *tmp;

    while (llist) {
        tmp = llist;
        llist = llist->next;
        destroy_node(tmp);
        tmp = NULL;
    }
}

node_t *node_create(char type, char *key, void *value)
{
    node_t *new = malloc(sizeof(node_t));

    if (!new)
        return (NULL);
    new->key = my_strdup(key);
    new->type = type;
    new->value = value;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

node_t *add_to_llist(char type, char *key, void *value, node_t **llist)
{
	node_t *new = node_create(type, key, value);
	node_t *tmp = *llist;

	if (!new)
		return (NULL);
	if (!tmp) {
		*llist = new;
		return (new);
	}
	for (; tmp->next && tmp->; tmp = tmp->next);
	tmp->next = new;
	new->prev = tmp;
	return (new);
}