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
    uint32_t flags = compute_flags(obj);

    printf("%s:\tfile format elf64-x86-64\n", obj->file_name);
    printf("architecture: i386:x86-64, flags %08x:\n", flags);
}

void dump_sys_64(object_dump_t *obj)
{
    dump_sys_64_header(obj);
}