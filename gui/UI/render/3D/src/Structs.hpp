/*
** EPITECH PROJECT, 2024
** zap
** File description:
** structs.hpp
*/
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#pragma once
#include <SFML/Graphics.hpp>

struct Material {
    sf::Color ambient;
    sf::Color diffuse;
    sf::Color specular;
    float shininess;
    sf::Texture diffuseTexture;
    bool hasTexture;
    std::string name;

    Material(): ambient(sf::Color::White), diffuse(sf::Color::White), specular(sf::Color::White), shininess(0.0f), hasTexture(false) {}
};

struct Model {
    std::vector<sf::Vector3f> vertices;
    std::vector<sf::Vector2f> texCoords;
    std::vector<std::vector<int>> faces;
    std::vector<std::vector<int>> texIndices;
    std::vector<int> materialIndices;
};

struct TriangleData {
    sf::VertexArray vertices;
    float depth;
    const Material* material;
};

struct Transform {
    sf::Vector3f position;
    sf::Vector3f rotation;
    sf::Vector3f scale;

    Transform(): position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) {}
    Transform(sf::Vector3f pos, sf::Vector3f rot, sf::Vector3f scl): position(pos), rotation(rot), scale(scl) {}
};

struct InstanceData {
    Transform transform;
    int materialIndex;
};
