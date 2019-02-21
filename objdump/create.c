/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** create.c
*/

#include "objdump.h"
#include <stdbool.h>

int open_file(char *file_name)
{
    int fd = open(file_name, O_RDONLY);

    if (fd == -1)
        dprintf(2, "my_objdump: \'%s\': No such file\n", file_name);
    return (fd);
}

void *mmap_file(int fd, char *file_name, struct stat *stats)
{
    void *buf = mmap(NULL, stats->st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    if (buf ==  MAP_FAILED)
        dprintf(2, "my_objdump: Warning: \'%s\' is not an ordinary file\n",
        file_name);
    return (buf);
}

int get_sys_type(char *file_name, void *buf)
{
    int type = ((char *)buf)[4];

    if (type != 1 && type != 2) {
        dprintf(2, "my_objdump: %s: File format not recognized\n", file_name);
        return (-1);
    }
    return (type);
}

bool is_magic_number_valid(char *file_name, void *buf)
{
    if (((char *)buf)[EI_MAG0] == ELFMAG0
    && ((char *)buf)[EI_MAG1] == ELFMAG1
    && ((char *)buf)[EI_MAG2] == ELFMAG2
    && ((char *)buf)[EI_MAG3] == ELFMAG3)
        return (true);
    dprintf(2, "my_objdump: %s: File format not recognized\n", file_name);
    return (false);
}

object_dump_t *create_object_dump(char *file_name)
{
    object_dump_t *new_obj = malloc(sizeof(*new_obj));

    if (!new_obj)
        return (NULL);
    new_obj->file_name = file_name;
    if ((new_obj->fd = open_file(file_name)) == -1)
        return (NULL);
    fstat(new_obj->fd, &new_obj->stats);
    new_obj->buf = mmap_file(new_obj->fd, file_name, &new_obj->stats);
    if (new_obj->buf == MAP_FAILED)
        return (NULL);
    if (!is_magic_number_valid(file_name, new_obj->buf))
        return (NULL);
    new_obj->sys_type = get_sys_type(new_obj->file_name, new_obj->buf);
    if (new_obj->sys_type == -1)
        return (NULL);
    return (new_obj);
}