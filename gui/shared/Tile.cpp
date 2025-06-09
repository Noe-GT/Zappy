/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Tile.cpp
*/
#include "Tile.hpp"

zappyGUI::Tile::Tile(const std::pair<size_t, size_t> &pos):
    _pos(pos)
{
    this->_ressources.push_back({std::make_shared<Food> (),0});
    this->_ressources.push_back({std::make_shared<Linemate> (),0});
    this->_ressources.push_back({std::make_shared<Deraumere> (),0});
    this->_ressources.push_back({std::make_shared<Sibur> (),0});
    this->_ressources.push_back({std::make_shared<Mendiane> (),0});
    this->_ressources.push_back({std::make_shared<Phiras> (),0});
    this->_ressources.push_back({std::make_shared<Thystame> (),0});
}

// zappyGUI::Tile::Tile(const zappyGUI::Tile &other):
//     _pos(other._pos),
//     _players(other.getPlayers()),
//     _ressources(other.getRessource())
// {
// }

zappyGUI::Tile::~Tile()
{
}

std::vector <std::shared_ptr <zappyGUI::Player>> &zappyGUI::Tile::getPlayers()
{
    return this->_players;
}

const std::vector <std::shared_ptr <zappyGUI::Player>> &zappyGUI::Tile::getPlayers() const
{
    return this->_players;
}

std::shared_ptr <zappyGUI::Player> &zappyGUI::Tile::getPlayer(int index)
{
    return this->_players.at(index);
}

std::vector <std::pair<std::shared_ptr <zappyGUI::IRessource>, int>> &zappyGUI::Tile::getRessource()
{
    return this->_ressources;
}

const std::pair<size_t, size_t> &zappyGUI::Tile::getPos() const
{
    return this->_pos;
}

void zappyGUI::Tile::setPlayer(std::vector <std::shared_ptr <zappyGUI::Player>> newVal)
{
    this->_players = newVal;
}

void zappyGUI::Tile::setRessource(std::vector <std::pair<std::shared_ptr <zappyGUI::IRessource>, int>> newVal)
{
    this->_ressources = newVal;
}

void zappyGUI::Tile::addPlayer(std::shared_ptr <zappyGUI::Player> newVal)
{
    this->_players.push_back(newVal);
}

void zappyGUI::Tile::addRessource(std::shared_ptr <zappyGUI::IRessource> newVal)
{
    this->_ressources.push_back({newVal, 1});
}
