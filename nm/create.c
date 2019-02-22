/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** create.c
*/

#include "nm.h"
#include <stdbool.h>

int open_file(char *file_name)
{
    int fd = open(file_name, O_RDONLY);

    if (fd == -1)
        dprintf(2, "nm: '%s': No such file\n", file_name);
    return (fd);
}

void *mmap_file(int fd, char *file_name, struct stat *stats)
{
    void *buf = mmap(NULL, stats->st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    if (buf ==  MAP_FAILED)
        dprintf(2, "nm: Warning: '%s' is not an ordinary file\n",
        file_name);
    return (buf);
}

int get_sys_type(char *file_name, void *buf)
{
    int type = ((char *)buf)[4];

    if (type != 1 && type != 2) {
        dprintf(2, "nm: %s: File format not recognized\n", file_name);
        return (-1);
    }
    return (type);
}

bool is_elf_valid(char *file_name, void *buf)
{
    if (((char *)buf)[EI_MAG0] == ELFMAG0
    && ((char *)buf)[EI_MAG1] == ELFMAG1
    && ((char *)buf)[EI_MAG2] == ELFMAG2
    && ((char *)buf)[EI_MAG3] == ELFMAG3)
        return (true);
    dprintf(2, "nm: %s: File format not recognized\n", file_name);
    return (false);
}

object_dump_t *create_object_dump(char *file_name)
{
    object_dump_t *obj = malloc(sizeof(*obj));

    if (!obj)
        return (NULL);
    obj->file_name = file_name;
    if ((obj->fd = open_file(file_name)) == -1)
        return (NULL);
    fstat(obj->fd, &obj->stats);
    obj->buf = mmap_file(obj->fd, file_name, &obj->stats);
    if (obj->buf == MAP_FAILED || !is_elf_valid(file_name, obj->buf)
    || (obj->sys_type = get_sys_type(obj->file_name, obj->buf)) == -1)
        return (NULL);
    if ((obj->sys_type == 2 && obj->stats.st_size + obj->buf < obj->buf
    + ((Elf64_Ehdr *)obj->buf)->e_shoff) || (obj->sys_type == 1
    && obj->stats.st_size + obj->buf < obj->buf +
    ((Elf64_Ehdr *)obj->buf)->e_shoff)) {
        dprintf(2, "objdump: %s: File truncated\n", file_name);
        return (NULL);
    }
    return (obj);
}