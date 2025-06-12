/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Cache.hpp
*/
#pragma once
#include "Engine.hpp"

class Cache {
    public:
        Cache(const std::string &objPath, const std::string& mtlPath);

        Model model;
        std::vector<Material> materials;
        std::vector<InstanceData> instances;
        std::string objPath;
        std::string mtlPath;
};