/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** instruction_queue
*/

#ifndef INSTRUCTION_QUEUE_H_
    #define INSTRUCTION_QUEUE_H_
    #include "external.h"

typedef struct instruction_queue_s {
    size_t cp_id;
    char *instruction;
    struct instruction_queue_s *next;
} instruction_queue_t;

#endif /* !INSTRUCTION_QUEUE_H_ */
