/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** tools.c
*/

#include "nm.h"

Elf64_Shdr *get_sys_64_section_by_name(char *name, object_dump_t *obj)
{
    Elf64_Ehdr *header = obj->buf;
    Elf64_Shdr *sections = (void *)header + header->e_shoff;
    Elf64_Shdr *names_section = &sections[header->e_shstrndx];
    char *section_name = NULL;

    for (int i = 0; i != header->e_shnum; i++) {
        section_name = obj->buf + names_section->sh_offset
        + sections[i].sh_name;
        if (strcmp(section_name, name) == 0)
            return (&sections[i]);
    }
    return (NULL);
}