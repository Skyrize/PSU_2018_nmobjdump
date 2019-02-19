/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** destroy.c
*/

#include "objdump.h"

void destroy_object_dump(object_dump_t *obj)
{
    munmap(obj->buf, obj->stats.st_size);
    close(obj->fd);
    free(obj);
}