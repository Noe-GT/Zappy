/*
*** EPITECH PROJECT, 2024
*** zap
*** File description:
*** Structs.hpp
*/
#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

struct Material {
    std::string name;
    glm::vec4 ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
    glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
    glm::vec4 specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    float shininess = 32.0f;
    bool hasTexture = false;
    GLuint textureID = 0;
    std::string texturePath;
};

struct Transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f)): position(pos), rotation(rot), scale(scl) {}

    glm::mat4 getMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, scale);
        return model;
    }
};

struct Model {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<std::vector<int>> faces;
    std::vector<std::vector<int>> texIndices;
    std::vector<std::vector<int>> normalIndices;
    std::vector<int> materialIndices;

    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;

    std::vector<Vertex> processedVertices;
    std::vector<unsigned int> indices;
    bool buffersGenerated = false;

    std::vector<std::pair<int, int>> materialRanges;
    std::vector<int> materialForRange;
};

struct InstanceData {
    Transform transform;
    int materialIndex = 0;
};

struct RenderBatch {
    const Material* material = nullptr;
    GLuint VAO = 0;
    size_t indexCount = 0;
    size_t indexOffset = 0;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    float depth = 0.0f;
    int materialIndex = 0;
};