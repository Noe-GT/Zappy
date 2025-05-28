/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Tile.cpp
*/
#include "Tile.hpp"

zappyGUI::Tile::Tile()
{
}

zappyGUI::Tile::~Tile()
{
}

std::vector <zappyGUI::Player> zappyGUI::Tile::getPlayers()
{
    return this->_player;
}

zappyGUI::Player zappyGUI::Tile::getPlayer(int index)
{
    return this->_player.at(index);
}

std::vector <zappyGUI::IRessource> zappyGUI::Tile::getRessource()
{
    return this->_ressource;
}

void zappyGUI::Tile::setPlayer(std::vector <zappyGUI::Player> newVal)
{
    this->_player = newVal;
}

void zappyGUI::Tile::setRessource(std::vector <zappyGUI::IRessource> newVal)
{
    this->_ressource = newVal;
}

void zappyGUI::Tile::addPlayer(zappyGUI::Player newVal)
{
    this->_player.push_back(newVal);
}

void zappyGUI::Tile::addRessource(zappyGUI::IRessource newVal)
{
    this->_ressource.push_back(newVal);
}
