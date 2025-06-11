/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include "../UI/shared/IGraphical.hpp"
#include <iostream>
zappyGUI::Game::Game() : _frequence(0), _teamNbr(0), _gameInProgess(false), _mapSize(30, 30)
{
    for (size_t y = 0; y < this->_mapSize.second; y++) {
        this->_map.emplace_back();
        for (size_t x = 0; x < this->_mapSize.first; x++)
            this->_map.back().emplace_back(std::pair<size_t, size_t>(x, y));
    }
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

std::pair<size_t, size_t> zappyGUI::Game::getMapSize()
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
    this->_map.clear();
    this->_map.resize(newY);
    for (int y = 0; y < newY; y++) {
        this->_map[y].reserve(newX);
        for (int x = 0; x < newX; x++)
            this->_map[y].emplace_back(std::make_pair(x, y));
    }
    std::clog << "map have now a size of " << this->_map.size() << "x" << (this->_map.empty() ? 0 : this->_map[0].size()) << std::endl;
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

void zappyGUI::Game::display(std::shared_ptr<zappyGUI::IGraphical> renderer) const
{
    renderer->update();
    renderer->display();
}
