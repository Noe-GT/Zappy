/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/ko.c
*/

#include "../../include/commands.h"

void command_ko(int fd)
{
    send_message(fd, "ko\n");
}
