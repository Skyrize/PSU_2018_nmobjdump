/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description: Created on: 7 févr. 2019
** main.c
*/

#include <unistd.h>
#include "nm.h"

int nm_file(char *file_name, int nb_files)
{
    object_dump_t *obj = create_object_dump(file_name);
	int my_errno = 0;

    if (!obj)
        return (84);
    if (nb_files > 1)
        printf("\n%s:\n", file_name);
    if (obj->sys_type == SYS_32) {
        my_errno = nm_sys_32(obj);
    } else if (obj->sys_type == SYS_64) {
        my_errno = nm_sys_64(obj);
    }
    destroy_object_dump(obj);
    return (my_errno);
}

int main(int argc, char **argv)
{
    int my_errno = 0;

	//printf("%s && %s = %d", argv[1], argv[2], key_is_higher(argv[1], argv[2]));
    if (argc == 1)
        return (nm_file("a.out", argc));
    for (int i = 1; i != argc; i++) {
        if (nm_file(argv[i], argc - 1) != 0)
            my_errno = 84;
    }
    return (my_errno);
}
