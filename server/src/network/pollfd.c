/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** pollfd
*/

#include "../../include/pollfd.h"

struct pollfd pollfd_set(int new_fd)
{
    struct pollfd pfd;

    pfd.fd = new_fd;
    pfd.events = POLLIN;
    return pfd;
}

struct pollfd *pollfd_array_add(struct pollfd *array, int new_fd, int a_size)
{
    struct pollfd *temp;

    temp = realloc(array, sizeof(struct pollfd) * (a_size + 1));
    temp[a_size].fd = new_fd;
    temp[a_size].events = POLLIN;
    return temp;
}

struct pollfd *pollfd_array_remove(struct pollfd *array, int elem_i, int a_size)
{
    struct pollfd *temp;
    int ti = 0;

    temp = (struct pollfd *)malloc(sizeof(struct pollfd) * a_size - 1);
    for (int si = 0; si < a_size; si++) {
        if (si == elem_i)
            si++;
        if (si != a_size) {
            temp[ti].fd = array[si].fd;
            temp[ti].events = array[si].events;
            ti++;
        }
    }
    free(array);
    return temp;
}
