/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** protocol/src/circular_buffer.c
*/

#include "../include/circular_buffer.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

circular_buffer_t *create_buffer(void)
{
    circular_buffer_t *buffer = malloc(sizeof(circular_buffer_t));

    if (buffer == NULL)
        return NULL;
    buffer->buffer = malloc(sizeof(uint8_t) * getpagesize());
    buffer->buffer = memset(buffer->buffer, 0, getpagesize());
    buffer->read_idx = 0;
    buffer->write_idx = 0;
    buffer->next = NULL;
    return buffer;
}

static circular_buffer_t *get_last_page(circular_buffer_t *buffer)
{
    if (buffer == NULL)
        return NULL;
    if (buffer->next == NULL)
        return buffer;
    return get_last_page(buffer->next);
}

void write_string(circular_buffer_t *buffer, char *string)
{
    circular_buffer_t *page = get_last_page(buffer);
    const size_t length = strlen(string);
    size_t to_copy = getpagesize() - page->write_idx;

    if (length + page->write_idx >= (size_t)getpagesize()) {
        memcpy(page->buffer + page->write_idx, string, to_copy);
        page->write_idx = getpagesize() - 1;
        page->next = create_buffer();
        return write_string(page->next, string + to_copy);
    } else {
        memcpy(page->buffer + page->write_idx, string, length);
        page->write_idx += length;
    }
}

static size_t get_bytes_to_read(circular_buffer_t *buffer)
{
    size_t bytes_to_read = 0;
    size_t available;
    char *start;

    for (circular_buffer_t *curr = buffer; curr != NULL; curr = curr->next) {
        available = (size_t)getpagesize() - curr->read_idx;
        start = memchr(curr->buffer + curr->read_idx, '\n', available);
        if (start == NULL) {
            bytes_to_read += available;
            continue;
        }
        bytes_to_read += (start - (curr->buffer + curr->read_idx));
        return bytes_to_read + 1;
    }
    return 0;
}

// Can return NULL, but should never happen
static char *concat_pages(circular_buffer_t *buffer, size_t bytes_to_read)
{
    char *string = malloc(sizeof(char) * bytes_to_read + 1);
    char *newline;
    size_t available;

    string = strcpy(string, "");
    for (circular_buffer_t *curr = buffer; curr != NULL; curr = curr->next) {
        available = (size_t)getpagesize() - curr->read_idx;
        newline = memchr(curr->buffer + curr->read_idx, '\n', available);
        if (newline) {
            available = newline - (curr->buffer + curr->read_idx) + 1;
            string = strncat(string, curr->buffer + curr->read_idx, available);
            curr->read_idx += available;
            return string;
        } else {
            string = strncat(string, curr->buffer + curr->read_idx, available);
            curr->read_idx = getpagesize() - 1;
        }
    }
    dprintf(2, "[PROTOCOL] Warning: Impossible page state\n");
    return NULL;
}

char *read_string(circular_buffer_t *buffer)
{
    size_t bytes_to_read;

    if (buffer == NULL)
        return NULL;
    if (buffer->read_idx == (size_t)getpagesize() - 1)
        return read_string(buffer->next);
    bytes_to_read = get_bytes_to_read(buffer);
    if (bytes_to_read == 0)
        return NULL;
    return concat_pages(buffer, bytes_to_read);
}

void destroy_buffer(circular_buffer_t *buffer)
{
    if (buffer == NULL)
        return;
    destroy_buffer(buffer->next);
    free(buffer->buffer);
    free(buffer);
}

circular_buffer_t *clean_buffer(circular_buffer_t *buffer)
{
    circular_buffer_t *next;

    if (buffer == NULL)
        return create_buffer();
    if (buffer->read_idx == (size_t)getpagesize() - 1) {
        next = buffer->next;
        free(buffer->buffer);
        free(buffer);
        return clean_buffer(next);
    }
    return buffer;
}

void free_str(char *str)
{
    free(str);
}
