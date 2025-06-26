/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** protocol/src/utils.c
*/

#include "../include/circular_buffer.h"

#include <stdlib.h>

void free_str(char *str)
{
    free(str);
}
