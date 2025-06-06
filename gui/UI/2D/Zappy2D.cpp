/*
** EPITECH PROJECT, 2025
** zappy - gui
** File description:
** Zappy2D
*/

#include "Zappy2D.hpp"

zappyGUI::Zappy2D::Zappy2D(zappyGUI::Window &window, zappyGUI::Game &game):
    zappyGUI::AGraphical(window, game)
{
}

void zappyGUI::Zappy2D::display()
{
    for (const std::vector<zappyGUI::Tile>& tileLine: this->_game.getMap()) {
        for (const zappyGUI::Tile &t : tileLine) {
            this->
        }
    }
}

void zappyGUI::Zappy2D::update()
{
}

void zappyGUI::Zappy2D::handleEvents()
{
}
