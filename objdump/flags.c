/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** flags.c
*/

#include "objdump.h"

void print_flags(uint32_t flags)
{
    int has_print = 0;

    if (flags == BFD_NO_FLAGS) {
        printf("BFD_NO_FLAGS");
        return;
    }
    has_print += PRINT_FLAG(has_print, flags, HAS_RELOC);
    has_print += PRINT_FLAG(has_print, flags, EXEC_P);
    has_print += PRINT_FLAG(has_print, flags, HAS_LINENO);
    has_print += PRINT_FLAG(has_print, flags, HAS_DEBUG);
    has_print += PRINT_FLAG(has_print, flags, HAS_SYMS);
    has_print += PRINT_FLAG(has_print, flags, DYNAMIC);
    has_print += PRINT_FLAG(has_print, flags, D_PAGED);
    if (has_print != 0)
        printf("\n");
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
    if (elf64_has_section_name(".debug", obj) == true)
        flags |= HAS_DEBUG;
    if (elf64_has_section_type(SHT_SYMTAB, obj) == true)
        flags |= HAS_SYMS;
    if (header->e_type == ET_DYN)
        flags |= DYNAMIC;
    if (elf64_has_section_type(SHT_DYNAMIC, obj) == true)
        flags |= D_PAGED;
    return (flags);
}