/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Window.cpp
*/

#include "Window.hpp"

zappyGUI::window::window()
{
    this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI");
    this->_window.setFramerateLimit(60);
    this->_isFullscreen = false;
}

zappyGUI::window::~window()
{
    this->_window.close();
}
zappyGUI::window::window(zappyGUI::window &other)
{
    if (other._isFullscreen) {
        this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", sf::Style::Fullscreen);
        this->_window.setFramerateLimit(60);
        this->_isFullscreen = true;
    }
    this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI");
    this->_window.setFramerateLimit(60);
    this->_isFullscreen = false;
}


void zappyGUI::window::switchFullscreen()
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

bool zappyGUI::window::pollEvent(sf::Event &event)
{
    return this->_window.pollEvent(event);
}

void zappyGUI::window::display()
{
    this->_window.display();
    this->_window.clear();
}

sf::Event &zappyGUI::window::getEvent()
{
    return this->_event;
}

bool zappyGUI::window::isOpen()
{
    return this->_window.isOpen();
}


