/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** objdump.h
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <fcntl.h>
#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

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

typedef enum {
    BFD_NO_FLAGS = 0x00,
    HAS_RELOC = 0x01,
    EXEC_P = 0x02,
    HAS_LINENO = 0x04,
    HAS_DEBUG = 0x08,
    HAS_SYMS = 0x10,
    HAS_LOCALS = 0x20,
    DYNAMIC = 0x40,
    WP_TEXT = 0x80,
    D_PAGED = 0x100
} flags_t;

                    /* Functions */

int open_file(char *file_name);
void *mmap_file(int fd, char *file_name, struct stat *stats);
int get_sys_type(char *file_name, void *buf);
object_dump_t *create_object_dump(char *file_name);
void destroy_object_dump(object_dump_t *obj);

void dump_sys_64(object_dump_t *obj);
void dump_sys_32(object_dump_t *obj);

uint32_t compute_flags(object_dump_t *obj);

#endif /* OBJDUMP_H_ */