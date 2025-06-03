/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** pollfd
*/

#ifndef POLLFD_H_
    #define POLLFD_H_
    #include "external.h"

struct pollfd *pollfd_array_add(struct pollfd *array, int new_fd, int a_size);
struct pollfd *pollfd_array_remove(struct pollfd *array, int elem_i, int a_size);
struct pollfd pollfd_set(int new_fd);

#endif /* !POLLFD_H_ */
