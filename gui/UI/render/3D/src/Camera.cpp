/*
*** EPITECH PROJECT, 2024
*** zap
*** File description:
*** Camera.cpp
*/
#include "Camera.hpp"
#include <iostream>

Camera::Camera(): position(0.0f, 0.0f, 0.0f), pitch(0.0f), yaw(-90.0f), _worldUp(0.0f, 1.0f, 0.0f)
{
    updateVectors();
}

glm::vec3 Camera::getFront() const
{
    return _front;
}

glm::vec3 Camera::getRight() const
{
    return _right;
}

glm::vec3 Camera::getUp() const
{
    return _up;
}

void Camera::move(float forward, float right, float up, float speed)
{
    position += _front * forward * speed;
    position += _right * right * speed;
    position += _worldUp * up * speed;
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + _front, _up);
}

void Camera::updateVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    _front = glm::normalize(front);
    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}
