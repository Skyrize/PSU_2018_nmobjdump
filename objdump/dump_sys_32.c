/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** dump_sys_32.c
*/

#include "objdump.h"

void dump_sys_32(object_dump_t *obj)
{
    (void)obj;
}
// {
// 	int fd = 0;
//     Elf64_Ehdr *elfHeader = NULL;
//     Elf64_Shdr *sectionHeader = NULL;

//     FILE *file = fopen(av[1], "r");
    
//     Elf64_Ehdr elfHeader;
//     Elf64_Shdr sectionHeader;
//     int offset = 0;

//     if (file) {
//         fread(&elfHeader, sizeof(Elf64_Ehdr), 1, file);
//         fseek(file, elfHeader.e_shoff + elfHeader.e_shstrndx * sizeof(sectionHeader), SEEK_SET);
//         fread(&sectionHeader, sizeof(sectionHeader), 1, file);

//         char *SectNames = malloc(sectionHeader.sh_size);
//   fseek(file, sectionHeader.sh_offset, SEEK_SET);
//   fread(SectNames, sectionHeader.sh_size, 1, file);

//         for (; offset < elfHeader.e_shnum; offset++) {
//             const char *name = "";

//             fseek(file, elfHeader.e_shoff + offset * sizeof(sectionHeader), SEEK_SET);
//             fread(&sectionHeader, sizeof(sectionHeader), 1, file);
//             if (sectionHeader.sh_name)
//                 name = SectNames + sectionHeader.sh_name;
//             printf("%s\n", name);
//         }
//     }
// }
