/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** main.c
*/

#include "objdump.h"

int dump_file(char *file_name)
{
    object_dump_t *obj = create_object_dump(file_name);

    if (!obj)
        return (84);
    if (obj->sys_type == SYS_32) {
        dump_sys_32(obj);
    } else if (obj->sys_type == SYS_64) {
        dump_sys_64(obj);
    }
    destroy_object_dump(obj);
    return (0);
}

int main(int argc, char **argv)
{
    int my_errno = 0;

    if (argc == 1)
        return (dump_file("a.out"));
    for (int i = 1; i != argc; i++) {
        if (dump_file(argv[i]) != 0)
            my_errno = 84;
    }
    return (my_errno);
}