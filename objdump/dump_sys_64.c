/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** dump_sys_64.c
*/

#include "objdump.h"

void dump_sys_64_header(object_dump_t *obj)
{
    Elf64_Ehdr *header = obj->buf;
    uint32_t flags = compute_sys_64_flags(obj);

    printf("\n%s:     file format elf64-x86-64\n", obj->file_name);
    printf("architecture: i386:x86-64, flags 0x%08x:\n", flags);
    print_flags(flags);
    printf("start address 0x%016x\n\n", (unsigned int)header->e_entry);
}

void dump_sys_64_section_content(Elf64_Shdr *section, void *section_content)
{
    for (unsigned int i = 0; i < section->sh_size; i += 16) {
        dump_sys_64_section_memory(section, i, section_content);
        dump_sys_64_section_ascii(section, i, section_content);
    }
}

void dump_sys_64_sections(object_dump_t *obj)
{
    Elf64_Ehdr *header = obj->buf;
    Elf64_Shdr *sections = (void *)header + header->e_shoff;

    for (int i = 0; i != header->e_shnum - 3; i++) {
        if (sections[i].sh_size == 0 || sections[i].sh_type == SHT_NULL
        || sections[i].sh_type == SHT_NOBITS || (header->e_type == ET_REL
        && (sections[i].sh_type == SHT_RELA || sections[i].sh_type == SHT_REL))
        || is_tab(get_sys_64_section_name(obj, i)) == true)
            continue;
        printf("Contents of section %s:\n", get_sys_64_section_name(obj, i));
        dump_sys_64_section_content(&sections[i],
        obj->buf + sections[i].sh_offset);
    }
}

void dump_sys_64(object_dump_t *obj)
{
    dump_sys_64_header(obj);
    dump_sys_64_sections(obj);
}