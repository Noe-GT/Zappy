/*
** EPITECH PROJECT, 2024
** zap
** File description:
** Player.cpp
*/

#include "Player.hpp"

zappyGUI::Player::Player()
{
}

zappyGUI::Player::~Player()
{
}

zappyGUI::Player::Player(const zappyGUI::Player& other):
    _id(other._id),
    _lvl(other._lvl),
    _name(other._name),
    _inventory(other._inventory),
    _spellInProgress(other._spellInProgress),
    _visionData(other._visionData),
    _logs(other._logs)
{
}

int zappyGUI::Player::getId()
{
    return this->_id;
}

int zappyGUI::Player::getLvl()
{
    return this->_lvl;
}

std::string zappyGUI::Player::getName()
{
    return this->_name;
}

std::vector <std::shared_ptr <zappyGUI::IRessource>> zappyGUI::Player::getInventory()
{
    return this->_inventory;
}

std::shared_ptr <zappyGUI::ISpell> zappyGUI::Player::getSpellInProgress()
{
    return this->_spellInProgress;
}

std::vector <zappyGUI::Tile> zappyGUI::Player::getVisionData()
{
    return this->_visionData;
}

std::vector <std::string> zappyGUI::Player::getLogs()
{
    return this->_logs;
}


void zappyGUI::Player::setId(int newVal)
{
    this->_id = newVal;
}

void zappyGUI::Player::setLvl(int newVal)
{
    this->_lvl = newVal;
}

void zappyGUI::Player::setName(std::string newVal)
{
    this->_name = newVal;
}

void zappyGUI::Player::setInventory(std::vector <std::shared_ptr <zappyGUI::IRessource>> newVal)
{
    this->_inventory = newVal;
}

void zappyGUI::Player::setSpellInProgress(std::shared_ptr <zappyGUI::ISpell> newVal)
{
    this->_spellInProgress = newVal;
}

void zappyGUI::Player::setVisionData(std::vector <zappyGUI::Tile> newVal)
{
    this->_visionData = newVal;
}

void zappyGUI::Player::setLogs(std::vector <std::string> newVal)
{
    this->_logs = newVal;
}
