/*
** EPITECH PROJECT, 2025
** zappy -server
** File description:
** client_list
*/

#include "../../include/client_list.h"

client_list_t *init_client_list(void)
{
    client_list_t *list = malloc(sizeof(client_list_t));

    list->begin = NULL;
    list->end = NULL;
    return list;
}

static void client_destroy(client_t *client)
{
    if (client == NULL)
        return;
    destroy_buffer(client->buffer);
    free(client);
}

client_list_t *cl_destroy(client_list_t *list)
{
    client_t *parse = list->begin;
    client_t *next;

    while (parse != NULL) {
        next = parse->next;
        client_destroy(parse);
        parse = next;
    }
    free(list);
    return NULL;
}

static client_t *new_node(int fd)
{
    client_t *new = malloc(sizeof(client_t));

    new->id = fd;
    new->fd = fd;
    new->next = NULL;
    new->buffer = create_buffer();
    return new;
}

void cl_add_end(client_list_t *list, int fd)
{
    if (list->begin == NULL) {
        list->begin = new_node(fd);
        list->end = list->begin;
        return;
    }
    list->end->next = new_node(fd);
    list->end = list->end->next;
}

void cl_remove(client_list_t *list, int id)
{
    client_t *parse = list->begin;
    client_t *previous = NULL;

    while (!(parse == NULL || parse->id == id)) {
        previous = parse;
        parse = parse->next;
    }
    if (parse == NULL) {
        fprintf(stderr, "cl remove: id(%d) out of range\n", id);
        return;
    }
    if (previous != NULL) {
        previous->next = parse->next;
    } else {
        list->begin = parse->next;
        if (list->end == parse)
            list->end = list->begin;
    }
    destroy_buffer(parse->buffer);
    free(parse);
}

client_t *cl_get(client_list_t *list, int id)
{
    client_t *parse = list->begin;

    while (!(parse == NULL || parse->id == id))
        parse = parse->next;
    if (parse == NULL)
        fprintf(stderr, "cl get: id(%d) out of range\n", id);
    return parse;
}
