/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Tile.cpp
*/
#include "Tile.hpp"

zappyGUI::Tile::Tile(): _playerSelector(std::vector<std::string>())
{
}

zappyGUI::Tile::~Tile()
{
}

std::vector <std::shared_ptr <zappyGUI::Player>> zappyGUI::Tile::getPlayers()
{
    return this->_players;
}

std::shared_ptr <zappyGUI::Player> zappyGUI::Tile::getPlayer(int index)
{
    return this->_players.at(index);
}

std::vector <std::shared_ptr <zappyGUI::IRessource>> zappyGUI::Tile::getRessource()
{
    return this->_ressources;
}

void zappyGUI::Tile::setPlayer(std::vector <std::shared_ptr <zappyGUI::Player>> newVal)
{
    this->_players = newVal;
}

void zappyGUI::Tile::setRessource(std::vector <std::shared_ptr <zappyGUI::IRessource>> newVal)
{
    this->_ressources = newVal;
}

void zappyGUI::Tile::addPlayer(std::shared_ptr <zappyGUI::Player> newVal)
{
    this->_players.push_back(newVal);
}

void zappyGUI::Tile::addRessource(std::shared_ptr <zappyGUI::IRessource> newVal)
{
    this->_ressources.push_back(newVal);
}


void display();
