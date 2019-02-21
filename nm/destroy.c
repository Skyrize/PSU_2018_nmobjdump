/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** destroy.c
*/

#include "nm.h"

void destroy_object_dump(object_dump_t *obj)
{
    munmap(obj->buf, obj->stats.st_size);
    close(obj->fd);
    free(obj);
}

void destroy_node(node_t *node)
{
    if (node) {
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