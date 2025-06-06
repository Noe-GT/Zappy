/*
** EPITECH PROJECT, 2025
** zappy - GUI
** File description:
** AGraphical
*/

#include "AGraphical.hpp"

zappyGUI::AGraphical::AGraphical()
{
}

void zappyGUI::AGraphical::display()
{

}

void zappyGUI::AGraphical::update()
{
}

void zappyGUI::AGraphical::handleEvents()
{
}

void zappyGUI::AGraphical::setWindow(std::shared_ptr<zappyGUI::Window> window)
{
    this->_window = window;
}

void zappyGUI::AGraphical::setGame(std::shared_ptr<zappyGUI::Game> game)
{
    this->_game = game;
}