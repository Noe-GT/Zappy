/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include <iostream>
zappyGUI::Game::Game() : _frequence(0), _teamNbr(0), _gameInProgess(false), _mapSize(0, 0)
{
}

zappyGUI::Game::~Game()
{
}

int zappyGUI::Game::getFrequence()
{
    return this->_frequence;
}

int zappyGUI::Game::getTeamNbr()
{
    return this->_teamNbr;
}

bool zappyGUI::Game::isGameInProgess()
{
    return this->_gameInProgess;
}

std::vector <std::string> &zappyGUI::Game::getLogs()
{
    return this->_logs;
}

std::vector <std::vector <zappyGUI::Tile>> &zappyGUI::Game::getMap()
{
    return this->_map;
}

std::pair<int, int> zappyGUI::Game::getMapSize()
{
    return this->_mapSize;
}

std::vector <zappyGUI::Player> &zappyGUI::Game::getPlayers()
{
    return this->_players;
}

std::vector <std::pair<std::shared_ptr <zappyGUI::Player>, int>> &zappyGUI::Game::getEggs()
{
    return this->_eggs;
}

std::vector <std::string> &zappyGUI::Game::getTeams()
{
    return this->_teams;
}

void zappyGUI::Game::setFrequence(int newVal)
{
    this->_frequence = newVal;
}

void zappyGUI::Game::setTeamNbr(int newVal)
{
    this->_teamNbr = newVal;
}

void zappyGUI::Game::setIsGameInProgess(bool newVal)
{
    this->_gameInProgess = newVal;
}

void zappyGUI::Game::setLogs(std::vector <std::string> newVal)
{
    this->_logs = newVal;
}

void zappyGUI::Game::addLogs(std::string newVal)
{
    this->_logs.push_back(newVal);
}

void zappyGUI::Game::setMap(std::vector <std::vector <zappyGUI::Tile>> newVal)
{
    this->_map = newVal;
}

void zappyGUI::Game::setMapSize(int newX, int newY)
{
    this->_mapSize = {newX, newY};
    this->_map.resize(newY);
    for (auto& row : this->_map)
        row.resize(newX, Tile());
    std::clog << "map have now a size of " << this->_map.size() << "x" << this->_map[0].size() << std::endl;
}

void zappyGUI::Game::setPlayers(std::vector <zappyGUI::Player> newVal)
{
    this->_players = newVal;
}

void zappyGUI::Game::addPlayer(zappyGUI::Player newVal)
{
    this->_players.push_back(newVal);
}

void zappyGUI::Game::setEggs(std::vector <std::pair <std::shared_ptr <zappyGUI::Player>, int>> newVal)
{
    this->_eggs = newVal;
}

void zappyGUI::Game::addEgg(std::shared_ptr <zappyGUI::Player> newVal, int ID)
{
    this->_eggs.push_back({newVal, ID});
}

void zappyGUI::Game::setTeams(std::vector <std::string> newVal)
{
    this->_teams = newVal;
}

void zappyGUI::Game::addTeam(std::string newVal)
{
    this->_teams.push_back(newVal);
}

void zappyGUI::Game::display()
{
    //TODO: implement the display method
}
