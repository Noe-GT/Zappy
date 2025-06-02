/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Window.cpp
*/

#include "Window.hpp"

zappyGUI::Window::Window()
{
    this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI");
    this->_window.setFramerateLimit(60);
    this->_isFullscreen = false;
}

zappyGUI::Window::~Window()
{
    this->_window.close();
}
zappyGUI::Window::Window(zappyGUI::Window &other)
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


void zappyGUI::Window::switchFullscreen()
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

bool zappyGUI::Window::pollEvent(sf::Event &event)
{
    return this->_window.pollEvent(event);
}

void zappyGUI::Window::display()
{
    this->_window.display();
    this->_window.clear();
}

sf::Event &zappyGUI::Window::getEvent()
{
    return this->_event;
}

bool zappyGUI::Window::isOpen()
{
    return this->_window.isOpen();
}

sf::RenderWindow &zappyGUI::Window::getRenderWindow()
{
    return this->_window;
}


