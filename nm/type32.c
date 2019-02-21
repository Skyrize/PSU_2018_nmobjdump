/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** type32.c
*/

#include "nm.h"

char get_sys_32_type_1(Elf32_Sym *sym)
{
    char c = 0;

    if (ELF32_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
        c = 'u';
    else if (ELF32_ST_BIND(sym->st_info) == STB_WEAK) {
            c = 'W';
            if (sym->st_shndx == SHN_UNDEF)
                c = 'w';
    } else if (ELF32_ST_BIND(sym->st_info)
    == STB_WEAK && ELF32_ST_TYPE(sym->st_info) == STT_OBJECT) {
            c = 'V';
            if (sym->st_shndx == SHN_UNDEF)
                c = 'v';
    }
    return (c);
}

char get_sys_32_type_2(Elf32_Sym *sym)
{
    char c = 0;

    if (sym->st_shndx == SHN_UNDEF)
        c = 'U';
    else if (sym->st_shndx == SHN_ABS)
        c = 'A';
    else if (sym->st_shndx == SHN_COMMON)
        c = 'C';
    return (c);
}

char get_sys_32_type_3(Elf32_Sym *sym, Elf32_Shdr *shdr)
{
    char c = 0;

    if (shdr[sym->st_shndx].sh_type == SHT_NOBITS
             && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'B';
    else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
             && shdr[sym->st_shndx].sh_flags == SHF_ALLOC)
        c = 'R';
    else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
             && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'D';
    else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
             && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        c = 'T';
    else if (shdr[sym->st_shndx].sh_type == SHT_DYNAMIC)
        c = 'D';
    else
        c = '?';
    return (c);
}

char get_sys_32_type(Elf32_Sym *sym, object_dump_t *obj)
{
    char c = 0;
    Elf32_Ehdr *header = obj->buf;
    Elf32_Shdr *shdr = (void *)obj->buf + header->e_shoff;

    if ((c = get_sys_32_type_1(sym)) != 0 || (c = get_sys_32_type_2(sym)) != 0
    || (c = get_sys_32_type_3(sym, shdr)) != 0)
        if (ELF32_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
            c += 32;
        return (c);
    return (c);
}
