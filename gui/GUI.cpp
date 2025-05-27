/*
** EPITECH PROJECT, 2024
** zap
** File description:
** GUI.cpp
*/
#include "GUI.hpp"

ZappyGui::GUI::GUI(int port, std::string hostname): _window(), _client(port, hostname)
{
}

void ZappyGui::GUI::display()
{
    this->_window.display();
    //FIXME: add the calls to the display of all elements of the map here
}

void ZappyGui::GUI::update()
{
    //FIXME: add the call to the client part here
}

void ZappyGui::GUI::events()
{
    while (this->_window.pollEvent(this->_window.getEvent())) {
        if (this->_window.getEvent().type == sf::Event::Closed)
            exit(0);
        if (this->_window.getEvent().type == sf::Event::KeyPressed && this->_window.getEvent().key.code == sf::Keyboard::Escape)
            this->_window.switchFullscreen();
    }
}


void ZappyGui::GUI::loop()
{
    while (this->_window.isOpen()) {
        this->events();
        this->update();
        this->display();
    }
}