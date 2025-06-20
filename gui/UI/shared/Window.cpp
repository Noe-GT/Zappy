/*
*** EPITECH PROJECT, 2024*
*** zap*
*** File description:*
*** Window.cpp*
*/
#include "Window.hpp"
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/RenderStates.hpp>
zappyGUI::Window::Window(): _isFullscreen(false)
{
    glEnable(GL_TEXTURE_2D);
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", sf::Style::Default, settings);
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
    glEnable(GL_TEXTURE_2D);
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    if (other._isFullscreen) {
        this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", sf::Style::Fullscreen, settings);
    } else {
        this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", sf::Style::Default, settings);
    }
    this->_window.setFramerateLimit(60);
}

zappyGUI::Window& zappyGUI::Window::operator=(const zappyGUI::Window &other)
{
    if (this != &other) {
        glEnable(GL_TEXTURE_2D);
        sf::ContextSettings settings;
        settings.depthBits = 24;
        settings.stencilBits = 8;
        settings.antialiasingLevel = 4;
        settings.majorVersion = 3;
        settings.minorVersion = 0;

        this->_isFullscreen = other._isFullscreen;

        if (other._isFullscreen) {
            this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", sf::Style::Fullscreen, settings);
        } else {
            this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", sf::Style::Default, settings);
        }
        this->_window.setFramerateLimit(60);
    }
    return *this;
}

void zappyGUI::Window::switchFullscreen()
{
    glEnable(GL_TEXTURE_2D);
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    this->_isFullscreen = !this->_isFullscreen;
    auto style = this->_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    this->_window.create(sf::VideoMode(1920, 1080), "Zappy - GUI", style, settings);
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

bool zappyGUI::Window::isFullScreen()
{
    return this->_isFullscreen;
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
