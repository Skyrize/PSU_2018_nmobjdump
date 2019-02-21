/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** nm.h
*/

#ifndef NM_H_
#define NM_H_

#include <fcntl.h>
#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
    SYS_32 = 1,
    SYS_64 = 2,
} sys_type_t;

typedef struct object_dump_s {
    char *file_name;
    int fd;
    void *buf;
    struct stat stats;
    int sys_type;
} object_dump_t;

#define IS_ASCII(x) (x >= 32 && x <= 126)

                    /* Functions */

int nm_sys_64(object_dump_t *obj);
int nm_sys_32(object_dump_t *obj);
Elf64_Shdr *get_sys_64_symtab(object_dump_t *obj);
object_dump_t *create_object_dump(char *file_name);
void destroy_object_dump(object_dump_t *obj);

#endif /* NM_H_ */