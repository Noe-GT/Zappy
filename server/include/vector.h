/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** vector.h
*/

#ifndef VECTOR_H_
    #define VECTOR_H_
    #include <stdint.h>

typedef struct vector2_s {
    uint32_t x;
    uint32_t y;
} vector2_t;

enum direction_e {
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

typedef enum direction_e direction_t;

#endif /* !VECTOR_H_ */
