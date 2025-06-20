/*
*** EPITECH PROJECT, 2024
*** zap
*** File description:
*** Cache.cpp
*/
#include "Cache.hpp"
#include <iostream>
#include <map>

Cache::Cache(const std::string& objPath, const std::string& mtlPath)
    : objPath(objPath), mtlPath(mtlPath)
{
}

Cache::~Cache()
{
    if (model.buffersGenerated) {
        glDeleteVertexArrays(1, &model.VAO);
        glDeleteBuffers(1, &model.VBO);
        glDeleteBuffers(1, &model.EBO);
        model.buffersGenerated = false;
    }
    for (auto& material : materials) {
        if (material.textureID != 0) {
            glDeleteTextures(1, &material.textureID);
            material.textureID = 0;
        }
    }
}

void Cache::generateBuffers()
{
    std::map<int, std::vector<size_t>> materialsFaces;
    if (model.buffersGenerated)
        return;
    model.processedVertices.clear();
    model.indices.clear();
    model.materialRanges.clear();
    model.materialForRange.clear();
    for (size_t i = 0; i < model.faces.size(); ++i) {
        int materialIndex = (i < model.materialIndices.size()) ? model.materialIndices[i] : 0;
        materialsFaces[materialIndex].push_back(i);
    }
    for (const auto& pair : materialsFaces) {
        int materialIndex = pair.first;
        const std::vector<size_t>& faceIndices = pair.second;
        size_t startIndex = model.indices.size();
        for (size_t faceIdx : faceIndices) {
            const std::vector<int>& face = model.faces[faceIdx];
            if (face.size() < 3)
                continue;
            const std::vector<int>& normalIndices = (faceIdx < model.normalIndices.size()) ? model.normalIndices[faceIdx] : std::vector<int>();
            for (size_t j = 1; j < face.size() - 1; ++j) {
                int indices[3] = {0, static_cast<int>(j), static_cast<int>(j + 1)};
                for (int k = 0; k < 3; ++k) {
                    Vertex vertex;
                    vertex.position = model.vertices[face[indices[k]]];
                    if (faceIdx < model.texIndices.size() &&
                        indices[k] < static_cast<int>(model.texIndices[faceIdx].size())) {
                        int texIdx = model.texIndices[faceIdx][indices[k]];
                        if (texIdx >= 0 && texIdx < static_cast<int>(model.texCoords.size()))
                            vertex.texCoord = model.texCoords[texIdx];
                        else
                            vertex.texCoord = glm::vec2(0.0f, 0.0f);
                    } else
                        vertex.texCoord = glm::vec2(0.0f, 0.0f);
                    if (indices[k] < static_cast<int>(normalIndices.size())) {
                        int normalIdx = normalIndices[indices[k]];
                        if (normalIdx >= 0 && normalIdx < static_cast<int>(model.normals.size()))
                            vertex.normal = model.normals[normalIdx];
                        else
                            vertex.normal = calculateFaceNormal(face, faceIdx);
                    } else
                        vertex.normal = calculateFaceNormal(face, faceIdx);
                    model.processedVertices.push_back(vertex);
                    model.indices.push_back(model.processedVertices.size() - 1);
                }
            }
        }
        size_t endIndex = model.indices.size();
        size_t count = endIndex - startIndex;
        if (count > 0) {
            model.materialRanges.push_back({static_cast<int>(startIndex), static_cast<int>(count)});
            model.materialForRange.push_back(materialIndex);
        }
    }

    glGenVertexArrays(1, &model.VAO);
    glGenBuffers(1, &model.VBO);
    glGenBuffers(1, &model.EBO);
    glBindVertexArray(model.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, model.VBO);
    glBufferData(GL_ARRAY_BUFFER, model.processedVertices.size() * sizeof(Vertex), model.processedVertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(unsigned int), model.indices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
    model.buffersGenerated = true;
}

glm::vec3 Cache::calculateFaceNormal(const std::vector<int>& face, size_t faceIdx)
{
    if (face.size() < 3)
        return glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 v0 = model.vertices[face[0]];
    glm::vec3 v1 = model.vertices[face[1]];
    glm::vec3 v2 = model.vertices[face[2]];
    glm::vec3 edge1 = v1 - v0;
    glm::vec3 edge2 = v2 - v0;
    return glm::normalize(glm::cross(edge1, edge2));
}
