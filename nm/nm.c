/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** nm.c
*/

#include "nm.h"

char get_type(Elf64_Sym *sym, Elf64_Sym *symtab, object_dump_t *obj)
{
    char c;
    Elf64_Ehdr *header = obj->buf;
    Elf64_Shdr *shdr = (void *)obj->buf + header->e_shoff;

    if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
        c = 'u';
    else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
        {
            c = 'W';
            if (sym->st_shndx == SHN_UNDEF)
                c = 'w';
        }
    else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK && ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
        {
            c = 'V';
            if (sym->st_shndx == SHN_UNDEF)
                c = 'v';
        }
    else if (sym->st_shndx == SHN_UNDEF)
        c = 'U';
    else if (sym->st_shndx == SHN_ABS)
        c = 'A';
    else if (sym->st_shndx == SHN_COMMON)
        c = 'C';
    else if (shdr[sym->st_shndx].sh_type == SHT_NOBITS
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
    if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
        c += 32;
    return c;
}

void nm_sys_64_dump(node_t *llist)
{
    bubble_sort(&llist);
    for (node_t *tmp = llist; tmp; tmp = tmp->next) {
        tmp->value == 0 ? printf("                ") : printf("%016x", tmp->value);
        printf(" %c %s\n", tmp->type, tmp->key);
    }
}

int nm_sys_64(object_dump_t *obj)
{
    Elf64_Shdr *symtab_h = get_sys_64_section_by_name(".symtab", obj);
    Elf64_Sym *symtab = NULL;
    Elf64_Shdr *strtab_header = get_sys_64_section_by_name(".strtab", obj);
    char *strtab = obj->buf + strtab_header->sh_offset;
    node_t *ll = NULL;

    if (!symtab_h) {
        dprintf(2, "nm: %s: no symbols\n", obj->file_name);
        return (84);
    }
    symtab = obj->buf + symtab_h->sh_offset;
    for (unsigned int i = 0; i != symtab_h->sh_size / sizeof(Elf64_Sym); i++) {
        if (strtab[symtab[i].st_name]
        && ELF64_ST_TYPE(symtab[i].st_info) != STT_FILE)
            add_to_llist(get_type(&symtab[i], symtab, obj),
            &strtab[symtab[i].st_name], (unsigned int)symtab[i].st_value, &ll);
    }
    nm_sys_64_dump(ll);
    return (0);
}

int nm_sys_32(object_dump_t *obj)
{
    return (0);
}