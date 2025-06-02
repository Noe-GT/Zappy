/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** client_list
*/

#include "../include/tests.h"

static bool test_list(client_list_t *list, int count, ...)
{
    client_t *parse = list->begin;
    va_list args;
    va_start(args, count);
    int i;

    for (i = 0; !(parse == NULL && count == i); i++) {
        if (parse->id != va_arg(args, int)) {
            va_end(args);
            return false;
        }
        parse = parse->next;
    }
    va_end(args);
    if (i == count)
        return true;
    return false;
}

Test(clien_list, create)
{
    client_list_t *list =  init_client_list();
    bool pass;

    pass = (list != NULL && list->begin == NULL && list->end == NULL);
    cl_destroy(list);
    cr_assert(pass);
}

Test(clien_list, add)
{
    client_list_t *list =  init_client_list();
    bool pass;

    cl_add_end(list, 1);
    pass = (test_list(list, 1, 1));
    cl_destroy(list);
    cr_assert(pass);
}

Test(clien_list, add_multiple)
{
    client_list_t *list =  init_client_list();
    bool pass;

    cl_add_end(list, 1);
    cl_add_end(list, 2);
    cl_add_end(list, 3);
    pass = (test_list(list, 3, 1, 2, 3));
    cl_destroy(list);
    cr_assert(pass);
}

Test(clien_list, remove)
{
    client_list_t *list =  init_client_list();
    bool pass;

    cl_add_end(list, 1);
    cl_add_end(list, 2);
    cl_add_end(list, 3);
    cl_remove(list, 2);
    pass = (test_list(list, 2, 1, 3));
    cl_destroy(list);
    cr_assert(pass);
}

Test(clien_list, remove_begin)
{
    client_list_t *list =  init_client_list();
    bool pass;

    cl_add_end(list, 1);
    cl_add_end(list, 2);
    cl_add_end(list, 3);
    cl_remove(list, 1);
    pass = (test_list(list, 2, 2, 3));
    cl_destroy(list);
    cr_assert(pass);
}

Test(clien_list, remove_end)
{
    client_list_t *list =  init_client_list();
    bool pass;

    cl_add_end(list, 1);
    cl_add_end(list, 2);
    cl_add_end(list, 3);
    cl_remove(list, 3);
    pass = (test_list(list, 2, 1, 2));
    cl_destroy(list);
    cr_assert(pass);
}

Test(clien_list, remove_nonexistant)
{
    client_list_t *list =  init_client_list();
    bool pass;

    cl_add_end(list, 1);
    cl_add_end(list, 2);
    cl_remove(list, 3);
    pass = (test_list(list, 2, 1, 2));
    cl_destroy(list);
    cr_assert(pass);
}

Test(clien_list, remove_empty)
{
    client_list_t *list =  init_client_list();
    bool pass;

    cl_remove(list, 3);
    pass = (list->begin == NULL && list->end == NULL);
    cl_destroy(list);
    cr_assert(pass);
}

Test(clien_list, destroy_empty)
{
    client_list_t *list =  init_client_list();

    list = cl_destroy(list);
    cr_assert(list == NULL);
}

Test(clien_list, destroy)
{
    client_list_t *list =  init_client_list();

    cl_add_end(list, 1);
    list = cl_destroy(list);
    cr_assert(list == NULL);
}
