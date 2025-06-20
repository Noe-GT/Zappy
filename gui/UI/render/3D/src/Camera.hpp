/*
*** EPITECH PROJECT, 2024
*** zap
*** File description:
*** Camera.hpp
*/
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

class Camera {
    public:
        glm::vec3 position;
        float pitch;
        float yaw;

        Camera();

        void move(float forward, float right, float up, float speed);
        glm::vec3 getFront() const;
        glm::vec3 getRight() const;
        glm::vec3 getUp() const;
        glm::mat4 getViewMatrix() const;

        void updateVectors();
        glm::vec3 _front;

        glm::vec3 _right;
        glm::vec3 _up;
    private:
        glm::vec3 _worldUp;
};