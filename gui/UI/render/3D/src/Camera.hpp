/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Camera.hpp
*/
#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Camera {
    public:
        sf::Vector3f position;
        float pitch;
        float yaw;

        Camera();

        void move(float forward, float right, float up, float speed);
        sf::Vector3f getForwardVector() const;
        sf::Vector3f getRightVector() const;
};