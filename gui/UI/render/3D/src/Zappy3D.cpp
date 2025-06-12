/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Zappy3D.cpp
*/

#include "Zappy3D.hpp"
#include <iostream>

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
            _engine.addObj("./model.obj", "./materials.mtl", {static_cast<float>(x), 0, static_cast<float>(y)}, {0, 0, 0}, {1, 1, 1});
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
    auto mapSize = this->_gui->getGame()->getMapSize();
    if (this->_engine.getObjectCount() != mapSize.first * mapSize.second) {
        for (size_t y = 0; y < mapSize.second; y++) {
            for (size_t x = 0; x < mapSize.first; x++)
            _engine.addObj("./assets/island.obj", "./assets/island_material.mtl", {static_cast<float>(x), 0, static_cast<float>(y)}, {0, 0, 0}, {1, 1, 1});
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