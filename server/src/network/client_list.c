/*
** EPITECH PROJECT, 2025
** zappy -server
** File description:
** client_list
*/

#include "../../include/client_list.h"

client_list_t *init_client_list()
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
    if (client->read_buffer != NULL)
        free(client->read_buffer);
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
    return NULL;
}

void cl_display(client_list_t *list)
{
    client_t *parse = list->begin;
    size_t count = 0;

    printf("CLIENT LIST:\n");
    while (parse != NULL) {
        count++;
        printf("(%ld) id : %d\n", count, parse->id);
        parse = parse->next;
    }
}

static client_t *new_node(int id)
{
    client_t *new = malloc(sizeof(client_t));

    new->id = id;
    new->next = NULL;
    return new;
}

client_list_t *cl_add_end(client_list_t *list, int id)
{
    if (list->begin == NULL) {
        list->begin = new_node(id);
        list->end = list->begin;
        return list;
    }
    list->end -> next = new_node(id);
    list->end = list->end->next;
    return list;
}

client_list_t *cl_remove(client_list_t *list, int id)
{
    client_t *parse = list->begin;
    client_t *previous = NULL;

    while (!(parse == NULL || parse->id == id)) {
        previous = parse;
        parse = parse->next;
    }
    if (parse == NULL) {
        fprintf(stderr, "cl remove: id out of range\n");
        return list;
    } else {
        if (previous != NULL) {
            previous->next = parse->next;
            free(parse);
        } else {
            list->begin = parse->next;
            if (list->end == parse)
                list->end = list->begin;
        }
    }
    return list;
}
