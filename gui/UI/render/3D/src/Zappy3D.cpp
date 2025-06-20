/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Zappy3D.cpp - Version corrigée pour SFML
*/

#include "Zappy3D.hpp"
#include <iostream>
#include "Cache.hpp"
#include <set>
#include <SFML/OpenGL.hpp>

zappyGUI::Zappy3D::Zappy3D() : _engine(), _camera()
{
    _camera.position = {0, 0, -5.0f};
    _camera.pitch = 0.0f;
    _camera.yaw = 0.0f;
    _mousePressed = false;
    _lastMousePos = {0, 0};
    _displayRessources = true;
    _selectedResourceType = -1;
}

void zappyGUI::Zappy3D::initialize(std::shared_ptr<zappyGUI::GUI> GUI)
{
    this->_gui = GUI;
    this->_fullscreen = GUI->getWindow()->isFullScreen();
    if (_gui && _gui->getWindow())
        _gui->getWindow()->getRenderWindow().setActive(true);
    _engine.initialize();
    for (size_t y = 0; y < GUI->getGame()->getMap().size(); y++) {
        for (size_t x = 0; x < GUI->getGame()->getMap()[x].size(); x++) {
            _engine.addObj("./assets/island.obj", "./assets/island_material.mtl", {static_cast<float>(x), 0, static_cast<float>(y)}, {0, 0, 0}, {1, 1, 1});
            std::clog << _engine.getObjectCount() << " " << x << " " << y << std::endl;
        }
    }

    auto mapSize = this->_gui->getGame()->getMapSize();
    float centerX = mapSize.first / 2.0f;
    float centerZ = mapSize.second / 2.0f;
    _mapCenter = {centerX, 0, centerZ};
    float distance = std::max(mapSize.first, mapSize.second) * 1.5f;
    _camera.position = {centerX, distance * 0.5f, centerZ - distance};
}


