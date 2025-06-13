/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Engine.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <unordered_map>
#include "Structs.hpp"
#include "Camera.hpp"
class Cache;
class Engine {
    public:
        Engine();
        ~Engine();

        bool addObj(const std::string& objPath, const std::string& mtlPath, sf::Vector3f position = sf::Vector3f(0, 0, 0), sf::Vector3f rotation = sf::Vector3f(0, 0, 0), sf::Vector3f scale = sf::Vector3f(1, 1, 1));
        void update(const Camera& camera, float width = 1920, float height = 1080);
        void draw(sf::RenderWindow& window);
        void clearObjects();
        size_t getObjectCount() const;
        std::unordered_map<std::string, std::shared_ptr<Cache>> getCache();

    private:
        bool loadResources(Cache& model);
        bool loadOBJ(Cache& model);
        bool loadMTL(Cache& model);
        sf::Vector2f project(const sf::Vector3f& point, float width, float height, const Camera& camera) const;
        sf::Vector3f crossProduct(const sf::Vector3f& a, const sf::Vector3f& b) const;
        void processInstance(const Cache& Cache, const InstanceData& instance, const Camera& camera, float width, float height, float cosYaw, float sinYaw, float cosPitch, float sinPitch, float tanHalfFov, float aspectRatio);
        std::unordered_map<std::string, std::shared_ptr<Cache>> _modelCache;
        std::vector<std::shared_ptr<Cache>> _visibleModels;
        std::vector<TriangleData> _trianglesToRender;
};