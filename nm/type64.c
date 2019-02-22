/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** type64.c
*/

#include "nm.h"

char get_sys_64_type_1(Elf64_Sym *sym)
{
    char c = 0;

    if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
        c = 'u';
    else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
            c = 'W';
            if (sym->st_shndx == SHN_UNDEF)
                c = 'w';
    } else if (ELF64_ST_BIND(sym->st_info)
    == STB_WEAK && ELF64_ST_TYPE(sym->st_info) == STT_OBJECT) {
            c = 'V';
            if (sym->st_shndx == SHN_UNDEF)
                c = 'v';
    }
    return (c);
}

char get_sys_64_type_2(Elf64_Sym *sym)
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

char get_sys_64_type_3(Elf64_Sym *sym, Elf64_Shdr *shdr)
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
    return (c);
}

char get_sys_64_type_4(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
    char c = 0;

    if ((shdr[sym->st_shndx].sh_type == SHT_PROGBITS
    && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    || shdr[sym->st_shndx].sh_type == SHT_INIT_ARRAY
        || shdr[sym->st_shndx].sh_type == SHT_FINI_ARRAY)
        c = 'T';
    else if (shdr[sym->st_shndx].sh_type == SHT_DYNAMIC)
        c = 'D';
    else
        c = '?';
    return (c);
}

char get_sys_64_type(Elf64_Sym *sym, object_dump_t *obj)
{
    char c = 0;
    Elf64_Ehdr *header = obj->buf;
    Elf64_Shdr *shdr = (void *)obj->buf + header->e_shoff;

    if ((c = get_sys_64_type_1(sym)) != 0 || (c = get_sys_64_type_2(sym)) != 0
    || (c = get_sys_64_type_3(sym, shdr)) != 0
    || (c = get_sys_64_type_4(sym, shdr)) != 0) {
        if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
            c += 32;
        return (c);
    }
    return (c);
}
