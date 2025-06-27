/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** protocol.h
*/

#ifndef PROTOCOL_H_
    #define PROTOCOL_H_
    #include "circular_buffer.h"
    #include <stdbool.h>

bool send_message(int fd, char *fmt, ...);
bool receive(int fd, circular_buffer_t *buffer);

#endif /* !PROTOCOL_H_ */
