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

std::vector <std::shared_ptr <zappyGUI::Player>> &zappyGUI::Tile::getPlayers()
{
    return this->_player;
}

std::shared_ptr <zappyGUI::Player> &zappyGUI::Tile::getPlayer(int index)
{
    return this->_player.at(index);
}

std::vector <std::pair<std::shared_ptr <zappyGUI::IRessource>, int>> &zappyGUI::Tile::getRessource()
{
    return this->_ressource;
}

void zappyGUI::Tile::setPlayer(std::vector <std::shared_ptr <zappyGUI::Player>> newVal)
{
    this->_player = newVal;
}

void zappyGUI::Tile::setRessource(std::vector <std::pair<std::shared_ptr <zappyGUI::IRessource>, int>> newVal)
{
    this->_ressource = newVal;
}

void zappyGUI::Tile::addPlayer(std::shared_ptr <zappyGUI::Player> newVal)
{
    this->_player.push_back(newVal);
}

void zappyGUI::Tile::addRessource(std::shared_ptr <zappyGUI::IRessource> newVal)
{
    this->_ressource.push_back({newVal, 1});
}

void zappyGUI::Tile::display()
{
 //TODO: draw smthg
}
