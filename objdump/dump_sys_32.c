/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** dump_sys_32.c
*/

#include "objdump.h"

void dump_sys_32_header(object_dump_t *obj)
{
    Elf32_Ehdr *header = obj->buf;
    uint32_t flags = compute_sys_32_flags(obj);

    printf("\n%s:     file format elf32-x86-32\n", obj->file_name);
    printf("architecture: i386:x86-32, flags 0x%08x:\n", flags);
    print_flags(flags);
    printf("start address 0x%08x\n\n", (unsigned int)header->e_entry);
}

void dump_sys_32_section_content(Elf32_Shdr *section, void *section_content)
{
    for (unsigned int i = 0; i < section->sh_size; i += 16) {
        dump_sys_32_section_memory(section, i, section_content);
        dump_sys_32_section_ascii(section, i, section_content);
    }
}

void dump_sys_32_sections(object_dump_t *obj)
{
    Elf32_Ehdr *header = obj->buf;
    Elf32_Shdr *sections = (void *)header + header->e_shoff;

    for (int i = 0; i != header->e_shnum - 3; i++) {
        if (sections[i].sh_size == 0 || sections[i].sh_type == SHT_NULL
        || sections[i].sh_type == SHT_NOBITS)
            continue;
        printf("Contents of section %s:\n", get_sys_32_section_name(obj, i));
        dump_sys_32_section_content(&sections[i],
        obj->buf + sections[i].sh_offset);
    }
}

void dump_sys_32(object_dump_t *obj)
{
    dump_sys_32_header(obj);
    dump_sys_32_sections(obj);
}