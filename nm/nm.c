/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** nm.c
*/

#include "nm.h"

void nm_sys_64_dump(node_t *llist)
{
    bubble_sort(&llist);
    for (node_t *tmp = llist; tmp; tmp = tmp->next) {
        tmp->type == 'U' || tmp->type == 'w' ? printf("                ") :
        printf("%016x", tmp->value);
        printf(" %c %s\n", tmp->type, tmp->key);
    }
}

int nm_sys_64(object_dump_t *obj)
{
    Elf64_Shdr *symtab_h = get_sys_64_section_by_name(".symtab", obj);
    Elf64_Sym *symtab = NULL;
    Elf64_Shdr *strtab_header = get_sys_64_section_by_name(".strtab", obj);
    char *strtab = obj->buf + strtab_header->sh_offset;
    node_t *li = NULL;

    if (!symtab_h) {
        dprintf(2, "nm: %s: no symbols\n", obj->file_name);
        return (84);
    }
    symtab = obj->buf + symtab_h->sh_offset;
    for (unsigned int i = 0; i != symtab_h->sh_size / sizeof(Elf64_Sym); i++) {
        if (strtab[symtab[i].st_name]
        && ELF64_ST_TYPE(symtab[i].st_info) != STT_FILE)
            add_to_llist(get_sys_64_type(&symtab[i], obj),
            &strtab[symtab[i].st_name], (unsigned int)symtab[i].st_value, &li);
    }
    nm_sys_64_dump(li);
    return (0);
}

void nm_sys_32_dump(node_t *llist)
{
    bubble_sort(&llist);
    for (node_t *tmp = llist; tmp; tmp = tmp->next) {
        tmp->type == 'U' || tmp->type == 'w' ? printf("        ") :
        printf("%08x", tmp->value);
        printf(" %c %s\n", tmp->type, tmp->key);
    }
}

int nm_sys_32(object_dump_t *obj)
{
    Elf32_Shdr *symtab_h = get_sys_32_section_by_name(".symtab", obj);
    Elf32_Sym *symtab = NULL;
    Elf32_Shdr *strtab_header = get_sys_32_section_by_name(".strtab", obj);
    char *strtab = obj->buf + strtab_header->sh_offset;
    node_t *li = NULL;

    if (!symtab_h) {
        dprintf(2, "nm: %s: no symbols\n", obj->file_name);
        return (84);
    }
    symtab = obj->buf + symtab_h->sh_offset;
    for (unsigned int i = 0; i != symtab_h->sh_size / sizeof(Elf32_Sym); i++) {
        if (strtab[symtab[i].st_name]
        && ELF32_ST_TYPE(symtab[i].st_info) != STT_FILE)
            add_to_llist(get_sys_32_type(&symtab[i], obj),
            &strtab[symtab[i].st_name], (unsigned int)symtab[i].st_value, &li);
    }
    nm_sys_32_dump(li);
    return (0);
}