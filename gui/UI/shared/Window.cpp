/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Window.cpp
*/

#include "Window.hpp"

ZappyGui::window::window()
{
    this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI");
    this->_window.setFramerateLimit(60);
    this->_isFullscreen = false;
}

ZappyGui::window::~window()
{
    this->_window.close();
}

void ZappyGui::window::switchFullscreen()
{
    this->_isFullscreen = !this->_isFullscreen;
    this->_window.close();
    if (this->_isFullscreen) {
        this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", sf::Style::Fullscreen);
        this->_window.setFramerateLimit(60);
        return;
    }
    this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI");
    this->_window.setFramerateLimit(60);
}

bool ZappyGui::window::pollEvent(sf::Event &event)
{
    return this->_window.pollEvent(event);
}

void ZappyGui::window::display()
{
    this->_window.display();
    this->_window.clear();
}

sf::Event &ZappyGui::window::getEvent()
{
    return this->_event;
}

bool ZappyGui::window::isOpen()
{
    return this->_window.isOpen();
}


