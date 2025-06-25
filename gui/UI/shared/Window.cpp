/*
*** EPITECH PROJECT, 2024*
*** zap*
*** File description:*
*** Window.cpp*
*/

#include "Window.hpp"

zappyGUI::Window::Window(): _isFullscreen(false)
{
    this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI");
    this->_window.setFramerateLimit(60);
}

zappyGUI::Window::~Window()
{
    if (this->_window.isOpen()) {
        this->_window.close();
    }
}

zappyGUI::Window::Window(const zappyGUI::Window &other) : _isFullscreen(other._isFullscreen)
{
    if (other._isFullscreen) {
        this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", sf::Style::Fullscreen);
    } else {
        this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", sf::Style::Default);
    }
    this->_window.setFramerateLimit(60);
}

zappyGUI::Window& zappyGUI::Window::operator=(const zappyGUI::Window &other)
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

void zappyGUI::Window::switchFullscreen()
{
    this->_isFullscreen = !this->_isFullscreen;
    auto style = this->_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", style);
    this->_window.setFramerateLimit(60);
}

bool zappyGUI::Window::pollEvent()
{
    return this->_window.pollEvent(this->_event);
}

void zappyGUI::Window::display()
{
    this->_window.display();
}

void zappyGUI::Window::clear()
{
    // this->_window.clear(sf::Color(225, 247, 213));
    this->_window.clear(sf::Color::Black);
}

void zappyGUI::Window::close()
{
    this->_window.close();
}

bool zappyGUI::Window::isOpen()
{
    return this->_window.isOpen();
}

sf::RenderWindow& zappyGUI::Window::getRenderWindow()
{
    return this->_window;
}

sf::Event &zappyGUI::Window::getEvent()
{
    return this->_event;
}

std::pair<size_t, size_t> zappyGUI::Window::getSize() const
{
    return {this->_window.getSize().x, this->_window.getSize().y};
}
