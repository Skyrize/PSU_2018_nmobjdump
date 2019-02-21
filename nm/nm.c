/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** nm.c
*/

#include "nm.h"

int nm_sys_64(object_dump_t *obj)
{
    Elf64_Shdr *symtab = get_sys_64_symtab(obj);

    if (!symtab) {
        dprintf(2, "nm: %s: no symbols\n", obj->file_name);
        return (84);
    }
    return (0);
}

int nm_sys_32(object_dump_t *obj)
{
    return (0);
}