/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** tool.c
*/

#include "objdump.h"

void dump_sys_64_section_memory(Elf64_Shdr *section, unsigned int starting_byte, void *section_content)
{
    int padding = get_number_padding(*(uint32_t *)section_content,
    *(uint32_t *)section_content + section->sh_size, 16);

    printf(" ");
    for (int i = 0; i != padding; i++)
        printf("0");
    printf("%04x ", (unsigned int)(starting_byte + section->sh_addr));
    for (unsigned int i = 0; i != 16; i++) {
        if (i == 4 || i == 8 || i == 12)
            printf(" ");
        if ((unsigned int)starting_byte + i < section->sh_size)
            printf("%02x", ((unsigned char *)section_content)[starting_byte + i]);
        else
            printf("  ");
    }
    printf("  ");
}

void dump_sys_64_section_ascii(Elf64_Shdr *section, unsigned int starting_byte, void *section_content)
{
    char *section_content_string = section_content;

    for (unsigned int i = 0; i != 16; i++) {
        if ((unsigned int )starting_byte + i < section->sh_size
        && IS_ASCII(section_content_string[starting_byte + i]))
            printf("%c", ((char *)section_content)[starting_byte + i]);
        else if (starting_byte + i < section->sh_size)
            printf(".");
        else
            printf(" ");
    }
    printf("\n");
}

char *get_sys_64_section_name(object_dump_t *obj, int index)
{
    Elf64_Ehdr *header = obj->buf;
    Elf64_Shdr *sections = (void *)header + header->e_shoff;
    Elf64_Shdr *names_section = &sections[header->e_shstrndx];

    return ((char *)(obj->buf
    + names_section->sh_offset + sections[index].sh_name));
}

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
