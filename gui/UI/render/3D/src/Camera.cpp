/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Camera.cpp
*/
#include "Camera.hpp"

Camera::Camera(): position(0, 0, 0), pitch(0), yaw(0)
{
}

sf::Vector3f Camera::getForwardVector() const
{
    return sf::Vector3f(
        std::sin(yaw) * std::cos(pitch),
        -std::sin(pitch),
        std::cos(yaw) * std::cos(pitch)
    );
}

sf::Vector3f Camera::getRightVector() const
{
    return sf::Vector3f(
        std::cos(yaw),
        0,
        -std::sin(yaw)
    );
}

void Camera::move(float forward, float right, float up, float speed)
{
    sf::Vector3f forwardVec = getForwardVector();
    sf::Vector3f rightVec = getRightVector();

    position.x += forwardVec.x * forward * speed;
    position.y += forwardVec.y * forward * speed;
    position.z += forwardVec.z * forward * speed;

    position.x += rightVec.x * right * speed;
    position.z += rightVec.z * right * speed;

    position.y += up * speed;
}