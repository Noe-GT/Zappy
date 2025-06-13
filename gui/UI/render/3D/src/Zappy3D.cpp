/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Zappy3D.cpp
*/

#include "Zappy3D.hpp"
#include <iostream>
#include "Cache.hpp"
#include <set>
zappyGUI::Zappy3D::Zappy3D() : _engine(), _camera()
{
    _camera.position = {0, 0, -5.0f};
    _camera.pitch = 0.0f;
    _camera.yaw = 0.0f;
}

void zappyGUI::Zappy3D::initialize(std::shared_ptr<zappyGUI::GUI> GUI)
{
    this->_gui = GUI;
    std::cout << "Zappy3D initialisé avec GUI" << std::endl;
    for (size_t y = 0; y < GUI->getGame()->getMap().size(); y++) {
        for (size_t x = 0; x < GUI->getGame()->getMap()[x].size(); x++) {
            _engine.addObj("./assets/island.obj", "./assets/island_material.mtl", {static_cast<float>(x), 0, static_cast<float>(y)}, {0, 0, 0}, {1, 1, 1});
            std::clog << _engine.getObjectCount()  << " " << x << " " << y << std::endl;
        }
    }
}

void zappyGUI::Zappy3D::handleEvents()
{
    if (_gui && _gui->getWindow()) {
        const float speed = 0.1f;
        const float rotSpeed = 0.02f;

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
            _camera.yaw -= rotSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            _camera.yaw += rotSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            _camera.pitch -= rotSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            _camera.pitch += rotSpeed;
    }
}

void zappyGUI::Zappy3D::display()
{
    if (_gui && _gui->getWindow()) {
        sf::RenderWindow& window = _gui->getWindow()->getRenderWindow();
        static int frameCount = 0;
        frameCount++;
        window.clear(sf::Color(50, 50, 100));
        _engine.draw(window);
        sf::CircleShape centerDot(2);
        centerDot.setFillColor(sf::Color::Red);
        centerDot.setPosition(window.getSize().x / 2 - 2, window.getSize().y / 2 - 2);
        window.draw(centerDot);
    }
}

void zappyGUI::Zappy3D::update()
{
    size_t count = 0;

    for (const auto& pair : this->_engine.getCache()) {
        if (pair.first == "./assets/island.obj|./assets/island_material.mtl")
            count += pair.second->instances.size();
        else
            this->_engine.getCache().erase(pair.first);
    }
    auto mapSize = this->_gui->getGame()->getMapSize();
    if (count != mapSize.first * mapSize.second) {
        _engine.clearObjects();
        for (size_t y = 0; y < mapSize.second; y++) {
            for (size_t x = 0; x < mapSize.first; x++)
                _engine.addObj("./assets/island.obj", "./assets/island_material.mtl", {static_cast<float>(x), 0, static_cast<float>(y)}, {0, 0, 0}, {1, 1, 1});
        }
    }
    std::set<std::tuple<float, float, float>> existingCubes;
    std::set<std::tuple<float, float, float>> neededCubes;
    for (const auto& pair : this->_engine.getCache()) {
        if (pair.first == "./assets/cube.obj|./assets/red.mtl") {
            for (const auto& instance : pair.second->instances) {
                auto pos = instance.transform.position;
                existingCubes.insert({pos.x, pos.y, pos.z});
            }
        }
    }
    for (size_t y = 0; y < mapSize.second; y++) {
        for (size_t x = 0; x < mapSize.first; x++) {
            for (int i = 0; i < 7; i++) {
                if (this->_gui->getGame()->getMap()[y][x].getRessource()[i].second > 0) {
                    float cubeY = 1.0f + (i / 6.0f);
                    neededCubes.insert({static_cast<float>(x), cubeY, static_cast<float>(y)});
                }
            }
        }
    }
    for (const auto& cubePos : existingCubes) {
        if (neededCubes.find(cubePos) == neededCubes.end()) {
            auto& instances = this->_engine.getCache()["./assets/cube.obj|./assets/red.mtl"]->instances;
            instances.erase(
                std::remove_if(instances.begin(), instances.end(),
                    [&cubePos](const auto& instance) {
                        auto pos = instance.transform.position;
                        return std::make_tuple(pos.x, pos.y, pos.z) == cubePos;
                    }),
                instances.end()
            );
        }
    }
    for (const auto& cubePos : neededCubes) {
        if (existingCubes.find(cubePos) == existingCubes.end()) {
            float x, y, z;
            std::tie(x, y, z) = cubePos;
            _engine.addObj("./assets/cube.obj", "./assets/red.mtl", {x, y, z}, {0, 0, 0}, {0.05, 0.05, 0.05});
        }
    }
    if (_gui && _gui->getWindow()) {
        sf::RenderWindow& window = _gui->getWindow()->getRenderWindow();
        sf::Vector2u windowSize = window.getSize();
        _engine.update(_camera, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
    }
}

extern "C" {
    zappyGUI::IGraphical* entryPoint() {
        return new zappyGUI::Zappy3D();
    }
}