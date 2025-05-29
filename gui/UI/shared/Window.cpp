/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Window.cpp
*/

#include "Window.hpp"

ZappyGui::Window::Window()
{
    this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI");
    this->_window.setFramerateLimit(60);
    this->_isFullscreen = false;
}

ZappyGui::Window::~Window()
{
    this->_window.close();
}

void ZappyGui::Window::switchFullscreen()
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

bool ZappyGui::Window::pollEvent(sf::Event &event)
{
    return this->_window.pollEvent(event);
}

void ZappyGui::Window::display()
{
    this->_window.display();
    this->_window.clear();
}

sf::Event &ZappyGui::Window::getEvent()
{
    return this->_event;
}

bool ZappyGui::Window::isOpen()
{
    return this->_window.isOpen();
}

sf::RenderWindow &ZappyGui::Window::getRenderWindow()
{
    return this->_window;
}


