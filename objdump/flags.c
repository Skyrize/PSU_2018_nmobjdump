/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** flags.c
*/

#include <stdbool.h>
#include "objdump.h"

bool elf64_has_section_name(char *seeked_name, object_dump_t *obj)
{
    Elf64_Ehdr *header = obj->buf;
    Elf64_Shdr *sections = (void *)header + header->e_shoff;
    Elf64_Shdr *names_section = &sections[header->e_shstrndx];
    char *section_name = NULL;

    for (int i = 0; i != header->e_shnum; i++) {
        section_name = obj->buf + names_section->sh_offset + sections[i].sh_name;
        if (strcmp(section_name, seeked_name) == 0)
            return (true);
    }
    return (false);
}

bool elf64_has_section_type(uint32_t seeked_type, object_dump_t *obj)
{
    Elf64_Ehdr *header = obj->buf;
    Elf64_Shdr *sections = (void *)header + header->e_shoff;

    for (int i = 0; i != header->e_shnum; i++)
        if (sections[i].sh_type == seeked_type)
            return (true);
    return (false);
}

uint32_t compute_flags(object_dump_t *obj)
{
    Elf64_Ehdr *header = obj->buf;
    uint32_t flags = 0;

    if (header->e_type == ET_REL)
        flags |= HAS_RELOC;
    if (header->e_type == ET_EXEC)
        flags |= EXEC_P;
    if (elf64_has_section_name(".line", obj) == true)
        flags |= HAS_LINENO;

    return (flags);
}