void zappyGUI::Zappy3D::handleEvents()
{
    float speed = 0.1f;
    int rotSpeed = 1;
    static bool key0Pressed = false;
    static bool key1Pressed = false;
    static bool key2Pressed = false;
    static bool key3Pressed = false;
    static bool key4Pressed = false;
    static bool key5Pressed = false;
    static bool key6Pressed = false;
    static bool key7Pressed = false;
    static bool keyRPressed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        _camera.move(1, 0, 0, speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        _camera.move(-1, 0, 0, speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        _camera.move(0, -1, 0, speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        _camera.move(0, 1, 0, speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        _camera.move(0, 0, 1, speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        _camera.move(0, 0, -1, speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        _camera.yaw += rotSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        _camera.yaw -= rotSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        _camera.pitch += rotSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        _camera.pitch -= rotSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        _engine._shadering = !_engine._shadering;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        _displayRessources = !_displayRessources;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        glm::vec3 hello =  _engine.screenToWorld(sf::Mouse::getPosition(_gui->getWindow()->getRenderWindow()).x, sf::Mouse::getPosition(_gui->getWindow()->getRenderWindow()).y, _gui->getWindow()->getRenderWindow().getSize().x, _gui->getWindow()->getRenderWindow().getSize().y, _camera);
        std::cout << static_cast<int> (hello.x + 0.5) << " " << static_cast <int > (hello.z + 0.5) << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
        _selectedResourceType = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        _selectedResourceType = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        _selectedResourceType = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        _selectedResourceType = 2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        _selectedResourceType = 3;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        _selectedResourceType = 4;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        _selectedResourceType = 5;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
        _selectedResourceType = 6;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        glm::vec3 hello = _engine.screenToWorld(sf::Mouse::getPosition(_gui->getWindow()->getRenderWindow()).x, sf::Mouse::getPosition(_gui->getWindow()->getRenderWindow()).y, _gui->getWindow()->getRenderWindow().getSize().x, _gui->getWindow()->getRenderWindow().getSize().y, _camera);
        std::cout << static_cast<int>(hello.x + 0.5) << " " << static_cast<int>(hello.z + 0.5) << std::endl;
    }
}

bool zappyGUI::Zappy3D::shouldDisplayResource(int resourceType)
{
    if (!_displayRessources)
        return false;
    if (_selectedResourceType == -1)
        return true;
    return _selectedResourceType == resourceType;
}

void zappyGUI::Zappy3D::display()
{
    sf::RenderWindow& window = _gui->getWindow()->getRenderWindow();
    window.setActive(true);
    window.clear(sf::Color(50, 50, 100));
    window.pushGLStates();

    glEnable(GL_DEPTH_TEST);
    glClearColor(50/255, 50/255, 100/255, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT);
    sf::Vector2u size = window.getSize();
    glViewport(0, 0, size.x, size.y);
    _engine.draw(_camera);
    window.popGLStates();
    sf::CircleShape centerDot(2);
    centerDot.setFillColor(sf::Color::Red);
    centerDot.setPosition(window.getSize().x / 2 - 2, window.getSize().y / 2 - 2);
    window.draw(centerDot);
}

void zappyGUI::Zappy3D::update()
{
    std::string resourceMaterials[7] = {
        "./assets/red.mtl",
        "./assets/green.mtl",
        "./assets/blue.mtl",
        "./assets/purple.mtl",
        "./assets/yellow.mtl",
        "./assets/brown.mtl",
        "./assets/cyan.mtl"
    };
    std::set<std::tuple<float, float, float, int>> existingCubes;
    std::set<std::tuple<float, float, float, int>> neededCubes;
    std::set<std::tuple<float, float, float>> existingPlayers;
    std::set<std::tuple<float, float, float>> neededPlayers;
    std::set<std::tuple<float, float, float>> existingEggs;
    std::set<std::tuple<float, float, float>> neededEggs;
    size_t cubeCount = 0;
    std::string playerCacheKey = std::string("./assets/player.obj|./assets/player.mtl");
    std::string eggCacheKey = std::string("./assets/egg.obj|./assets/egg.mtl");

    if (this->_gui->getWindow()->isFullScreen() != this->_fullscreen) {
        this->_fullscreen = !this->_fullscreen;
        _engine.clearObjects();
        _engine.initialize();
    }
    _camera.updateVectors();
    _gui->getWindow()->getRenderWindow().setActive(true);

    auto cacheIterator = this->_engine.getCache().begin();
    while (cacheIterator != this->_engine.getCache().end()) {
        if (cacheIterator->first == "./assets/island.obj|./assets/island_material.mtl") {
            cubeCount += cacheIterator->second->instances.size();
            ++cacheIterator;
        } else
            cacheIterator = this->_engine.getCache().erase(cacheIterator);
    }
    auto mapSize = this->_gui->getGame()->getMapSize();
    if (cubeCount != mapSize.first * mapSize.second) {
        _engine.clearObjects();
        for (size_t y = 0; y < mapSize.second; y++) {
            for (size_t x = 0; x < mapSize.first; x++)
                _engine.addObj("./assets/island.obj", "./assets/island_material.mtl", {static_cast<float>(x), 0, static_cast<float>(y)}, {0, 0, 0}, {1, 1, 1});
        }
        _mapCenter = {mapSize.first / 2.0f, 0, mapSize.second / 2.0f};
        float height = std::max(mapSize.first, mapSize.second) * 0.5f;
        _camera.position = {_mapCenter.x, height, _mapCenter.z};
        _camera.pitch = -89.0f;
        _camera.yaw = -90.0f;
    }
    for (int resourceType = 0; resourceType < 7; resourceType++) {
        std::string cacheKey = std::string("./assets/cube.obj|") + resourceMaterials[resourceType];
        auto cubeCache = this->_engine.getCache().find(cacheKey);
        if (cubeCache != this->_engine.getCache().end()) {
            for (const auto& instance : cubeCache->second->instances) {
                auto pos = instance.transform.position;
                existingCubes.insert({pos.x, pos.y, pos.z, resourceType});
            }
        }
    }

    auto playerCache = this->_engine.getCache().find(playerCacheKey);
    if (playerCache != this->_engine.getCache().end()) {
        for (const auto& instance : playerCache->second->instances) {
            auto pos = instance.transform.position;
            existingPlayers.insert({pos.x, pos.y, pos.z});
        }
    }

    auto eggCache = this->_engine.getCache().find(eggCacheKey);
    if (eggCache != this->_engine.getCache().end()) {
        for (const auto& instance : eggCache->second->instances) {
            auto pos = instance.transform.position;
            existingEggs.insert({pos.x, pos.y, pos.z});
        }
    }

    for (size_t y = 0; y < mapSize.second; y++) {
        for (size_t x = 0; x < mapSize.first; x++) {
            for (int i = 0; i < 7; i++) {
                if (this->_gui->getGame()->getMap()[y][x].getRessource()[i].second > 0 && shouldDisplayResource(i)) {
                    float cubeX = static_cast<float>(x) - 0.3 + ((i / 5) * 0.15);
                    float cubeY = 0.7;
                    float cubeZ = static_cast<float>(y) + ((i % 5) * 0.15) - 0.3;
                    neededCubes.insert({cubeX, cubeY, cubeZ, i});
                }
            }
            for (int i = 0; i < this->_gui->getGame()->getMap()[y][x].getPlayers().size(); i++) {
                neededPlayers.insert({x + 0.2, 0.7, y + 0.2});
            }
        }
    }

    for (int i = 0; i < _gui->getGame()->getEggs().size(); i++)
        neededEggs.insert({_gui->getGame()->getEggs()[i].first->getPos().first + 0.2, 0.7, _gui->getGame()->getEggs()[i].first->getPos().second - 0.2});

    for (const auto& existingCube : existingCubes) {
        if (neededCubes.find(existingCube) == neededCubes.end()) {
            float x, y, z;
            int resourceType;
            std::tie(x, y, z, resourceType) = existingCube;
            std::string CacheKey = std::string("./assets/cube.obj|") + resourceMaterials[resourceType];
            auto cubeCache = this->_engine.getCache().find(CacheKey);
            if (cubeCache != this->_engine.getCache().end()) {
                auto& instances = cubeCache->second->instances;
                instances.erase(
                    std::remove_if(instances.begin(), instances.end(),
                        [x, y, z](const auto& instance) {
                            auto pos = instance.transform.position;
                            return std::abs(pos.x - x) < 0.001f && std::abs(pos.y - y) < 0.001f && std::abs(pos.z - z) < 0.001f;
                        }),
                    instances.end()
                );
            }
        }
    }

    for (const auto& existingPlayer : existingPlayers) {
        if (neededPlayers.find(existingPlayer) == neededPlayers.end()) {
            float x, y, z;
            std::tie(x, y, z) = existingPlayer;
            auto playerCache = this->_engine.getCache().find(playerCacheKey);
            if (playerCache != this->_engine.getCache().end()) {
                auto& instances = playerCache->second->instances;
                instances.erase(
                    std::remove_if(instances.begin(), instances.end(),
                        [x, y, z](const auto& instance) {
                            auto pos = instance.transform.position;
                            return std::abs(pos.x - x) < 0.001f && std::abs(pos.y - y) < 0.001f && std::abs(pos.z - z) < 0.001f;
                        }),
                    instances.end()
                );
            }
        }
    }

    for (const auto& existingEgg : existingEggs) {
        if (neededEggs.find(existingEgg) == neededEggs.end()) {
            float x, y, z;
            std::tie(x, y, z) = existingEgg;
            auto eggCache = this->_engine.getCache().find(eggCacheKey);
            if (eggCache != this->_engine.getCache().end()) {
                auto& instances = eggCache->second->instances;
                instances.erase(
                    std::remove_if(instances.begin(), instances.end(),
                        [x, y, z](const auto& instance) {
                            auto pos = instance.transform.position;
                            return std::abs(pos.x - x) < 0.001f && std::abs(pos.y - y) < 0.001f && std::abs(pos.z - z) < 0.001f;
                        }),
                    instances.end()
                );
            }
        }
    }

    for (const auto& neededCube: neededCubes) {
        if (existingCubes.find(neededCube) == existingCubes.end()) {
            float x, y, z;
            int resourceType;
            std::tie(x, y, z, resourceType) = neededCube;
            _engine.addObj("./assets/cube.obj", resourceMaterials[resourceType], {x, y, z}, {0, 0 , 0}, {6, 6, 6});
        }
    }

    for (const auto& neededPlayer: neededPlayers) {
        if (existingPlayers.find(neededPlayer) == existingPlayers.end()) {
            float x, y, z;
            std::tie(x, y, z) = neededPlayer;
            _engine.addObj("./assets/player.obj", "assets/player.mtl", {x, y, z}, {0, 0, 0}, {0.1, 0.1, 0.1});
        }
    }

    for (const auto& neededEgg: neededEggs) {
        if (existingEggs.find(neededEgg) == existingEggs.end()) {
            float x, y, z;
            std::tie(x, y, z) = neededEgg;
            _engine.addObj("./assets/egg.obj", "assets/egg.mtl", {x, y, z}, {0, 0, 0}, {0.1, 0.1, 0.1});
        }
    }

    sf::Vector2u windowSize = _gui->getWindow()->getRenderWindow().getSize();
    _engine.update(_camera, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
}

extern "C" {
    zappyGUI::IGraphical* entryPoint() {
        return new zappyGUI::Zappy3D();
    }
}