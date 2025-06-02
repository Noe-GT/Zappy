/*
*** EPITECH PROJECT, 2024*
*** zap*
*** File description:*
*** Window.cpp*
*/
#include "Window.hpp"

zappyGUI::window::window() : _isFullscreen(false)
{
    this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI");
    this->_window.setFramerateLimit(60);
}

zappyGUI::window::~window()
{
    if (this->_window.isOpen()) {
        this->_window.close();
    }
}

zappyGUI::window::window(const zappyGUI::window &other) : _isFullscreen(other._isFullscreen)
{
    if (other._isFullscreen) {
        this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", sf::Style::Fullscreen);
    } else {
        this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", sf::Style::Default);
    }
    this->_window.setFramerateLimit(60);
}

zappyGUI::window& zappyGUI::window::operator=(const zappyGUI::window &other)
{
    if (this != &other) {
        this->_isFullscreen = other._isFullscreen;

        if (other._isFullscreen) {
            this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", sf::Style::Fullscreen);
        } else {
            this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", sf::Style::Default);
        }
        this->_window.setFramerateLimit(60);
    }
    return *this;
}

void zappyGUI::window::switchFullscreen()
{
    this->_isFullscreen = !this->_isFullscreen;
    auto style = this->_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", style);
    this->_window.setFramerateLimit(60);
}

bool zappyGUI::window::pollEvent()
{
    return this->_window.pollEvent(this->_event);
}

void zappyGUI::window::display()
{
    this->_window.clear();
    this->_window.display();
}

void zappyGUI::window::clear()
{
    this->_window.clear();
}

void zappyGUI::window::close()
{
    this->_window.close();
}

bool zappyGUI::window::isOpen()
{
    return this->_window.isOpen();
}

sf::RenderWindow& zappyGUI::window::getRenderWindow()
{
    return this->_window;
}

sf::Event &zappyGUI::window::getEvent()
{
    return this->_event;
}