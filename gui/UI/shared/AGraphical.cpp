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

std::shared_ptr<zappyGUI::Window> zappyGUI::AGraphical::getWindow() const
{
    return this->_window;
}

std::shared_ptr<zappyGUI::Window> zappyGUI::AGraphical::getWindow() const
{
    return this->_window;
}


void zappyGUI::AGraphical::initialize(std::shared_ptr<zappyGUI::GUI> gui)
{
    this->_window = gui->getWindow();
    this->_gui = gui;
}
