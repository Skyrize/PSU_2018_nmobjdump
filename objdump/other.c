/*
** EPITECH PROJECT, 2018
** PSU_2018_nmobjdump
** File description:
** other.c
*/

int get_number_padding(unsigned int n1, unsigned int n2, int base)
{
    int padding = 0;

    if (n1 >= n2)
        return (0);
    while (n1) {
        n1 = n1 / base;
        n2 = n2 / base;
    }
    while (n2) {
        n2 = n2 / base;
        padding++;
    }
    return (padding);
}