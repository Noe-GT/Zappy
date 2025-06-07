/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Tile.cpp
*/
#include "Tile.hpp"
#include "ressources/Food.hpp"
#include "ressources/Linemate.hpp"
#include "ressources/Deraumere.hpp"
#include "ressources/Sibur.hpp"
#include "ressources/Mendiane.hpp"
#include "ressources/Phiras.hpp"
#include "ressources/Thystame.hpp"
#include "../GUI.hpp"

zappyGUI::Tile::Tile()
{
    this->_ressources.push_back({std::make_shared<Food> (),0});
    this->_ressources.push_back({std::make_shared<Linemate> (),0});
    this->_ressources.push_back({std::make_shared<Deraumere> (),0});
    this->_ressources.push_back({std::make_shared<Sibur> (),0});
    this->_ressources.push_back({std::make_shared<Mendiane> (),0});
    this->_ressources.push_back({std::make_shared<Phiras> (),0});
    this->_ressources.push_back({std::make_shared<Thystame> (),0});
}

zappyGUI::Tile::~Tile()
{
}

std::vector <std::shared_ptr <zappyGUI::Player>> &zappyGUI::Tile::getPlayers()
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

void zappyGUI::Tile::display(zappyGUI::GUI &gui)
{
    gui.getRenderers()[0]->display();
    //TODO: display players
    //TODO: display ressources
}
