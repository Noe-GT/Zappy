/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** circular_buffer.h
*/

#ifndef CIRCULAR_BUFFER_H_
    #define CIRCULAR_BUFFER_H_
    #include <unistd.h>

typedef struct circular_buffer_s {
    char *buffer;
    size_t read_idx;
    size_t write_idx;
    struct circular_buffer_s *next;
} circular_buffer_t;

// This can return NULL
circular_buffer_t *create_buffer(void);

void write_string(circular_buffer_t *buffer, char *string);

// Returns a heap allocated string, can be NULL.
char *read_string(circular_buffer_t *buffer);

void destroy_buffer(circular_buffer_t *buffer);

// This should be called to delete unused buffers every so often
circular_buffer_t *clean_buffer(circular_buffer_t *buffer);

#endif /* !CIRCULAR_BUFFER_H_ */
