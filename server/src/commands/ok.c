/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/ok.c
*/

#include "../../include/commands.h"

void command_ok(int fd)
{
    send_message(fd, "ok\n");
}
