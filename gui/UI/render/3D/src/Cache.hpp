/*
*** EPITECH PROJECT, 2024
*** zap
*** File description:
*** Cache.hpp
*/
#pragma once

#include "Structs.hpp"
#include <string>
#include <vector>

class Cache {
public:
    Cache(const std::string& objPath, const std::string& mtlPath);
    ~Cache();

    void generateBuffers();
    Model model;
    std::vector<Material> materials;
    std::vector<InstanceData> instances;
    std::string objPath;
    std::string mtlPath;
private:
    glm::vec3 calculateFaceNormal(const std::vector<int>& face, size_t faceIdx);

};