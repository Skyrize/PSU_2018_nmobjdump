/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** nm.c
*/

#include "nm.h"

int nm_sys_64(object_dump_t *obj)
{
    Elf64_Shdr *symtab_h = get_sys_64_section_by_name(".symtab", obj);
    Elf64_Sym *symtab = NULL;
    Elf64_Shdr *strtab_header = get_sys_64_section_by_name(".strtab", obj);
    char *strtab = obj->buf + strtab_header->sh_offset;

    if (!symtab_h) {
        dprintf(2, "nm: %s: no symbols\n", obj->file_name);
        return (84);
    }
    symtab = obj->buf + symtab_h->sh_offset;
    for (unsigned int i = 0; i != symtab_h->sh_size / sizeof(Elf64_Sym); i++) {
        if (strtab[symtab[i].st_name]) {
            printf("%016x ", (unsigned int)symtab[i].st_value);
            printf("%s ", "0");
            printf("%s\n", &strtab[symtab[i].st_name]);
        }
    }
    return (0);
}

int nm_sys_32(object_dump_t *obj)
{
    return (0);
}