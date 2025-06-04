/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** protocol/src/network.c
*/

#include "../include/protocol.h"

#include <stdio.h>
#include <string.h>
#include <poll.h>

bool send(int fd, char *string)
{

    struct pollfd pfd = {fd, POLLOUT, 0};

    if (poll(&pfd, 1, 100) <= 0 || !(pfd.revents & POLLOUT)) {
        perror("[PROTOCOL] Poll failed\n");
        return false;
    }
    if (write(fd, string, strlen(string)) == -1) {
        perror("[PROTOCOL] Write failed\n");
        return false;
    }
    return true;
}

bool receive(int fd, circular_buffer_t *buffer)
{
    char buf[4096];
    ssize_t n = read(fd, buf, 4095);

    if (n == -1)
        perror("[PROTOCOL] Read failed\n");
    if (n == 0)
        return false;
    buf[n] = '\0';
    write_string(buffer, buf);
    return true;
}
