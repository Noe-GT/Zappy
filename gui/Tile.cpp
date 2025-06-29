/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Tile.cpp
*/
#include "Tile.hpp"
#include <iostream>

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

zappyGUI::Tile::Tile(const zappyGUI::Tile &other):
    _pos(other._pos),
    _players(other.getPlayers())
{
    this->_ressources.push_back({std::make_shared<Food> (),other._ressources[0].second});
    this->_ressources.push_back({std::make_shared<Linemate> (),other._ressources[1].second});
    this->_ressources.push_back({std::make_shared<Deraumere> (),other._ressources[2].second});
    this->_ressources.push_back({std::make_shared<Sibur> (),other._ressources[3].second});
    this->_ressources.push_back({std::make_shared<Mendiane> (),other._ressources[4].second});
    this->_ressources.push_back({std::make_shared<Phiras> (),other._ressources[5].second});
    this->_ressources.push_back({std::make_shared<Thystame> (),other._ressources[6].second});
}

zappyGUI::Tile& zappyGUI::Tile::operator=(const Tile& other)
{
    if (this != &other) {
        this->_pos = other._pos;
        this->_players = other._players;
        this->_ressources.push_back({std::make_shared<Food> (),other._ressources[0].second});
        this->_ressources.push_back({std::make_shared<Linemate> (),other._ressources[1].second});
        this->_ressources.push_back({std::make_shared<Deraumere> (),other._ressources[2].second});
        this->_ressources.push_back({std::make_shared<Sibur> (),other._ressources[3].second});
        this->_ressources.push_back({std::make_shared<Mendiane> (),other._ressources[4].second});
        this->_ressources.push_back({std::make_shared<Phiras> (),other._ressources[5].second});
        this->_ressources.push_back({std::make_shared<Thystame> (),other._ressources[6].second});
    }
    return *this;
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

std::vector <std::pair<std::shared_ptr <zappyGUI::IRessource>, int>> &zappyGUI::Tile::getRessources()
{
    return this->_ressources;
}

const std::vector <std::pair<std::shared_ptr <zappyGUI::IRessource>, int>> &zappyGUI::Tile::getRessourcesConst() const
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

void zappyGUI::Tile::removePlayerAt(int id)
{
    for (size_t i = 0; i < this->_players.size(); i++) {
        if (this->_players[i]->getId() == id) {
            this->_players.erase(this->_players.begin() + i);
            break;
        }
    }
}

void zappyGUI::Tile::addRessource(std::shared_ptr <zappyGUI::IRessource> newVal)
{
    this->_ressources.push_back({newVal, 1});
}
