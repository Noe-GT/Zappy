/*
** EPITECH PROJECT, 2024
** zap
** File description:
** GUI.cpp
*/
#include "GUI.hpp"

zappyGUI::GUI::GUI(int port, std::string hostname): _window(), _client(port, hostname)
{
}

void zappyGUI::GUI::display()
{
    this->_window.display();
    //FIXME: add the calls to the display of all elements of the map here
}

void zappyGUI::GUI::update()
{
    //FIXME: add the call to the client part here
}

void zappyGUI::GUI::events()
{
    while (this->_window.pollEvent(this->_window.getEvent())) {
        if (this->_window.getEvent().type == sf::Event::Closed)
            exit(0);
        if (this->_window.getEvent().type == sf::Event::KeyPressed && this->_window.getEvent().key.code == sf::Keyboard::Escape)
            this->_window.switchFullscreen();
    }
}


void zappyGUI::GUI::loop()
{
    while (this->_window.isOpen()) {
        this->events();
        this->update();
        this->display();
    }
}

zappyGUI::window zappyGUI::GUI::getWindow()
{
    return this->_window;
}

zappyGUI::Client zappyGUI::GUI::getClient()
{
    return this->_client;
}

zappyGUI::Game zappyGUI::GUI::getGame()
{
    return this->_game;
}